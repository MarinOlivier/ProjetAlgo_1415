//
//  arbre.h
//  projet_algo
//
//  Created by Olivier on 11/11/2014.
//  Copyright (c) 2014 Alex&Olivier. All rights reserved.
//


#ifndef projet_algo_arbre_h
#define projet_algo_arbre_h

// Description de nos arbres, avec une lettre, un frère et un fils
typedef struct arbre{
    char etiq;
    int code;
    struct arbre * frere;
    struct arbre * fils;
} noeud, *ptarbre  ;


ptarbre creer_arbre();
ptarbre creer_noeud(unsigned char etiq, int code, ptarbre frere, ptarbre fils);
void ajout(ptarbre arbre, unsigned char s[]);
ptarbre init_arbre_ASCII(void);
int getCode(unsigned char s[], ptarbre arbre);
void affichage(ptarbre arbre);
int showCode(void);

#endif