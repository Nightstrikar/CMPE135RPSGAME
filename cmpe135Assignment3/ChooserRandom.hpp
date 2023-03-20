//
//  ChooserRandom.hpp
//  cmpe135Assignment3
//
//  Created by Alberto Chavez on 3/14/23.
//

#ifndef ChooserRandom_hpp
#define ChooserRandom_hpp

#include <stdio.h>

#include <iostream>
#include <vector>
#include "Chooser.h"
using namespace std;

class RandomChooser : public Chooser {
private:
    int value;
    string choice;
public:
    string make_choice() override;
};


#endif /* ChooserRandom_hpp */
