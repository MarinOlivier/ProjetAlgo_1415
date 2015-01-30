//
//  decompression.cpp
//  projet_algo
//
//  Created by Olivier on 11/11/2014.
//  Copyright (c) 2014 Alex&Olivier. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <stdio.h>

#include "decompression.h"
#include "arbre.h"
#include "in_out.h"

using namespace std;

#define MAX 10000

// lecture d'un caractère c;
// écrire c;
// w = c;
// tant que (lecture d'un caractère c) faire
// 		si (c > 255 && l'index c existe dans le dictionnaire) faire
// 			entrée = l'entrée du dictionnaire de c;
// 		sinon si (c > 255 && l'index c n'existe pas dans le dictionnaire) faire
//      	entrée = w + w[0];
// 		sinon
//      	entrée = c;
// 		fin si;
//
//      sortie : écrire entrée;
//      ajouter w+entrée[0] au dictionnaire;
//      w = entrée;
// fin tant que;


// Autre version plus simple 
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


//    unsigned char * code_read = read_char();
//    cout << "code read " << code_read << endl;



   // unsigned char * mot_precedent = NULL;
   //  int code_lu;
    
   //  code_lu = lire_code_binaire ();
   //  mot_precedent = rechercher_mot (dictionnaire, code_lu);
   //  ecrire_texte (mot_precedent);
    
   //  while ((code_lu = lire_code_binaire ()) != 0) {
   //      unsigned char * mot_decode                  = NULL,
   //                    * mot_precedent_et_mot_decode = NULL;
        
   //      mot_decode = rechercher_mot (dictionnaire, code_lu);
   //      if (mot_decode == NULL) {
   //          mot_decode = copier_chaine (mot_precedent);
   //          mot_decode = ajouter_caractere (mot_decode, mot_precedent[0]);
   //      }
        
   //      ecrire_texte (mot_decode);
        
   //      free (mot_precedent_et_mot_decode);
        
   //      mot_precedent_et_mot_decode = copier_chaine (mot_precedent);
   //      mot_precedent_et_mot_decode = ajouter_caractere (mot_precedent_et_mot_decode, mot_decode[0]);
        
   //      if (DICTIONNAIRE_PLEIN == 0)
   //          ajouter_mot (dictionnaire, mot_precedent_et_mot_decode);
        
   //      free (mot_precedent_et_mot_decode);
   //      free (mot_precedent);
        
   //      mot_precedent = mot_decode;
   //  }
    
   //  free (mot_precedent);

static unsigned char * w;

void decompress(ptarbre arbre)
{
    cout << "dans decomp" << endl;
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
            cout << "dans if " << endl;
            cout << "mot_precedent " << endl;

            cout << mot_precedent << endl;

            mot_decode = copier_chaine(mot_precedent);
            mot_decode = addChar(mot_decode, mot_precedent[0]);
        }

        cout << "Ecriture de  " << mot_decode << endl;
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


    // unsigned char* c;

    // c = lire_code_binaire();
    // cout << "c = " << c << endl;
    // writer_char(c[0]);
    // unsigned char * entree = (unsigned char*)malloc(sizeof(unsigned char));

    // w = c;
    // while((c = lire_code_binaire()) != NULL)
    // {
    //     entree = searchCode(getCode(w, arbre), arbre);
    //     writer_char(entree[0]);
    //     addChar(w, entree[0]);
    //     memset(w, 0, sizeof(w));
    //     cout << entree << endl;
    //     w = entree;
    // }

}