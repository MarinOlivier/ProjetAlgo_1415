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
 * @file dictionnaire.c
 * @brief Module gerant le dictionnaire necessaire aux algorithmes de 
 * compression et de decompression.
 */


#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chaine_caracteres.h"
#include "dictionnaire.h"


/* Variable globale qui indique si le dictionnaire est plein */
int DICTIONNAIRE_PLEIN = 0;


/** @brief Fonction primaire qui renvoie le caractere du noeud.
 * @param noeud  Noeud dont on veut recuperer le caractere.
 * @return  Retourne le caractere du noeud.
 */
unsigned char caractere (t_ptr_arbre noeud) {
    assert (noeud != NULL);
    return noeud->caractere;
}

/** @brief Fonction primaire qui renvoie le code du noeud.
 * @param noeud  Noeud dont on veut recuperer le code.
 * @return  Retourne le code du noeud.
 */
unsigned int code (t_ptr_arbre noeud) {
    assert (noeud != NULL);
    return noeud->code;
}

/** @brief Fonction primaire qui renvoie le fils du noeud.
 * @param noeud  Noeud dont on veut recuperer le fils.
 * @return  Retourne le fils du noeud.
 */
t_ptr_arbre fils (t_ptr_arbre noeud) {
    assert (noeud != NULL);
    return noeud->fils;
}

/** @brief Fonction primaire qui renvoie le frere du noeud.
 * @param noeud  Noeud dont on veut recuperer le frere.
 * @return  Retourne le frere du noeud.
 */
t_ptr_arbre frere (t_ptr_arbre noeud) {
    assert (noeud != NULL);
    return noeud->frere;
}

/** @brief Fonction primaire qui teste si le noeud est le pointeur NULL.
 * @param noeud  Noeud teste.
 * @return  Retourne le booleen correspondant a la reponse.
 */
static int est_vide (t_ptr_arbre noeud) {
    return (noeud == NULL) ? 1 : 0;
}

/** @brief Fonction qui permet d'assigner un code au noeud.
 * @param noeud  Noeud auquel on veut assigner le code.
 * @param init  Booleen qui, lorsqu'il vaut 1, reiniatialise les codes.
 * @return void
 */
static void assigner_code (t_ptr_arbre noeud, int init) {
    static unsigned int code = 255;
    static int code_max;
    
    if (init) {
        code = 255;
        code_max = (int)pow (2, NB_BITS_CODE) - 1;
        DICTIONNAIRE_PLEIN = 0;
    }
    
    assert (noeud != NULL);
    assert (DICTIONNAIRE_PLEIN == 0);
    
    noeud->code = code;
    
    /* Fin de la phase d'initialisation du dictionnaire */
    if (code == 1)
        code = 260;
    /* Phase d'initialisation du dictionnaire */
    else if (code <= 255)
        code--;
    /* Phase d'ajout de mot */
    else
        code++;
    
    if (code >= code_max)
        DICTIONNAIRE_PLEIN = 1;
}

/** @brief Fonction qui change le caractere contenu dans un noeud.
 * @param noeud  Noeud dont on veut changer le caractere.
 * @param caractere  Caractere par lequel on va remplacer le caractere precedent.
 * @return  void
 */
static void modifier_caractere (t_ptr_arbre noeud, unsigned char caractere) {
    assert (noeud != NULL);
    noeud->caractere = caractere;
}

/** @brief Fonction qui change le fils d'un noeud.
 * @param noeud  Noeud dont on veut changer le fils.
 * @param fils  Fils par lequel on va remplacer le fils precedent.
 * @return  void
 */
static void modifier_fils (t_ptr_arbre noeud, t_ptr_arbre fils) {
    assert (noeud != NULL);
    noeud->fils = fils;
}

/** @brief Fonction qui change le frere d'un noeud.
 * @param noeud  Noeud dont on veut changer le frere.
 * @param frere  Frere par lequel on va remplacer le frere precedent.
 * @return  void
 */
static void modifier_frere (t_ptr_arbre noeud, t_ptr_arbre frere) {
    assert (noeud != NULL);
    noeud->frere = frere;
}

/** @brief Fonction qui cree un noeud.
 * @param caractere  Caractere que l'on va placer dans le noeud.
 * @param fils  Fils du noeud que l'on cree.
 * @param frere  Frere du noeud que l'on cree.
 * @param init  Booleen qui, lorsqu'il vaut 1, reiniatialise les codes.
 * @return  Retourne le noeud cree.
 */
static t_ptr_arbre creer_noeud (unsigned char caractere, t_ptr_arbre fils, t_ptr_arbre frere, int init) {
    t_ptr_arbre noeud;
    noeud = (t_ptr_arbre)malloc (sizeof (t_arbre));
    assert (noeud != NULL);
    
    modifier_caractere (noeud, caractere);
    modifier_fils      (noeud, fils);
    modifier_frere     (noeud, frere);
    assigner_code      (noeud, init);
    
    return noeud;
}


/** @brief Fonction qui initialise le dictionnaire avec les codes de la table 
 * ASCII.
 * @return  Retourne l'arbre (dictionnaire) rempli avec les 255 codes de la 
 * table ASCII.
 */
t_ptr_arbre initialiser_dictionnaire () {
    t_ptr_arbre arbre = NULL;
    unsigned char caractere = 255;
    
    arbre = creer_noeud (caractere, NULL, arbre, 1);
    for (caractere = 254; caractere > 0; caractere--)
        arbre = creer_noeud (caractere, NULL, arbre, 0);
    
    return arbre;
}

