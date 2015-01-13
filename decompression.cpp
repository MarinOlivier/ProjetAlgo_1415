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

static unsigned char w[MAX] = {0};

void decompress(const char* finput, const char* foutput, ptarbre arbre)
{

	FILE* entry = NULL;
    entry = fopen(finput, "r");
    unsigned char entree[MAX] = {0};
    int c;
    int i = 0;

    if (entry == NULL) {
        cout << "Error, can't read file !" << endl;
        return;
    }

    fscanf(entry, "%d", &c);
    cout << "c : " << c << endl;
    writer_char(c, foutput);

    w[1] = c;

    while(fscanf(entry, "%d", &c) != EOF)
    {

    	while (w[i] != '\0') {
            i++;
        }

    	cout << "c : " << c << endl;
    	if (c >= 260 && searchCode(c, arbre) != NULL)
    	{

    	}
    	else if(c >= 260 && searchCode(c, arbre) == NULL)
    	{

    	}
    	else
    	{
    		entree[0] = (char)c;
    	}

    	cout << "entree : " << entree << endl;

    	// écriture de entree
    	int k=0;
    	while(entree[k] != 0)
    	{
    		writer_char(entree[k], foutput);
    		k++;
    	}

    	// ajout de w+entree[0] au dico
    	w[i] = entree[0];
    	cout << "ajout de " << w << endl;
    	ajout(arbre, w);

    	// w = entree
    	int j = 0;
    	for (j = 0; j < MAX; j++)
    		w[j] = entree[j];

    }

}