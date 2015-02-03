/**
 *
 * Polytech Marseille
 * Case 925 - 163, avenue de Luminy
 * 13288 Marseille CEDEX 9
 *
 * Ce fichier est l'oeuvre d'eleves de Polytech Marseille. Il ne peut etre
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 * Copyright (c) 2014 Alex&Olivier. All rights reserved.
 */

/**
 * @author LAGRANGE CETTO Alexandre <>
 * @author MARIN Olivier <olivier.marin@etu.univ-amu.fr>
 *
 * @todo
 */

/**
 * @file stats.cpp
 * @brief Module calculant le taux de compression
 * 
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>

using namespace std;

static long entry_fileSize = 0;


// Fonctions de statistiques

// Calcul la taille du fichier passer en paramètre
long fileSize(const char * fileName){
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
    //cout << lSize;
    return lSize;
}


//Compare la taille des fichiers et renvoie le pourcentage de compression
void compareSize(const char * before, const char * after){
    long fileSize1 = fileSize(before);
    long fileSize2 = fileSize(after);

    cout << "---------------------------- STATS ----------------------------" << endl;
    cout << "|    Fichier à compresser    |    " << fileSize1 << " octets, soit : " << fileSize1/1024 << " Ko."<< endl;
    cout << "|    Fichier compressé       |    " << fileSize2 << " octets, soit : " << fileSize2/1024 << " Ko." << endl;
    cout << setprecision (4);
    cout << "|    Taux de compression     |    " << ((float)fileSize2/(float)fileSize1) * 100 << "%"<< endl;
    cout << "---------------------------------------------------------------" << endl;
    cout << endl;
}

void setEntryFileSize(long val)
{
    entry_fileSize = val;
}

void loadBar(long position)
{
    long nb_octet = entry_fileSize/8;
    long pourcentage  = nb_octet/20;
    if (!(position%(long)pourcentage))
        cout << "=";
}