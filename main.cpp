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
	while(arbre->frere != NULL)
	{
		cout << arbre->etiq << endl;
		arbre = arbre->frere;
	}	
    return 0;
}