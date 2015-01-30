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
#include <unistd.h>    /* for getopt */

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

void menu(int n){
    char c;
    ptarbre arbre = init_arbre_ASCII();
    cout << "\033[2J\033[1;1H";
    char fileName[40] = {'\0'};
    char out[40] = {'\0'};
    // Affichage du menu :
    char fN[] = "reader.txt";
    //reader(fN);
    if(!n){
        cout << "\033[2J\033[1;1H";
        cout << endl;
        cout << "Choisissez la tâche à effectuer : "<< endl;
        cout << "1. Compresser un fichier" << endl;
        cout << "2. Décompresser un fichier" << endl;
        cout << "0. Quitter le programme" << endl;
        cin >> n;
    }
    switch(n){
        case 0: 
            cout << "A bientôt"<< endl;
            exit(EXIT_SUCCESS);

        case 1:
            cout << "\033[2J\033[1;1H";
            cout << "Entrez le nom du fichier à compresser : ";
            cin >> fileName;
            if((fileName[0] == '\0') || !fichier_existe(fileName)){
                cout << "Le fichier n'existe pas, retour au début" << endl;
                return menu(1);
            }

            cout << "Entrez le nom du fichier de sortie : ";
            cin >> out;
            if((out[0] != '\0') && fichier_existe(out)){
                cout << "Le fichier existe déjà, O pour l'utiliser quand même, N pour retourner au début" << endl;
                cin >> c;
                if (c == 'O' || c == 'o'){
                    ouvrir_fichier_entree(fileName);
                    ouvrir_fichier_sortie(out);
                    compress(arbre);
                    fermer_fichiers();
                    cout << "COMPRESS" << endl;
                } else return menu(1);    
            } else if(fileName[0] == '\0'){
                cout << "Nom de fichier invalide" << endl;
                return menu(1);
            } else {
                ouvrir_fichier_entree(fileName);
                ouvrir_fichier_sortie(out);
                compress(arbre);
                fermer_fichiers();
                cout << "COMPRESS" << endl;
            }
            break;

        case 2:
            cout << "\033[2J\033[1;1H";
            cout << "Entrez le nom du fichier à décompresser : ";
            cin >> fileName;
            cout << endl;
            if((fileName[0] == '\0') || !fichier_existe(fileName)){
                cout << "Le fichier n'existe pas, retour au début" << endl;
                return menu(1);
            }

            cout << "Entrez le nom du fichier de sortie : ";
            cin >> out;
            cout << endl;
            if((out[0] != '\0') && fichier_existe(out)){
                cout << "Le fichier existe déjà, O pour l'utiliser quand même, N pour retourner au début" << endl;
                cin >> c;
                if (c == 'O' || c == 'o')
                {
                    ouvrir_fichier_entree(fileName);
                    ouvrir_fichier_sortie(out);
                    decompress(arbre);
                    fermer_fichiers();

                    cout << "DECOMPRESS" << endl;
                }
                else return menu(1);    
            } else if(fileName[0] == '\0'){
                cout << "Nom de fichier invalide" << endl;
                return menu(1);
            } else {
                ouvrir_fichier_entree(fileName);
                ouvrir_fichier_sortie(out);
                decompress(arbre);
                fermer_fichiers();
                cout << "DECOMPRESS" << endl;
            }
            break;

        default:
            menu(0);
    }
}

int main(int argc, char * argv[])
{

    // Mise en place du chrono pour déterminer le temps d'execution
   /*typedef std::chrono::high_resolution_clock Clock;
    typedef std::chrono::milliseconds milliseconds;
    Clock::time_point t0 = Clock::now();*/
    
    
    const char * truc;
	

    char c = '\0';
    char opt;
    if(argc == 1)                       // Programme lancé sans arguments, on affiche le menu de saisie
        menu(0);
    else {                              // Arguments présents, on enchaine
        ptarbre arbre = init_arbre_ASCII();
        while ((opt = getopt(argc, argv, ":cd:h")) != -1) {
            switch(opt){
                case 'c':
                    if((argv[2][0] == '\0') || !fichier_existe((char*)argv[2])){
                        cout << "Le fichier n'existe pas, arrêt du programme" << endl;
                        break;
                    }

                    if((argv[3][0] != '\0') && fichier_existe(argv[3])){
                        cout << "Le fichier existe déjà, O pour l'utiliser quand même, N pour arrêter le programme" << endl;
                        cin >> c;
                        if (c == 'O' || c == 'o'){
                            ouvrir_fichier_entree(argv[2]);
                            ouvrir_fichier_sortie(argv[3]);
                            compress(arbre);
                            fermer_fichiers();
                            cout << "COMPRESS" << endl;
                        } else break;    
                    } else if(argv[2][0] == '\0'){
                        cout << "Nom de fichier invalide" << endl;
                        break;
                    } else {
                        ouvrir_fichier_entree(argv[2]);
                        ouvrir_fichier_sortie(argv[3]);
                        compress(arbre);
                        fermer_fichiers();
                        cout << "COMPRESS" << endl;
                    }
                    break;
                case 'd':
                    if((argv[2][0] == '\0') || !fichier_existe(argv[2])){
                        cout << "Le fichier n'existe pas, arrêt du programme" << endl;
                        break;
                    }

                    if((argv[3][0] != '\0') && fichier_existe(argv[3])){
                        cout << "Le fichier existe déjà, O pour l'utiliser quand même, N pour arrêter le programme" << endl;
                        cin >> c;
                        if (c == 'O' || c == 'o')
                        {
                            ouvrir_fichier_entree(argv[2]);
                            ouvrir_fichier_sortie(argv[3]);
                            decompress(arbre);
                            fermer_fichiers();
                            cout << "DECOMPRESS" << endl;
                        }
                        else break;    
                    } else if(argv[2][0] == '\0'){
                        cout << "Nom de fichier invalide" << endl;
                        break;
                    } else {
                        ouvrir_fichier_entree(argv[2]);
                        ouvrir_fichier_sortie(argv[3]);
                        decompress(arbre);
                        fermer_fichiers();
                        cout << "DECOMPRESS" << endl;
                    }
                    break;
                case 'h':
                    cout << "\033[2J\033[1;1H";
                    reader("help.txt");
                    break;
                default:
                    cout << "Erreur ! "; 
                    break;
            }
        }
    }

    

    return 0;
}