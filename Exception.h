//
//  Exception.h
//  Semestral
//
//  Created by Tomas Gajarsky on 24.4.2016.
//  Copyright (c) 2016 Gajarsky. All rights reserved.
//

#include "stdio.h"
#include "iostream"
#include "stdlib.h"
#include "string"
using namespace std;

#ifndef Semestral_Exception_h
#define Semestral_Exception_h

class Exception {
    int n_error;
    string s_error;
    
public: Exception(int error)
    {
        n_error = error;
    }
    
    string Message_en(void){
        switch(n_error) {
            case 1: return string("The signals don't have the same length!");
            case 2: return string("The filter coefficient is not between 0 and 1.");
            case 3: return string("The frequency of sine wave cannot be negative and must fulfil the Nyquist theorem");
            default: return string("Another error occurred");
        }
    }
};

#endif
