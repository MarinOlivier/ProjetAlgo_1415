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
 * @file decompression.cpp
 * @brief Module contenant l'algorithme de décompression
 * 
 */

#include <iostream>
#include <fstream>
#include <stdio.h>

#include "decompression.h"
#include "arbre.h"
#include "in_out.h"

using namespace std;

// read a character k;
//    output k;
//    w = k;
//    while ( read a character k )    
//   /* k could be a character or a code. */
//         {
//          entry = dictionary entry for w;
//          output entry;
//          add w + entry[0] to dictionary;
//          w = entry;
//         }


static unsigned char * w;

void decompress(ptarbre arbre)
{
    unsigned char * mot_precedent = NULL;
    int code_lu;
    
    code_lu = lire_code_binaire();
    mot_precedent = searchCode(code_lu, arbre);
    writer_char(mot_precedent);
    
    while ((code_lu = lire_code_binaire()) != 0) {

        unsigned char * mot_decode                  = NULL;
        unsigned char * mot_precedent_et_mot_decode = NULL;
        
        mot_decode = searchCode(code_lu, arbre);
        if (mot_decode == NULL) {
            mot_decode = copier_chaine(mot_precedent);
            mot_decode = addChar(mot_decode, mot_precedent[0]);
        }
        writer_char(mot_decode);
        
        free(mot_precedent_et_mot_decode);
        
        mot_precedent_et_mot_decode = copier_chaine(mot_precedent);
        mot_precedent_et_mot_decode = addChar(mot_precedent_et_mot_decode, mot_decode[0]);
        
        ajout(arbre, mot_precedent_et_mot_decode);

        free (mot_precedent_et_mot_decode);
        free (mot_precedent);
        
        mot_precedent = mot_decode;
    }
    
    free (mot_precedent);


}