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
 * @file arbre.cpp
 * @brief Module de gestion de l'arbre
 * 
 */

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "arbre.h"

using namespace std;

static int codeFinal = 0;

ptarbre creer_arbre()
{
	ptarbre arbre = (ptarbre)malloc(sizeof(noeud));
	return arbre;
}

ptarbre creer_noeud(unsigned char etiq, int code, ptarbre frere, ptarbre fils, ptarbre pere)
{
	ptarbre aux;
	aux = (ptarbre)malloc(sizeof(noeud));
	aux->etiq = etiq;
	aux->code = code;
	aux->frere = frere;
	aux->fils = fils;
	aux->pere = pere;
	
	return aux;
}

void ajout(ptarbre arbre, unsigned char c[])
{
	if (arbre->etiq != c[0] && arbre->frere != NULL) // && arbre->frere->code <= (int)c[0])
		ajout(arbre->frere, c);

	else if (arbre->etiq == c[0] && c[1] != '\0')
	{
		c++;
		ajout(arbre->fils, c);
	}
	else if (arbre->frere == NULL)
	{
		ptarbre aux = creer_noeud('\0', codeFinal, NULL, NULL, NULL);
		ptarbre aux_bis = creer_noeud(c[0], codeFinal, NULL, aux, NULL);
		aux->pere = aux_bis;
		arbre->frere = aux_bis;

		codeFinal++;
		//cout << "CF ++ " << endl;
		// if (codeFinal == 256) {
		// 	codeFinal = 260;
		// }
		
	}
	else if ((int)arbre->frere->etiq > (int)c[0])
	{
		ptarbre aux = arbre->frere;
		ptarbre aux_bis = creer_noeud('\0', codeFinal, NULL, NULL, NULL);
		ptarbre aux_sec = creer_noeud(c[0], codeFinal, aux, aux_bis, NULL);
		aux_bis->pere = aux_sec;
		arbre->frere = aux_sec;
		
		codeFinal++;
		//cout << "CF bis ++ " << endl;
		// if (codeFinal == 256) {
		// 	codeFinal = 260;
		// }
	}
	else
		cout << "Error : Aucune condition." << endl;
}


ptarbre init_arbre_ASCII(void)
{
	unsigned char c[2];
	c[0] = (unsigned char)'\0';
	c[1] = '\0';

	ptarbre racine = creer_noeud((unsigned char)'\0', 0, NULL, NULL, NULL);
	ajout(racine, c);

	for (int i = 1; i < 256; i++) {
		c[0] = (unsigned char)i;
		c[1] = '\0';
		ajout(racine, c);
	}

	return racine;
}


// OK 
int getCode(unsigned char s[], ptarbre arbre)
{
	if (arbre == NULL && arbre->frere == NULL)
		return -1;

	//cout << "s[0] = " << s[0] << endl;
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
				return -2;
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

unsigned char * addChar(unsigned char * str, unsigned char c){
	int length = strlen((char*)str);

	str = (unsigned char *) realloc(str,sizeof(unsigned char) * (length + 2));
	if (str!= NULL)	{
		str[length] = c;
		str[length + 1] = '\0';
	}
	return str;
}
unsigned char * insertString(unsigned char * str, unsigned char c, int place){
    
    int length = strlen((char*)str);
    str = (unsigned char *) realloc(str,sizeof(unsigned char) * (length + 2));
    //strcpy((char *)str,(char *)tempC);
    if (str!= NULL) {
        for(int i = length +1; i >= 0; i--)
            if(i > place) str[i] = str[i-1];
            else str[i] = c;
    }

    return str;
}

unsigned char * searchCode(int val, ptarbre arbre){
	if(arbre->code == val){
		unsigned char * end;
		unsigned char * tempC = (unsigned char *)malloc (sizeof (unsigned char));
		tempC[0] = '\0';
		end = addChar(tempC,arbre->etiq);
		return end;
	} else {

		unsigned char * str = NULL;
		if((arbre->fils) != NULL)
			str = searchCode(val, arbre->fils);

		if(str == NULL && arbre->frere != NULL)
			return searchCode(val, arbre->frere);

		if(str != NULL)
			str = insertString(str, arbre->etiq, 0);

		return str;
	}
}

unsigned char * copier_chaine (unsigned char * chaine) {
    int longueur_chaine = strlen ((char *)chaine);
    unsigned char * copie = NULL;
    
    copie = (unsigned char *)malloc(sizeof (unsigned char) * (longueur_chaine + 1));
    while (longueur_chaine >= 0) {
        copie[longueur_chaine] = chaine[longueur_chaine];
        longueur_chaine--;
    }
    
    return copie;
}

// unsigned char* getWord(int val, ptarbre arbre)
// {
// 	if (arbre == NULL)
// 		return EOF;
// 	ptarbre feuille = searchCode(val, arbre); 
// 	if (feuille != NULL) {
// 		// remonter l'arbre en sauvegardant chaque lettre
// 	}
// }

int showCode(void){
	return codeFinal;
}






