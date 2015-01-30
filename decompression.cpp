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
//          entry = dictionary entry for k;
//          output entry;
//          add w + entry[0] to dictionary;
//          w = entry;
//         }

static unsigned char w[MAX] = {0};

void decompress(ptarbre arbre)
{
    unsigned char c;
    fscanf(input, "%d", &c);
    writer_char(c);
    unsigned char * entree = (unsigned char*)malloc(sizeof(unsigned char));

    w[0] = c;

    while(fscanf(input, "%d", &c) != EOF)
    {
        entree = searchCode(c, arbre);
        writer_char(c);
        addChar(w, entree[0]);
        memset(w, 0, sizeof(w));
        
        w = entree;
    }

}