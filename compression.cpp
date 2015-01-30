//
//  compression.cpp
//  projet_algo
//
//  Created by Olivier on 11/11/2014.
//  Copyright (c) 2014 Alex&Olivier. All rights reserved.
//

#include <iostream>
#include <stdio.h> // gestion de fichiers
#include "string.h"

#include "compression.h"
#include "arbre.h"
#include "in_out.h"

using namespace std;


static unsigned char w[10000] = {0};
//unsigned char * w = (unsigned char *)malloc(10 * sizeof(char));

void compress(ptarbre arbre)
{
// w = Nul;
//    tant que (lecture d'un caractère c) faire
//        si (w + c existe dans le dictionnaire) alors
//            w = w + c;
//        sinon
//            ajouter w + c au dictionnaire;
//            écrire le code de w;
//            w = c;
//        fin si
//    fin tant que
//    écrire le code de w;

    unsigned char c;
    int buffer = 0;
    
    buffer = fgetc(input);
    while(buffer != EOF){        
        short i = 0;

        c = buffer;
        while (w[i] != '\0') {
            i++;
        }
        // cout << "w = " << w << " i = " << i << endl;
        w[i] = c;

        // cout << "w = " << w;
        // cout << " dans le dico ? " << getCode(w, arbre) << endl;
        if (getCode(w, arbre) > 0)
            w[i] = c;
        else {
            // cout << "ajout de " << w << endl;
            ajout(arbre, w);

            // passage de w+c a w
            w[i] = 0;

            int codeToWrite = getCode(w, arbre);

            ecrire_code_binaire (codeToWrite, 0);
            memset(w, 0, sizeof(w));
            w[0] = c;
        }
        buffer = fgetc(input);
    }

    int codeToWrite = getCode(w, arbre);
    ecrire_code_binaire (codeToWrite, 1);

}