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
 * @file compression.cpp
 * @brief Module contenant l'algorithme de compression
 * 
 */

#include <iostream>
#include <stdio.h> // gestion de fichiers
#include <math.h>
#include "string.h"
#include <chrono>

#include "compression.h"
#include "arbre.h"
#include "in_out.h"

using namespace std;

// w = Nul;
//    tant que (lecture d'un caractère c) faire
//        si (w + c existe dans le dictionnaire) alors
//            w = w + c;
//        sinon
//            ajouter w + c au dictionnaire;
//            écrire le code de w;
//            w = c;
//        fin si
//    fin tant que
//    écrire le code de w;

static unsigned char w[10000] = {0};

void compress(ptarbre arbre)
{
    unsigned char c;
    int buffer = 0;
    typedef std::chrono::high_resolution_clock Clock;
    typedef std::chrono::milliseconds milliseconds;
    Clock::time_point t0 = Clock::now();

    buffer = lire_caractere ();

    while(buffer != EOF){     
        short i = 0;

        c = buffer;
        while (w[i] != '\0') {
            i++;
        }

        w[i] = c;

        if (getCode(w, arbre) > 0)
        {
            w[i] = c; 
        }
        else {
            if (showCode() == pow(2, show_NB_BITS_CODE()))
            { 
                change_NB_BITS_CODE();
                ajout(arbre, w);
                // passage de w+c a w
                w[i] = 0;

                int codeToWrite = getCode(w, arbre);
                ecrire_code_binaire (codeToWrite, 0);
                memset(w, 0, sizeof(w));
                w[0] = c;
            } else {

                ajout(arbre, w);
                // passage de w+c a w
                w[i] = 0;

                int codeToWrite = getCode(w, arbre);
                ecrire_code_binaire (codeToWrite, 0);
                memset(w, 0, sizeof(w));
                w[0] = c;
            }
        }
        buffer = lire_caractere ();
    }
    int codeToWrite = getCode(w, arbre);
    ecrire_code_binaire (codeToWrite, 1);

    Clock::time_point t1 = Clock::now();
    milliseconds ms = std::chrono::duration_cast<milliseconds>(t1 - t0);
    cout << "Temps d'exécution du programme : " << ms.count() << "ms\n";
}