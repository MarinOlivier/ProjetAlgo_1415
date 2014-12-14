//
//  arbre.cpp
//  projet_algo
//
//  Created by Olivier on 11/11/2014.
//  Copyright (c) 2014 Alex&Olivier. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "arbre.h"

using namespace std;

ptarbre creer_arbre()
{
	ptarbre arbre = (ptarbre)malloc(sizeof(noeud));
	return arbre;
}

ptarbre creer_noeud(unsigned char etiq, int code, ptarbre frere, ptarbre fils)
{
	ptarbre aux;
	aux = (ptarbre)malloc(sizeof(noeud));
	aux->etiq = etiq;
	aux->code = code;
	aux->frere = frere;
	aux->fils = fils;

	return aux;
}

void ajout(ptarbre arbre, unsigned char c[])
{
	if (arbre->etiq != c[0] && arbre->frere != NULL && arbre->frere->code <= (int)c[0])
		ajout(arbre->frere, c);

	if (arbre->frere == NULL)
	{
		ptarbre aux = creer_noeud('\0', 0, NULL, NULL);
		ptarbre aux_bis = creer_noeud(c[0], (int)c[0], NULL, aux);
		arbre->frere = aux_bis;
	}
	if (arbre->frere->code > (int)c[0])
	{
		ptarbre aux = arbre->frere;
		ptarbre aux_bis = creer_noeud('\0', 0, NULL, NULL);
		ptarbre aux_sec = creer_noeud(c[0], (int)c[0], aux, aux_bis);
		arbre->frere = aux_sec;
	}
	if (arbre->etiq == c[0] && c[1] != '\0')
	{
		c++;
		ajout(arbre->fils, c);
	}
}


ptarbre init_arbre_ASCII(void)
{
	unsigned char c[2];
	c[0] = (unsigned char)'\0';
	c[1] = '\0';

	cout << c << endl;

	ptarbre racine = creer_noeud((unsigned char)'\0', 0, NULL, NULL);
	ajout(racine, c);

	for (int i = 1; i < 256; i++) {
		c[0] = (unsigned char)i;
		c[1] = '\0';
		ajout(racine, c);
	}

	return racine;

}

bool estPresent(unsigned char s[], ptarbre arbre)
{
	if (arbre == NULL && arbre->frere == NULL)
		return false;

	if (s[0] == arbre->etiq)
	{
		if (s[0] == '\0')
			return true;
		else
			return estPresent(&s[1], arbre->fils);
	}
	else
		{
			if (arbre->frere != NULL)
				return estPresent(s, arbre->frere);
			else
				return false;
		}
		
}

void affichage(ptarbre arbre)
{
	if(arbre == NULL)
	{
		return;
	}
	else
	{
		if (arbre->etiq == '\0')
			cout << "\\0 " << endl;
		else
			cout << arbre->etiq <<'\t'<< arbre->code;
		affichage(arbre->fils);
		affichage(arbre->frere);
	}
}

