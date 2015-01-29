//
//  in_out.cpp
//  pa1415
//
//  Created by Alex on 02/12/2014.
//  Copyright (c) 2014 Alex et Olivier. All rights reserved.
//
#include <iostream>
#include <stdio.h>
#include "string.h"

#include "in_out.h"

using namespace std;

#define NB_BITS_CODE 8

char reader(char * uncomp_file){
    char current_char;
    FILE* entry;
    entry = fopen("/Users/alex/developper/pa1415/test.txt", "r");
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

void writer_char(char code, const char* foutput){
    FILE* output = NULL;
    output = fopen(foutput, "a+");

    if (output == NULL) {
        cout << "Error, can't write file !" << endl;
        return;
    }

    fprintf (output, "%c",code);
    //fputc(code, output);

   
    fclose(output);
}


static void mise_a_un (unsigned char * buffer, int i) {
    unsigned char un = 1;
    un = un << i;
    *buffer = *buffer | un;
}


void ecrire_code_binaire (unsigned int code, const char* foutput, int vider_buffer) 
{
    FILE* output = NULL;
    output = fopen(foutput, "a+");
    
    if (output == NULL)
    {
        cout << "Error : can not open file !" << endl;
        return;
    }

 
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

unsigned int lire_code_binaire (const char* finput) 
{
    FILE* input = NULL;
    input = fopen(foutput, "a+");
    
    if (input == NULL)
    {
        cout << "Error : can not open file !" << endl;
        return;
    }

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