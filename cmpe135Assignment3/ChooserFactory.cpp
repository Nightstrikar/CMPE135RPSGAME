//
//  ChooserFactory.cpp
//  cmpe135Assignment3
//
//  Created by Alberto Chavez on 3/14/23.
//

#include "ChooserFactory.hpp"
#include <iostream>
#include <vector>
#include "ChooserFactory.h"
using namespace std;

Chooser* ChooserFactory::make_chooser(string which){
              if (which == "random") {
                return new RandomChooser();
            }
            /*
            else if (which == "smart") {
                return new SmartChooser();
            }
            else if (which == "genius") {
                return new GeniusChooser();
            }
             */
            else {
                return nullptr;
            }
}