/** @brief Fonction qui detruit le dictionnaire.
 * @param dictionnaire  Dictionnaire a detruire.
 * @return  void
 */
void detruire_dictionnaire (t_ptr_arbre dictionnaire) {
    t_ptr_arbre noeud = dictionnaire;
    
    if (!est_vide (fils (noeud)))
        detruire_dictionnaire (fils (noeud));
    
    if (!est_vide (frere (noeud)))
        detruire_dictionnaire (frere (noeud));
    
    free (noeud);
}


/** @brief Parcours les noeuds de l'arbre afin d'afficher toutes les chaines de
 * caracteres du dictionnaire.
 * @param noeud  Noeud a parcourir.
 * @param chaine  Chaine de caracteres parcourue depuis la racine de l'arbre.
 * @param afficher_table_ascii  Booleen indiquant si l'on affiche ou non la 
 * table ASCII.
 * @return  void
 */
static void parcours (t_ptr_arbre noeud, unsigned char * chaine, int afficher_table_ascii) {
    unsigned char * copie = copier_chaine (chaine);
    chaine = ajouter_caractere (chaine, caractere (noeud));
    
    if (afficher_table_ascii || (!afficher_table_ascii && code (noeud) > 255))
        printf ("%s %d\n", chaine, code (noeud));
    
    if (!est_vide (fils (noeud)))
        parcours (fils (noeud), chaine, afficher_table_ascii);
    else
        free (chaine);
    
    if (!est_vide (frere (noeud)))
        parcours (frere (noeud), copie, afficher_table_ascii);
    else
        free (copie);
}

/** @brief Affiche le dictionnaire.
 * @param dictionnaire  Dictionnaire a afficher.
 * @param afficher_table_ascii  Booleen indiquant si l'on affiche ou non la 
 * table ASCII.
 * @return  void
 */
void afficher_dictionnaire (t_ptr_arbre dictionnaire, int afficher_table_ascii) {
    unsigned char * chaine = creer_chaine_vide ();
    parcours (dictionnaire, chaine, afficher_table_ascii);
}


/** @brief Recherche un mot dans le dictionnaire a partir de son code.
 * @param dictionnaire  Dictionnaire dans lequel on recherche le mot.
 * @param code_mot  Code du mot a rechercher.
 * @return  Retourne le pointeur NULL si le code n'est pas trouvé, sinon le mot
 * correspondant au code.
 */
unsigned char * rechercher_mot (t_ptr_arbre dictionnaire, unsigned int code_mot) {
    t_ptr_arbre noeud = dictionnaire;
    
    if (code (noeud) == code_mot) {
        unsigned char * fin_mot;
        fin_mot = ajouter_caractere (creer_chaine_vide (), caractere (noeud));
        
        return fin_mot;
    }
    else {
        unsigned char * chaine = NULL;
        
        if (!est_vide (fils (noeud)))
            chaine = rechercher_mot (fils (noeud), code_mot);
        
        if (chaine == NULL && !est_vide (frere (noeud)))
            return rechercher_mot (frere (noeud), code_mot);
        
        if (chaine != NULL)
            chaine = inserer_caractere (chaine, caractere (noeud), 0);
        
        return chaine;
    }
}


/** @brief Recherche un code dans le dictionnaire a partir du mot.
 * @param dictionnaire  Dictionnaire dans lequel on recherche le code.
 * @param chaine  Mot a rechercher.
 * @return  Retourne le code 0 si le mot n'est pas trouvé, sinon le code
 * correspondant au mot.
 */
unsigned int rechercher_code (t_ptr_arbre dictionnaire, unsigned char * chaine) {
    t_ptr_arbre noeud = dictionnaire;
    
    if (est_vide (dictionnaire))
        return 0;
    else if (caractere (noeud) == chaine[0]) {
        if (strlen ((char *)chaine) == 1)
            return code (noeud);
        else
            return rechercher_code (fils (noeud), &chaine[1]);
    }
    else {
        if (caractere (noeud) > chaine[0])
            return 0;
        else
            return rechercher_code (frere (noeud), chaine);
    }
}


/** @brief Cree de fils en fils les noeuds contenant les caracteres a ajouter.
 * @param chaine  Chaine de caracteres contenant les caracteres a ajouter.
 * @return  Retourne le pere principal de la suite des fils.
 */
static t_ptr_arbre creer_fils_cascade (unsigned char * chaine) {
    int i;
    t_ptr_arbre noeud = NULL;
    
    for (i = strlen((char *)chaine) - 1; i >= 0; i--)
        noeud = creer_noeud (chaine[i], noeud, NULL, 0);
    
    return noeud;
}

/** @brief Ajoute un mot dans le dictionnaire.
 * @param dictionnaire  Dictionnaire dans lequel on ajoute le mot.
 * @param chaine  Mot a ajouter.
 * @return  Retourne le dictionnaire avec le nouveau mot ajoute.
 */
t_ptr_arbre ajouter_mot (t_ptr_arbre dictionnaire, unsigned char * chaine) {
    if (chaine[0] == '\0')
        return dictionnaire;
    else if (est_vide (dictionnaire))
        return creer_fils_cascade (chaine);
    else {
        t_ptr_arbre noeud = dictionnaire;
        
        if (caractere (noeud) > chaine[0])
            noeud = creer_noeud (chaine[0], creer_fils_cascade (&chaine[1]), noeud, 0);
        else if (caractere (noeud) < chaine[0])
            modifier_frere (noeud, ajouter_mot (frere (noeud), chaine));
        else
            modifier_fils (noeud, ajouter_mot (fils (noeud), &chaine[1]));
        
        return noeud;
    }
}
