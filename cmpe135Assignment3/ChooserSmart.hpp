//
//  ChooserSmart.hpp
//  cmpe135Assignment3
//
//  Created by Alberto Chavez on 3/20/23.
//

#ifndef ChooserSmart_hpp
#define ChooserSmart_hpp

#include <stdio.h>
#include "Chooser.h"
using namespace std;

class SmartChooser : public Chooser {
private:
    string choice;
    int value_rad;
public:
    string make_choice(string user_choice, int turn_number) override;
};

#endif /* ChooserSmart_hpp */
