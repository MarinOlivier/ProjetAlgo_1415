//
//  decompression.cpp
//  projet_algo
//
//  Created by Olivier on 11/11/2014.
//  Copyright (c) 2014 Alex&Olivier. All rights reserved.
//

#include <iostream>

#include "decompression.h"

using namespace std;

// lecture d'un caractère c;
// écrire c; // ajout suite à un oubli
// w = c;
// tant que (lecture d'un caractère c) faire
// si (c > 255 && l'index c existe dans le dictionnaire) faire
// entrée = l'entrée du dictionnaire de c;
//        sinon si (c > 255 && l'index c n'existe pas dans le dictionnaire) faire
//            entrée = w + w[0];
//        sinon
//            entrée = c;
//        fin si;
//        sortie : écrire entrée;
//        ajouter w+entrée[0] au dictionnaire;
//        w = entrée;
//    fin tant que;