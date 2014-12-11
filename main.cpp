//
//  main.cpp
//  projet_algo
//
//  Created by Olivier on 11/11/2014.
//  Copyright (c) 2014 Alex&Olivier. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "compression.h"

#include "string.h"
#include "in_out.h"
#include "arbre.h"

using namespace std;

unsigned char mot[100];

void testRecherche(ptarbre arbre){
    strcat((char*)mot, "b");
	cout << estPresent(mot, arbre) << endl;
}

// void testLecture(){
//     reader("test.rtf");
// }

int main(int argc, const char * argv[])
{
    const char * truc;
	ptarbre arbre = init_arbre_ASCII();

	cout << "init success" << endl;
    //testRecherche(arbre);
	//testLecture();

    // unsigned char s[2] = {'b', '\0'};
    // cout << estPresent(s, arbre) << endl; 

    compress(truc, truc,arbre);
    affichage(arbre);
    //affichage(arbre);
    return 0;
}