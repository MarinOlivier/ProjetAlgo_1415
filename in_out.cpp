//
//  in_out.cpp
//  pa1415
//
//  Created by Alex on 02/12/2014.
//  Copyright (c) 2014 Alex et Olivier. All rights reserved.
//
#include <iostream>
#include <stdio.h>
#include "in_out.h"
using namespace std;

char reader(char * uncomp_file){
    char current_char;
    FILE* entry;
    entry = fopen("/Users/alex/developper/pa1415/test.txt", "r");
    current_char = fgetc(entry);
    while(current_char != EOF){
        cout << current_char;
        current_char = fgetc(entry);
        //return current_char;
    }
    return current_char;
}

void writer(){
    
}