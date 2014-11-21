//
//  arbre.cpp
//  projet_algo
//
//  Created by Olivier on 11/11/2014.
//  Copyright (c) 2014 Alex&Olivier. All rights reserved.
//

#include <iostream>
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

ptarbre ajout_ligne(char c, ptarbre arbre)
{
	if(arbre->frere == NULL)
	{
		ptarbre nouveau = creer_noeud(c, (int)c, NULL, NULL );
		arbre->frere = nouveau;
		return nouveau;
	}
	else
	{
		ajout_ligne(c, arbre->frere);
	}

	return arbre;
	
}

ptarbre init_arbre_ASCII(void)
{
	ptarbre arbre = creer_arbre();

	for (int i = 0; i < 256; i++)
	{
		ajout_ligne((char)i, arbre);
	}

	return arbre;

}