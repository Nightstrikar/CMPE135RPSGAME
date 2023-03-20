//
//  ChooserRandom.cpp
//  cmpe135Assignment3
//
//  Created by Alberto Chavez on 3/14/23.
//

#include "ChooserRandom.hpp"
#include <iostream>
#include <vector>
//#include "RandomChooser.h"
using namespace std;

string RandomChooser::make_choice(){
        value = rand() % 3;
        if (value == 0) {
                choice = "rock";
        } else if (value == 1) {
                choice = "scissors";
        } else {
                choice = "paper";
        }
        return choice;
}
