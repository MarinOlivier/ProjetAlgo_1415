//
//  main.cpp
//  projet_algo
//
//  Created by Olivier on 11/11/2014.
//  Copyright (c) 2014 Alex&Olivier. All rights reserved.
//

#include <iostream>
#include <stdio.h>

#include "string.h"

#include "arbre.h"

using namespace std;

unsigned char mot[100];

int main(int argc, const char * argv[])
{
	ptarbre arbre = init_arbre_ASCII();

	cout << "ini success" << endl;

	affichage(arbre);

	strcat((char*)mot, "b");

	cout << estPresent(mot, arbre) << endl;
    return 0;
}