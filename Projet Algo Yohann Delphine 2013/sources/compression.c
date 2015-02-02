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
 * @file compression.c
 * @brief Module gerant l'algorithme de compression.
 */


#include <stdio.h>
#include <stdlib.h>

#include "chaine_caracteres.h"
#include "dictionnaire.h"
#include "lecture_ecriture.h"
#include "compression.h"


/** @brief Compresse le fichier d'entree
 *
 * Compresse le fichier d'entree en ecrivant les codes de compression dans le 
 * fichier de sortie.
 * @param dictionnaire  Dictionnaire intialisé par la table ASCII.
 * @return	void
 */
void compresser (t_ptr_arbre dictionnaire) {
    unsigned char * tampon       = NULL,
                  * caractere_lu = NULL;
    
    while ((caractere_lu = lire_caractere ()) != NULL) {
        unsigned char * tampon_et_caractere_lu = concatener_chaines (tampon, caractere_lu);
        
        if (rechercher_code (dictionnaire, tampon_et_caractere_lu) != 0) {
            free (tampon);
            free (caractere_lu);
            
            tampon = tampon_et_caractere_lu;
        }
        else {
            if (DICTIONNAIRE_PLEIN == 0)
                ajouter_mot (dictionnaire, tampon_et_caractere_lu);
            
            ecrire_code_binaire (rechercher_code (dictionnaire, tampon), 0);
            
            free (tampon);
            free (tampon_et_caractere_lu);
            
            tampon = caractere_lu;
        }
    }
    
    ecrire_code_binaire (rechercher_code (dictionnaire, tampon), 1);
    free (tampon);
}
