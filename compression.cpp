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

using namespace std;


unsigned char w[10] = {0};
//unsigned char * w = (unsigned char *)malloc(10 * sizeof(char));

void compress(const char* fentry, const char* foutput, ptarbre arbre)
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
    
    FILE* entry = NULL;
    entry = fopen("/Users/alex/developper/pa1415/testa.txt", "r");
    unsigned char c;
    int buffer = 0;

    if (entry == NULL) {
        cout << "Error, can't read file !" << endl;
        return;
    }

    buffer = fgetc(entry);
    while(buffer != EOF){        
        short i = 0;

        c = buffer;
        while (w[i] != '\0') {
            i++;
        }
        cout << "w = " << w << " i = " << i << endl;
        w[i] = c;

        cout << "w = " << w << endl;
        cout << "dans le dico ? " << estPresent(w, arbre) << endl;
        if (estPresent(w, arbre))
            w[i] = c;
        else {
            cout << "ajout de " << w << endl;
            ajout(arbre, w);
            memset(w, 0, sizeof(w));
            w[0] = c;
        }
        buffer = fgetc(entry);
    }

    fclose(entry);
}


