
#ifndef DICTIONNAIRE__H
#define DICTIONNAIRE__H

/* Definition des constantes */
#define NB_BITS_CODE 11

/* Structure de données du dictionnaire : arbre lexicographique */
typedef struct t_arbre {
    unsigned char caractere;
    unsigned int  code;
    struct t_arbre * fils;
    struct t_arbre * frere;
} t_arbre, * t_ptr_arbre;


/* Prototypes des fonctions */
extern unsigned char caractere (t_ptr_arbre noeud);
extern unsigned int  code      (t_ptr_arbre noeud);
extern t_ptr_arbre   fils      (t_ptr_arbre noeud);
extern t_ptr_arbre   frere     (t_ptr_arbre noeud);

extern t_ptr_arbre initialiser_dictionnaire ();
void               detruire_dictionnaire    (t_ptr_arbre dictionnaire);

extern void afficher_dictionnaire (t_ptr_arbre dictionnaire, int afficher_table_ascii);

extern unsigned char * rechercher_mot (t_ptr_arbre dictionnaire, unsigned int code_mot);

extern unsigned int rechercher_code (t_ptr_arbre dictionnaire, unsigned char * chaine);

extern t_ptr_arbre ajouter_mot (t_ptr_arbre dictionnaire, unsigned char * chaine);


#endif /* DICTIONNAIRE__H */
