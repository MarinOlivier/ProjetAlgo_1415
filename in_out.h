//
//  in_out.h
//  pa1415
//
//  Created by Alex on 02/12/2014.
//  Copyright (c) 2014 Alex et Olivier. All rights reserved.
//

#ifndef __pa1415__in_out__
#define __pa1415__in_out__

#include "arbre.h"

static FILE * output = NULL;
static FILE * input = NULL;

char reader(char *);
void writer(int code, const char* foutput);
void writer_char(unsigned char * code);
unsigned char * read_char();
int fichier_existe(char * nom_fichier);
void ouvrir_fichier_entree (char * nom_fichier_entree);
void ouvrir_fichier_sortie (char * nom_fichier_sortie);
void fermer_fichiers ();
static void mise_a_un (unsigned char * buffer, int i);
int lire_caractere ();
void ecrire_code_binaire (unsigned int code, int vider_buffer);
unsigned int lire_code_binaire ();


#endif