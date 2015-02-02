/**
 *
 * Polytech Marseille
 * Case 925 - 163, avenue de Luminy
 * 13288 Marseille CEDEX 9
 *
 * Ce fichier est l'oeuvre d'eleves de Polytech Marseille. Il ne peut etre
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 */

/**
 * @author BURNOTTE Delphine <delphine.burnotte@etu.univ-amu.fr>
 * @author DUFOUR Yohann <yohann.dufour@etu.univ-amu.fr>
 *
 * @version 0.0.2 / 19-01-2013
 * @todo
 */


/**
 * @file lecture_ecriture.c
 * @brief Module gerant la lecture du fichier d'entree et l'ecriture du 
 * fichier de sortie.
 */


#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionnaire.h"
#include "lecture_ecriture.h"


static FILE * fichier_entree = NULL;
static FILE * fichier_sortie = NULL;


/** @brief Ouvre le fichier d'entree.
 *
 * Initialise la variable globale fichier_entree par un descripteur sur 
 * le fichier d'entree (lecture seule).
 * @param nom_fichier_entree  Chaine de caracteres du nom du fichier d'entree.
 * @param binaire  Booleen contenant si le fichier doit etre ouvert en binaire.
 * @return  void
 */
void ouvrir_fichier_entree (char * nom_fichier_entree, int binaire) {
    if (binaire)
        fichier_entree = fopen (nom_fichier_entree, "rb");
    else
        fichier_entree = fopen (nom_fichier_entree, "r");
    
    assert (fichier_entree != NULL);
}

/** @brief Ouvre le fichier d'entree.
 *
 * Initialise la variable globale fichier_entree par un descripteur sur 
 * le fichier d'entree (lecture seule).
 * @param nom_fichier_entree  Chaine de caracteres du nom du fichier d'entree.
 * @param binaire  Booleen contenant si le fichier doit etre ouvert en binaire.
 * @return  void
 */
void ouvrir_fichier_sortie (char * nom_fichier_sortie, int binaire) {
    if (binaire)
        fichier_sortie = fopen (nom_fichier_sortie, "wb");
    else
        fichier_sortie = fopen (nom_fichier_sortie, "w");
    
    assert (fichier_sortie != NULL);
}

/** @brief Ferme les descripteurs sur les fichiers de lecture et d'ecriture.
 * @param void
 * @return  void
 */
void fermer_fichiers () {
    fclose (fichier_entree);
    fclose (fichier_sortie);
}

/** @brief Lit le caractere suivant du fichier d'entree.
 * 
 * Lit le caractere suivant du fichier d'entree et alloue une chaine de 
 * caracteres contenant ce caractere. Si aucun caractere n'est lu, on renvoie le
 * pointeur NULL.
 * @param void
 * @return  Retourne le caractere lu sous forme d'une chaine de caracteres.
 */
unsigned char * lire_caractere () {
    unsigned char * chaine = NULL;
    int caractere_lu;
    assert (fichier_entree != NULL);
    
    caractere_lu = fgetc (fichier_entree);
    
    if (caractere_lu != EOF) {
        chaine = malloc (sizeof (unsigned char) * 2);
        sprintf ((char *)chaine, "%c", (unsigned char)caractere_lu);
    }
    
    return chaine;
}

/** @brief Ecrit le texte donné dans le fichier de sortie.
 * @param texte  Texte à écrire dans le fichier de sortie.
 * @return  void
 */
void ecrire_texte (unsigned char * texte) {
    assert (fichier_sortie != NULL);
    
    fprintf (fichier_sortie, "%s", texte);
}

/** @brief Lit le code suivant du fichier d'entree.
 * @param void
 * @return  Retourne le code lu.
 */
unsigned int lire_code () {
    unsigned int code = 0;
    assert (fichier_entree != NULL);
    
    fscanf (fichier_entree, "%d", &code);
    
    return code;
}

/** @brief Ecrit le code donné dans le fichier de sortie.
 * @param code  Code à ecrire dans le fichier de sortie.
 * @return  void
 */
void ecrire_code (unsigned int code) {
    assert (fichier_sortie != NULL);
    
    fprintf (fichier_sortie, "%d ", code);
}


/** @brief Met à 1 le ieme bit du buffer
 * @param buffer  Tableau de bits.
 * @param i  Position du bit a mettre a un.
 * @return  void
 */
static void mettre_a_un (unsigned char * buffer, int i) {
    unsigned char un = 1;
    un = un << i;
    *buffer = *buffer | un;
}

/** @brief Lit, en binaire, le code sur un certain nombre de bits
 * @return  Code lu sous forme d'entier positif
 */
unsigned int lire_code_binaire () {
    static unsigned char buffer = 0; /* Debut d'ecriture dans le buffer à droite */
    static unsigned int indice_buffer = 0;
    unsigned int code;
    int i, nb_bits_a_lire, temp = 0;
    
    assert (fichier_entree != NULL);
    
    /* Recuperation des bits restants du buffer */
    nb_bits_a_lire = NB_BITS_CODE - indice_buffer;
    code = ((int)buffer) << nb_bits_a_lire;
    
    for (i = 1; i <= (nb_bits_a_lire / 8); i++) {
        fread (&buffer, sizeof (unsigned char), 1, fichier_entree);
        
        temp = ((int)buffer) << (nb_bits_a_lire - 8*i);
        code = code | temp;
    }
    
    /* Lecture du dernier paquet de 8 bits dont les non utilisés iront dans le buffer */
    if (nb_bits_a_lire % 8 != 0) {
        fread (&buffer, sizeof (unsigned char), 1, fichier_entree);
        
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

/** @brief Ecrit, en binaire, le code sur un certain nombre de bits
 * @param code  Code a ecrire.
 * @param vider_buffer  Booleen qui, lorsqu'il est à 1, ecrit le buffer restant.
 * @return  void
 */
void ecrire_code_binaire (unsigned int code, int vider_buffer) {
    static unsigned char buffer = 0; /* Debut d'ecriture dans le buffer à gauche */
    static int indice_buffer = 7;
    int i;
    
    assert (fichier_sortie != NULL);
    
    for (i = NB_BITS_CODE - 1; i >= 0; i--) {
        int bit_i = ((code >> i) & 1);
        
        switch (bit_i) {
            case 0 : break; /* Le bit i est deja à zero */
            case 1 : mettre_a_un (&buffer, indice_buffer); break;
        }
        
        /* Ecriture, dans le fichier, du buffer lorsqu'il est plein */
        if (indice_buffer == 0) {
            fwrite (&buffer, sizeof (unsigned char), 1, fichier_sortie);
            buffer = 0;
            indice_buffer = 7;
        }
        else
            indice_buffer--;
    }
    
    if (vider_buffer) {
        fwrite (&buffer, sizeof (unsigned char), 1, fichier_sortie);
        buffer = 0;
        indice_buffer = 7;
    }
}


/** @brief Recupere la taille du fichier d'entree en octets
 * @return  Taille du fichier d'entree en octets
 */
long recuperer_taille_fichier_entree () {
    return (long)ftell (fichier_entree);
}

/** @brief Recupere la taille du fichier de sortie en octets
 * @return  Taille du fichier de sortie en octets
 */
long recuperer_taille_fichier_sortie () {
    return (long)ftell (fichier_sortie);
}
