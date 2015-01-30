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
#include "decompression.h"

#include "string.h"
#include "in_out.h"
#include "arbre.h"
#include "stats.h"

using namespace std;

unsigned char mot[100];

void testRecherche(ptarbre arbre){
    strcat((char*)mot, "b");
	cout << getCode(mot, arbre) << endl;
}

// void testLecture(){
//     reader("test.rtf");
// }

/*unsigned char * insertString(unsigned char * str, unsigned char c, int place){
    
    int length = strlen((char*)str);
    str = (unsigned char *) realloc(str,sizeof(unsigned char) * (length + 2));
    //strcpy((char *)str,(char *)tempC);
    if (str!= NULL) {
        for(int i = length +1; i >= 0; i--)
            if(i > place) str[i] = str[i-1];
            else str[i] = c;
    }

    return str;
}*/

void menu(void){
    cout << "1. Compresser un fichier" << endl;
    cout << "2. Décompresser un fichier" << endl;
    cout << "3. Quitter le programme" << endl;
}

int main(int argc, const char * argv[])
{

    //cout << "\033[2J\033[1;1H";
    switch(argc){
        case 1: 
            cout << "Cas 1 ! \n";
            break;
        case 2:
            cout << "Cas 2 :) \n";
            break;
        default:
            cout << "none";
    }
    // Affichage du menu :
    char fN[] = "reader.txt";
    //reader(fN);
    cout << endl;



    // Mise en place du chrono pour déterminer le temps d'execution
    typedef std::chrono::high_resolution_clock Clock;
    typedef std::chrono::milliseconds milliseconds;
    Clock::time_point t0 = Clock::now();
    
    
    const char * truc;
	ptarbre arbre = init_arbre_ASCII();

	cout << "init success" << endl;
    
    //cout << "Le dernier code : " << showCode() << endl;
    char fileName[] = "test2.txt";
    char out[] = "out.txt";
    char out_decomp[] = "out_decomp.txt";

    char * bidule = NULL;
    bidule = (char *)malloc(sizeof(unsigned char *) * 7);
    strcpy(bidule,"Hello ");



    ouvrir_fichier_entree(fileName);
    ouvrir_fichier_sortie(out);

    compress(arbre);

    fermer_fichiers();

    // decompress(out, out_decomp, arbre);

    
    // compareSize(fileName, out);
    //affichage(arbre);
    cout << "Le dernier code : " << showCode() << endl;

    // cout << "Code recherché : 4060 =  \"";
    // cout << searchCode(4000, arbre);
    // cout << "\""<< endl;
    
    Clock::time_point t1 = Clock::now();
    milliseconds ms = std::chrono::duration_cast<milliseconds>(t1 - t0);
    cout << "Temps d'exécution du programme : " << ms.count() << "ms\n";
    
    return 0;
}