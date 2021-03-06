/**
 *
 * Polytech Marseille
 * Case 925 - 163, avenue de Luminy
 * 13288 Marseille CEDEX 9
 *
 * Ce fichier est l'oeuvre d'eleves de Polytech Marseille. Il ne peut etre
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 * Copyright (c) 2014 Alex&Olivier. All rights reserved.
 */

/**
 * @author LAGRANGE CETTO Alexandre <>
 * @author MARIN Olivier <olivier.marin@etu.univ-amu.fr>
 *
 * @todo
 */

/**
 * @file in_out.cpp
 * @brief Module gerant la lecture / ecriture dans des fichiers externes
 * 
 */

#include <iostream>
#include <stdio.h>
#include "string.h"

#include "in_out.h"

using namespace std;

static int NB_BITS_CODE = 13; // marche a partir de 13


char reader(char * uncomp_file){
    char current_char;
    FILE* entry;
    entry = fopen(uncomp_file, "r");
    current_char = fgetc(entry);
    while(current_char != EOF){
        cout << current_char;
        current_char = fgetc(entry);
        //return current_char;
    }
    return current_char;
}

void writer(int code, const char* foutput){
    FILE* output = NULL;
    output = fopen(foutput, "a+");

    if (output == NULL) {
        cout << "Error, can't write file !" << endl;
        return;
    }
    
    fprintf (output, "%d\n",code);
    //fputc(code, output);

   
    fclose(output);
}

void writer_char(unsigned char * code){
    fprintf (output, "%s",code);
}

unsigned char * read_char()
{
    unsigned char* code = (unsigned char*)malloc(sizeof(unsigned char));
    fread(code, sizeof(unsigned char), 1, input);
    return code;
}

int fichier_existe(char * nom_fichier)
{
    FILE * file = NULL;
    file = fopen(nom_fichier, "r");
    if (file == NULL)
    {
        return 0;
    }
    fclose(file);
    return 1;
}

/** @brief Ouvre le fichier d'entree.
 *
 * Initialise la variable globale input par un descripteur sur 
 * le fichier d'entree (lecture seule).
 * @param nom_fichier_entree  Chaine de caracteres du nom du fichier d'entree.
 * @return  void
 */
void ouvrir_fichier_entree (char * nom_fichier_entree) 
{
   input = fopen (nom_fichier_entree, "r");
}

/** @brief Ouvre le fichier de sortie.
 *
 * Initialise la variable globale output par un descripteur sur 
 * le fichier de sortie.
 * @param nom_fichier_sortie  Chaine de caracteres du nom du fichier de sortie.
 * @return  void
 */
void ouvrir_fichier_sortie (char * nom_fichier_sortie)
{
    output = fopen (nom_fichier_sortie, "w+");
}

/** @brief Ferme les descripteurs sur les fichiers de lecture et d'ecriture.
 * @param void
 * @return  void
 */
void fermer_fichiers ()
{
    fclose (input);
    fclose (output);
}

/** @brief Met à 1 le ieme bit du buffer
 * @param buffer  Tableau de bits.
 * @param i  Position du bit a mettre a un.
 * @return  void
 */
static void mise_a_un (unsigned char * buffer, int i) 
{
    unsigned char un = 1;
    un = un << i;
    *buffer = *buffer | un;
}

/** @brief Lit le caractere suivant du fichier d'entree.
 * 
 * Lit le caractere suivant du fichier d'entree.
 * @param void
 * @return  Retourne le caractere lu sous forme d'un entier
 */
int lire_caractere () 
{
    int caractere_lu;
    caractere_lu = fgetc (input);

    return caractere_lu;
}

/** @brief Ecrit, en binaire, le code sur un certain nombre de bits
 * @param code  Code a ecrire.
 * @param vider_buffer  Booleen qui, lorsqu'il est à 1, ecrit le buffer restant.
 * @return  void
 */
void ecrire_code_binaire (unsigned int code, int vider_buffer) 
{
 
    static unsigned char buffer = 0; /* Debut d'ecriture dans le buffer à gauche */
    static int indice_buffer = 7;
    int i;
    
    for (i = NB_BITS_CODE - 1; i >= 0; i--) {
        int bit_i = ((code >> i) & 1);
        
        switch (bit_i) {
            case 0 : break; /* Le bit i est deja à zero */
            case 1 : 
                mise_a_un (&buffer, indice_buffer); 
                break;
        }
        /* Ecriture, dans le fichier, du buffer lorsqu'il est plein */
        if (indice_buffer == 0) {
            fwrite (&buffer, sizeof (unsigned char), 1, output);
            buffer = 0;
            indice_buffer = 7;
        }
        else
            indice_buffer--;
    }
    
    if (vider_buffer) {
        fwrite (&buffer, sizeof (unsigned char), 1, output);
        buffer = 0;
        indice_buffer = 7;
    }
}

/** @brief Lit, en binaire, le code sur un certain nombre de bits
 * @return  Code lu sous forme d'entier positif
 */
unsigned int lire_code_binaire () 
{
    static unsigned char buffer = 0; /* Debut d'ecriture dans le buffer à droite */
    static unsigned int indice_buffer = 0;
    unsigned int code;
    int i, nb_bits_a_lire, temp = 0;
    
    
    /* Recuperation des bits restants du buffer */
    nb_bits_a_lire = NB_BITS_CODE - indice_buffer;
    code = ((int)buffer) << nb_bits_a_lire;
    
    for (i = 1; i <= (nb_bits_a_lire / 8); i++) {
        fread (&buffer, sizeof (unsigned char), 1, input);
        
        temp = ((int)buffer) << (nb_bits_a_lire - 8*i);
        code = code | temp;
    }
    
    /* Lecture du dernier paquet de 8 bits dont les non utilisés iront dans le buffer */
    if (nb_bits_a_lire % 8 != 0) {
        fread (&buffer, sizeof (unsigned char), 1, input);
        
        temp = ((int)buffer) >> (8 - nb_bits_a_lire % 8);
        code = code | temp;
        
        /* Stockage dans le buffer des bits restants */
        indice_buffer = 8 - nb_bits_a_lire % 8;
        buffer = buffer << (8 - indice_buffer);
        buffer = buffer >> (8 - indice_buffer);
    }
    else {
        buffer = 0;
        indice_buffer = 0;
    }
    
    return code;
}

int show_NB_BITS_CODE(void)
{
    return NB_BITS_CODE;
}

void change_NB_BITS_CODE(void)
{
    NB_BITS_CODE = NB_BITS_CODE + 1;
}