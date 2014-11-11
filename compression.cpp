//
//  compression.cpp
//  projet_algo
//
//  Created by Olivier on 11/11/2014.
//  Copyright (c) 2014 Alex&Olivier. All rights reserved.
//

#include <iostream>
#include <stdio.h> // gestion de fichiers

using namespace std;


/*********************************************
 *               Pseudo code                 *
 *********************************************/
// 1 compteur ← −1
// 2 pour a ∈ A faire
// 3 compteur ← compteur + 1
// 4 Inserer((D,(−1, a, compteur)))
// 5 compteur ← compteur + 1
// 6 Inserer((D,(−1, a, compteur)))
// 7 p ← −1
// 8 tantque non fdf(fentr´ee) et a est le prochain caract`ere faire
// 9 q ← Recherche((D,(p, a)))
// 10 si q = nil alors
// 11 ´ecrire codep sur 1 + log(compteur) bits dans fsortie
// 12 compteur ← compteur + 1
// 13 Inserer((D,(p, a, compteur)))
// 14 p ← Recherche((D,(−1, a)))
// 15 sinon p ← q
// 16 ´ecrire code(p) sur 1 + log(compteur) bits dans fsortie
// 17 ´ecrire Recherche((D,(−1, FIN))) sur 1 + log(compteur) bits dans fsortie