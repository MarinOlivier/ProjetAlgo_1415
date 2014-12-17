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

int codeFinal = 0;

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
		ptarbre aux = creer_noeud('\0', codeFinal, NULL, NULL);
		ptarbre aux_bis = creer_noeud(c[0], codeFinal, NULL, aux);
		arbre->frere = aux_bis;

		codeFinal++;
		if (codeFinal == 256) {
			codeFinal = 260;
		}
		
	}
	if (arbre->frere->code > (int)c[0])
	{
		ptarbre aux = arbre->frere;
		ptarbre aux_bis = creer_noeud('\0', codeFinal, NULL, NULL);
		ptarbre aux_sec = creer_noeud(c[0], codeFinal, aux, aux_bis);
		arbre->frere = aux_sec;
		
		codeFinal++;
		if (codeFinal == 256) {
			codeFinal = 260;
		}
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

	ptarbre racine = creer_noeud((unsigned char)'\0', 0, NULL, NULL);
	ajout(racine, c);

	for (int i = 1; i < 256; i++) {
		c[0] = (unsigned char)i;
		c[1] = '\0';
		ajout(racine, c);
	}

	return racine;
}

int getCode(unsigned char s[], ptarbre arbre)
{
	if (arbre == NULL && arbre->frere == NULL)
		return -1;

	if (s[0] == arbre->etiq)
	{
		if (s[0] == '\0')
			return arbre->code;
		else
			return getCode(&s[1], arbre->fils);
	}
	else
		{
			if (arbre->frere != NULL)
				return getCode(s, arbre->frere);
			else
				return -1;
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
			cout << "\\0 " << arbre->code << endl;
		else
			cout << arbre->etiq;
		affichage(arbre->fils);
		affichage(arbre->frere);
	}
}

int showCode(void){
	return codeFinal;
}