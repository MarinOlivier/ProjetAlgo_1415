//
//  in_out.h
//  pa1415
//
//  Created by Alex on 02/12/2014.
//  Copyright (c) 2014 Alex et Olivier. All rights reserved.
//

#ifndef __pa1415__in_out__
#define __pa1415__in_out__

#include "arbre.h"

char reader(char *);
void writer(int code, const char* foutput);
void writer_char(char code, const char* foutput);
static void mise_a_un (unsigned char * buffer, int i);
void ecrire_code_binaire (unsigned int code, const char* foutput, int vider_buffer);


#endif