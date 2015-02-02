
#ifndef LECTURE_ECRITURE__H
#define LECTURE_ECRITURE__H


/* Prototypes des fonctions */
extern void ouvrir_fichier_entree (char * nom_fichier_entree, int binaire);
extern void ouvrir_fichier_sortie (char * nom_fichier_sortie, int binaire);
extern void fermer_fichiers ();

extern unsigned char * lire_caractere ();
extern unsigned int    lire_code         ();
extern unsigned int    lire_code_binaire ();

extern void ecrire_texte (unsigned char * texte);
extern void ecrire_code         (unsigned int code);
extern void ecrire_code_binaire (unsigned int code, int vider_buffer);

long recuperer_taille_fichier_entree ();
long recuperer_taille_fichier_sortie ();

#endif /* LECTURE_ECRITURE__H */
