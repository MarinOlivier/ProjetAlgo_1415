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
#include <ctime>
#include <chrono>
#include "compression.h"

#include "string.h"
#include "in_out.h"
#include "arbre.h"
#include "stats.h"

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
    // Mise en place du chrono pour déterminer le temps d'execution
    typedef std::chrono::high_resolution_clock Clock;
    typedef std::chrono::milliseconds milliseconds;
    Clock::time_point t0 = Clock::now();
    
    
    const char * truc;
	ptarbre arbre = init_arbre_ASCII();

	cout << "init success" << endl;
    //testRecherche(arbre);
	//testLecture();

    // unsigned char s[2] = {'b', '\0'};
    //affichage(arbre);
    cout << "Le dernier code : " << showCode() << endl;
    char fileName[] = "/Users/alex/developper/pa1415/test.txt";
    char out[] = "/Users/alex/developper/pa1415/out.txt";
    compress(fileName, out, arbre);
    //cout << "Taille de fichier : " << fileSize(fileName) << " octets" << endl;
    //compareSize(truc, truc);
    
   // Boucle lol pour voir le temps d'exécution du programme
   short k = 0;
   for (int i = 0; i < 10000; i++)
       for (int j = 0; j < 10000; j++)
           k++;
    
    Clock::time_point t1 = Clock::now();
    milliseconds ms = std::chrono::duration_cast<milliseconds>(t1 - t0);
    cout << "Temps d'exécution du programme : " << ms.count() << "ms\n";
    
    return 0;
}