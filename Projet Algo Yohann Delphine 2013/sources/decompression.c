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
 * @file decompression.c
 * @brief Module gerant l'algorithme de decompression.
 */


#include <stdio.h>
#include <stdlib.h>

#include "chaine_caracteres.h"
#include "dictionnaire.h"
#include "lecture_ecriture.h"
#include "decompression.h"


/** @brief Decompresse le fichier d'entree
 *
 * Decompresse le fichier d'entree en ecrivant les chaines de caracteres 
 * correspondant aux codes de compression dans le fichier de sortie.
 * @param dictionnaire  Dictionnaire intialisé par la table ASCII.
 * @return	void
 */
void decompresser (t_ptr_arbre dictionnaire) {
    unsigned char * mot_precedent = NULL;
    int code_lu;
    
    code_lu = lire_code_binaire ();
    mot_precedent = rechercher_mot (dictionnaire, code_lu);
    ecrire_texte (mot_precedent);
    
    while ((code_lu = lire_code_binaire ()) != 0) {
        unsigned char * mot_decode                  = NULL,
                      * mot_precedent_et_mot_decode = NULL;
        
        mot_decode = rechercher_mot (dictionnaire, code_lu);
        if (mot_decode == NULL) {
            mot_decode = copier_chaine (mot_precedent);
            mot_decode = ajouter_caractere (mot_decode, mot_precedent[0]);
        }
        
        ecrire_texte (mot_decode);
        
        free (mot_precedent_et_mot_decode);
        
        mot_precedent_et_mot_decode = copier_chaine (mot_precedent);
        mot_precedent_et_mot_decode = ajouter_caractere (mot_precedent_et_mot_decode, mot_decode[0]);
        
        if (DICTIONNAIRE_PLEIN == 0)
            ajouter_mot (dictionnaire, mot_precedent_et_mot_decode);
        
        free (mot_precedent_et_mot_decode);
        free (mot_precedent);
        
        mot_precedent = mot_decode;
    }
    
    free (mot_precedent);
}
