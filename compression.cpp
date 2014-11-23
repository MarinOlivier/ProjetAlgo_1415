//
//  compression.cpp
//  projet_algo
//
//  Created by Olivier on 11/11/2014.
//  Copyright (c) 2014 Alex&Olivier. All rights reserved.
//

#include <iostream>
#include <stdio.h> // gestion de fichiers

#include "compression.h"
#include "arbre.h"

using namespace std;

void compress(const char* fentry, const char* foutput)
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

	// ptarbre arbre = init_arbre_ASCII();

	// FILE* entry = NULL;
	// entry = fopen(fentry, "r");
	// if (entry != NULL)
	// {
	// 	FILE* output = NULL;
	// 	output = fopen(foutput, "w");
	// 	if (output != NULL)
	// 	{
	// 		char* w = NULL;
	// 		char* c = NULL;
	// 		while(fgets(c, 1, entry) != NULL)
	// 		{
	// 			if(estPresent(strcat(w,c), arbre))
	// 			{
	// 				w = strcat(w,c);
	// 			}
	// 			else
	// 			{
	// 				ajout(strcat(w,c), arbre);
	// 				char* code = (char*)((int)w); // <<-------- Trouver un autre moyen de récupérer le code
	// 				fputs(code, output);
	// 				w = c;
	// 			}
	// 		}
	// 		char* code = (char*)((int)w); // <<----------- Trouver un autre moyen de récupérer le code
	// 		fputs(code, output);
	// 	}
	// 	else
	// 	{
	// 		cout << "Impossible d'ouvrir le fichier de sortie" << endl;
	// 	}
	// }
	// else
	// {
	// 	cout << "Impossible d'ouvrir le fichier d'entré" << endl;
	// }
}