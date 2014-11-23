//
//  arbre.cpp
//  projet_algo
//
//  Created by Olivier on 11/11/2014.
//  Copyright (c) 2014 Alex&Olivier. All rights reserved.
//

#include <iostream>
#include <string.h>
#include "arbre.h"

using namespace std;

ptarbre creer_arbre()
{
	ptarbre arbre = (ptarbre)malloc(sizeof(noeud));
	return arbre;
}

ptarbre creer_noeud(char etiq, int code, ptarbre frere, ptarbre fils)
{
	ptarbre aux;
	aux = (ptarbre)malloc(sizeof(noeud));
	aux->etiq = etiq;
	aux->code = code;
	aux->frere = frere;
	aux->fils = fils;

	return aux;
}

ptarbre ajout_colonne(char s[], ptarbre arbre)
{
	if (arbre != NULL) return arbre;

	int i = 0;
	ptarbre noeud_courant, suivant ;
	//cas i = 0
	noeud_courant = creer_noeud(s[i], (int)s[i], NULL, NULL);
	arbre = noeud_courant ;
	i++ ;
	// i : premiere lettre non traitée
	// noeux_courant : dernier maillon cree
	while(s[i] != '\0')
	{	
		suivant = creer_noeud(s[i], (int)s[i], NULL, NULL);
		noeud_courant->fils = suivant;
		noeud_courant->frere = NULL ;
		noeud_courant = suivant;
		i++;
	}

	//Ajout du '\0' à la fin du mot
	suivant = creer_noeud('\0', 256, NULL, NULL);
	noeud_courant->fils = suivant;
	noeud_courant->frere = NULL ;
	noeud_courant = suivant;


	return arbre;
}

ptarbre ajout(char s[], ptarbre arbre)
{
	if(arbre == NULL){
		arbre = ajout_colonne(s, arbre);
		return arbre;
	}
	if(s[0] == arbre->etiq && s[0] != '\0'){
		arbre->fils = ajout(&s[1], arbre->fils);
	} else {
		if(s[0] > arbre->etiq){
			arbre->frere = ajout(s, arbre->frere);
		} else if(s[0] < arbre->etiq) {
			ptarbre nouveau = creer_noeud(s[0], (int)s[0], arbre, NULL);
			ajout_colonne(&s[1], nouveau);
			return nouveau; 
		}
	}
	return arbre;
}


ptarbre init_arbre_ASCII(void)
{
	char c[1];
	c[0] = (char)0;
	ptarbre arbre = ajout(c, NULL);
	ptarbre racine = arbre;

	for (int i = 1; i < 128; i++)
	{
		c[0] = (char)i;
		ajout(c, arbre);
	}

	return racine;

}

bool estPresent(char s[], ptarbre arbre)
{
	if (arbre == NULL)
		return false;

	if (s[0] == arbre->etiq)
	{
		if (s[0] == '\0')
			return true;
		else
			return estPresent(&s[1], arbre->fils);
	}
	else
		return estPresent(s, arbre->frere);
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
			cout << "\\0" << endl;
		else
			cout << arbre->etiq;
		affichage(arbre->fils);
		affichage(arbre->frere);
	}
}

