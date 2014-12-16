//
//  stats.cpp
//  projet_algo
//
//  Created by Olivier on 15/12/2014.
//  Copyright (c) 2014 Alex&Olivier. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;


// Fonctions de statistiques

// Calcul la taille du fichier passer en paramètre
double fileSize(const char * fileName){
    FILE * pFile;
    long lSize;
    //char * buffer;
    //size_t result; // <-- inutile pour le moment

    pFile = fopen (fileName, "rb");
    if (pFile==NULL) {fputs ("File error",stderr); exit (1);}

    // obtain file size:
    fseek (pFile , 0 , SEEK_END);
    lSize = ftell (pFile);
    rewind (pFile);
    fclose (pFile);
    //free (buffer);
    cout << lSize;
    return lSize;
}


//Compare la taille des fichiers et renvoie le pourcentage de compression
void compareSize(const char * before, const char * after){
    double fileSize1 = fileSize(before);
    double fileSize2 = fileSize(after);
    //cout << fileSize1 << ", " << fileSize2 << endl;
    //cout << fileSize2/fileSize1 * 100 << endl;
}
