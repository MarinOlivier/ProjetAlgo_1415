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
    int j = 0;
    char text[] =   {'a','b','c','a','a','b','\0'};
    char c = text[0];
    while (c != '\0') {
        short i = 0;
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
            //writer(w);
            memset(w, 0, sizeof(w));
            w[0] = c;
        }
        //cout << c;
        c = text[++j];
        unsigned char s[3] = {'a', 'a', '\0'};
        //cout << estPresent(s, arbre) << endl;

        //cout << w;
        // writer(w);
    }

    // affichage(arbre);
    
    // cout << endl;

// 	FILE* entry = NULL;
// 	entry = fopen(fentry, "r");
// 	if (entry != NULL)
// 	{
// 		FILE* output = NULL;
// 		output = fopen(foutput, "w");
// 		if (output != NULL)
// 		{
// 			
// 			char* c = NULL;
// 			while(fgets(c, sizeof(char), entry) != NULL)
// 			{
// 				if(estPresent(strcat_p(w,c), arbre))
// 				{
// 					w = strcat_p(w,c);
// 				}
// 				else
// 				{
// 					ajout(strcat_p(w,c), arbre);
// 					char* code = (char*)((int)w); // <<-------- Trouver un autre moyen de récupérer le code
// 					fputs(code, output);
// 					w = c;
// 				}
// 			}
// 			char* code = (char*)((int)w); // <<----------- Trouver un autre moyen de récupérer le code
// 			fputs(code, output);
// 		}
// 		else
// 		{
// 			cout << "Impossible d'ouvrir le fichier de sortie" << endl;
// 		}
// 	}
// 	else
// 	{
// 		cout << "Impossible d'ouvrir le fichier d'entré" << endl;
// 	}
}