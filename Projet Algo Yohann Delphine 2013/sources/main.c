/**
 *
 * Polytech Marseille
 * Case 925 - 163, avenue de Luminy
 * 13288 Marseille CEDEX 9
 *
 * Ce fichier est l'oeuvre d'eleves de Polytech Marseille. Il ne peut etre
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 */

/**
 * @author BURNOTTE Delphine <delphine.burnotte@etu.univ-amu.fr>
 * @author DUFOUR Yohann <yohann.dufour@etu.univ-amu.fr>
 *
 * @version 0.0.2 / 19-01-2013
 * @todo
 */


/**
 * @file main.c
 * @brief Module principal
 * 
 * Programme permettant la compression et la decompression d'un fichier.
 * Le programme de compression lit le fichier texte donne en entree et ecrit les 
 * code de compression au format binaire dans le fichier de sortie.
 * Le programme de decompression lit le fichier binaire donne en entree et 
 * decompression dans le fichier texte de sortie.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "dictionnaire.h"
#include "lecture_ecriture.h"
#include "compression.h"
#include "decompression.h"


static void demander_nom_fichiers (char * fichier_entree, char * fichier_sortie) {
    printf ("Nom du fichier d'entree : ");
    fgets (fichier_entree, 256, stdin);
    fichier_entree[strlen (fichier_entree) - 1] = '\0';
    printf ("Nom du fichier de sortie : ");
    fgets (fichier_sortie, 256, stdin);
    fichier_sortie[strlen (fichier_sortie) - 1] = '\0';
    printf ("\n");
}


static void afficher_statistiques (int compression, double temps_debut, double temps_fin) {
    long taille_entree = recuperer_taille_fichier_entree ();
    long taille_sortie = recuperer_taille_fichier_sortie ();
    long pourcentage = (taille_entree - taille_sortie)/(double)taille_entree * 100;
    double temps = (double)((temps_fin-temps_debut)/CLOCKS_PER_SEC);
    
    if (compression)
        printf ("Fichier compresse à %ld%c\n", pourcentage, '%');
    printf ("Fichier genere en %f secondes\n", temps);
}


int main (int argc, char * argv[]) {
    t_ptr_arbre dictionnaire = NULL;
    unsigned int choix = 1;
    char fichier_entree[256], fichier_sortie[256];
    double temps_debut = 0.0, temps_fin = 0.0;
    
    printf ("\n\n");
    printf (" ---------- Compression et Decompression LZW ---------------\n\n");
    
    if (argc == 2 && strcmp ("h", argv[1]) == 0) {
        printf ("\n\n");
        printf (" lzw <c|d|h> <fichier_d_entree> <fichier_de_sortie>\n");
        printf (" \tc : compression\n");
        printf (" \td : decompression\n");
        printf (" \th : affichage de l'aide\n");
        printf (" \tfichier_d_entree : nom du fichier d'entree\n");
        printf (" \tfichier_de_sortie : nom du fichier de sortie\n");
        printf ("\n\n");
        return EXIT_SUCCESS;
    }
    else if (argc == 4) {
        if (strcmp ("c", argv[1]) == 0) {
            printf ("COMPRESSION\n");
            temps_debut = (double)clock ();
            
            dictionnaire = initialiser_dictionnaire ();
            ouvrir_fichier_entree (argv[2], 0);
            ouvrir_fichier_sortie (argv[3], 1);
            compresser (dictionnaire);
            
            temps_fin = (double)clock ();
            afficher_statistiques (1, temps_debut, temps_fin);
            fermer_fichiers ();
            detruire_dictionnaire (dictionnaire);
        }
        else if (strcmp ("d", argv[1]) == 0) {
            printf ("DECOMPRESSION\n");
            temps_debut = (double)clock ();
            dictionnaire = initialiser_dictionnaire ();
            ouvrir_fichier_entree (argv[2], 1);
            ouvrir_fichier_sortie (argv[3], 0);
            decompresser (dictionnaire);
            temps_fin = (double)clock ();
            afficher_statistiques (0, temps_debut, temps_fin);
            fermer_fichiers ();
            detruire_dictionnaire (dictionnaire);
        }
        
        printf ("\n\n");
        return EXIT_SUCCESS;
    }
    
    /* Menu si aucun argument n'a ete donne en ligne de commande */
    while (choix != 0) {
        printf ("\n\n");
        printf (" \t1 - Compresser un fichier (fichier texte)\n");
        printf (" \t2 - Decompresser un fichier (fichier binaire)\n");
        printf (" \t3 - Affichage du dernier dictionnaire utilise\n");
        printf (" \t0 - Quitter le programme\n");
        printf (" Votre choix : ");
        scanf ("%d", &choix);
        fgets (fichier_entree, 256, stdin); /* Recupere le caractere \n lu apres le choix */
        printf ("\n");
        
        switch (choix) {
            case 1 :
                printf ("COMPRESSION\n");
                if (dictionnaire != NULL)
                    detruire_dictionnaire (dictionnaire);
                
                temps_debut = (double)clock ();
                
                dictionnaire = initialiser_dictionnaire ();
                demander_nom_fichiers (fichier_entree, fichier_sortie);
                ouvrir_fichier_entree (fichier_entree, 0);
                ouvrir_fichier_sortie (fichier_sortie, 1);
                compresser (dictionnaire);
                
                temps_fin = (double)clock ();
                afficher_statistiques (1, temps_debut, temps_fin);
                fermer_fichiers ();
                break;
            case 2 :
                printf ("DECOMPRESSION\n");
                if (dictionnaire != NULL)
                    detruire_dictionnaire (dictionnaire);
                
                temps_debut = (double)clock ();
                
                dictionnaire = initialiser_dictionnaire ();
                demander_nom_fichiers (fichier_entree, fichier_sortie);
                ouvrir_fichier_entree (fichier_entree, 1);
                ouvrir_fichier_sortie (fichier_sortie, 0);
                decompresser (dictionnaire);
                
                temps_fin = (double)clock ();
                afficher_statistiques (0, temps_debut, temps_fin);
                fermer_fichiers ();
                break;
            case 3 :
                printf ("AFFICHAGE DU DICTIONNAIRE\n");
                if (dictionnaire != NULL)
                    afficher_dictionnaire (dictionnaire, 0);
                break;
            default : choix = 0; break;
        }
    }
    
    printf ("\n");
    
    return EXIT_SUCCESS;
}
