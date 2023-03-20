//
//  ChooserFactory.hpp
//  cmpe135Assignment3
//
//  Created by Alberto Chavez on 3/14/23.
//

#ifndef ChooserFactory_hpp
#define ChooserFactory_hpp

#include <stdio.h>

#include <iostream>
using namespace std;
#include <ctime>
#include "ChooserRandom.hpp"
class ChooserFactory {
public:
    static Chooser* make_chooser(string which);
};

class HumanChooser : public Chooser {
public:
    string choice() {
        string choice;
        cout << "Please enter your answer (rock, paper, scissors) :";
        cin >> choice;
        while (choice != "rock" && choice != "paper" && choice != "scissors") {
            cout << "Please enter your answer again! ";
            cin >>choice;
        }
        return choice;
    }
};


#endif /* ChooserFactory_hpp */
