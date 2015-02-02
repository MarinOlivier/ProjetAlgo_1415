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
 * @file chaine_caracteres.c
 * @brief Module gerant les chaines de caracteres du dictionnaire.
 */


#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "chaine_caracteres.h"

/** @brief Création d'une chaine de caracteres vide.
 * @return	Retourne la chaide de caracteres vide.
 */
unsigned char * creer_chaine_vide () {
    unsigned char * chaine = malloc (sizeof (unsigned char));
    
    assert (chaine != NULL);
    chaine[0] = '\0';
    
    return chaine;
}

/** @brief Ajoute un caractere a la fin de la chaine.
 *
 * On realloue dynamiquement la chaine de caracteres afin d'y rajouter un 
 * caractere.
 * @param chaine  Chaine de caracteres.
 * @param caractere  Caractere que l'on ajoute a la chaine.
 * @return	Retourne la nouvelle chaine.
 */
unsigned char * ajouter_caractere (unsigned char * chaine, unsigned char caractere) {
    int longueur_chaine = strlen ((char *)chaine);
    
    chaine = realloc (chaine, sizeof (unsigned char) * (longueur_chaine + 2));
    assert (chaine != NULL);
    chaine[longueur_chaine]   = caractere;
    chaine[longueur_chaine+1] = '\0';
    
    return chaine;
}

/** @brief Insere a un indice donne, un caractere dans la chaine.
 *
 * On realloue dynamiquement la chaine de caracteres afin d'y inserer a un 
 * indice donne, un caractere.
 * @param chaine  Chaine de caracteres.
 * @param caractere  Caractere que l'on souhaite inserer dans la chaine de 
 * caracteres.
 * @param indice  Indice d'insertion du caractere.
 * @return	Retourne la chaine de caracteres avec le nouveau caractere insere.
 */
unsigned char * inserer_caractere (unsigned char * chaine, unsigned char caractere, int indice) {
    int i, longueur_chaine = strlen ((char *)chaine);
    
    chaine = realloc (chaine, sizeof (unsigned char) * (longueur_chaine + 2));
    assert (chaine != NULL);
    
    for (i = longueur_chaine + 1; i >= 0; i--) {
        if (i > indice)
            chaine[i] = chaine[i-1];
        else {
            chaine[i] = caractere;
            break;
        }
    }
    
    return chaine;
}

/** @brief Copie la chaine de caracteres.
 *
 * Cree une nouvelle chaine de caracateres identique a la chaine de caracteres donnee.
 * @param chaine  Chaine de caracteres que l'on souhaite copier.
 * @return	Retourne une nouvelle chaine de caracteres identique a la premiere 
 * chaine de caracteres.
 */
unsigned char * copier_chaine (unsigned char * chaine) {
    int longueur_chaine = strlen ((char *)chaine);
    unsigned char * copie = NULL;
    
    copie = malloc (sizeof (unsigned char) * (longueur_chaine + 1));
    assert (copie != NULL);
    while (longueur_chaine >= 0) {
        copie[longueur_chaine] = chaine[longueur_chaine];
        longueur_chaine--;
    }
    
    return copie;
}

/** @brief Concatene deux chaines de caracteres.
 *
 * Alloue dynamiquement une nouvelle chaine de caracteres qui est la 
 * concatenation des deux chaines de caracteres, en parametres.
 * @param chaine1  Premiere chaine de caracteres a concatener.
 * @param chaine2  Seconde chaine de caracteres a concatener.
 * @return	Retourne la concatenation des deux chaines de caracteres.
 */
unsigned char * concatener_chaines (unsigned char * chaine1, unsigned char * chaine2) {
    unsigned char * chaine12;
    int i, n1 = 0, n2 = 0;
    
    if (chaine1 != NULL)
        n1 = strlen ((char *)chaine1);
    if (chaine2 != NULL)
        n2 = strlen ((char *)chaine2);
    
    chaine12 = malloc (sizeof (unsigned char) * (n1 + n2 + 1));
    assert (chaine12 != NULL);
    for (i = 0; i < n1; i++)
        chaine12[i] = chaine1[i];
    for (i = n1; i <= n1+n2; i++)
        chaine12[i] = chaine2[i-n1];
    
    return chaine12;
}
