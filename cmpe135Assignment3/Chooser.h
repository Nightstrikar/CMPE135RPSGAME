//
//  Chooser.h
//  cmpe135Assignment3
//
//  Created by Alberto Chavez on 3/14/23.
//

#ifndef Chooser_h
#define Chooser_h

#include <iostream>
#include <vector>
using namespace std;

class Chooser {
public:
    string prediction = "none";
    virtual string make_choice(string user_choice, int turn_number) = 0;
};


#endif /* Chooser_h */
