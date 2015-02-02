
#ifndef CHAINE_CARACTERES__H
#define CHAINE_CARACTERES__H


/* Prototypes des fonctions */
extern unsigned char * creer_chaine_vide ();

extern unsigned char * ajouter_caractere (unsigned char * chaine, unsigned char caractere);

extern unsigned char * inserer_caractere (unsigned char * chaine, unsigned char caractere, int indice);

extern unsigned char * copier_chaine (unsigned char * chaine);

extern unsigned char * concatener_chaines (unsigned char * chaine1, unsigned char * chaine2);


#endif /* CHAINE_CARACTERES__H */
