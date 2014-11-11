//
//  arbre.cpp
//  projet_algo
//
//  Created by Olivier on 11/11/2014.
//  Copyright (c) 2014 Alex&Olivier. All rights reserved.
//

#include <iostream>
#include "arbres.h"

using namespace std;

ptarbre creer_arbre()
{
	ptarbre arbre = (ptarbre)malloc(sizeof(maillon));
	return arbre;
}

ptarbre creer_noeud(char etiq, int code, ptarbre frere, ptarbre fils)
{
	ptarbre aux;
	aux = (ptarbre)malloc(sizeof(maillon));
	aux->etiq = etiq;
	aux->code = code;
	aux->frere = frere;
	aux->fils = fils;

	return aux;
}