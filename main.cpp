//
//  main.cpp
//  projet_algo
//
//  Created by Olivier on 11/11/2014.
//  Copyright (c) 2014 Alex&Olivier. All rights reserved.
//

#include <iostream>

#include "arbre.h"

using namespace std;

int main(int argc, const char * argv[])
{
	ptarbre arbre = init_arbre_ASCII();
	char c[2];
	c[0]='a';
	c[1]='\0';
	bool a = rechercher(c, arbre);
	cout << a << endl;
	
	affichage(arbre);
    return 0;
}