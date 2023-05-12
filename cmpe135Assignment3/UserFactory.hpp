#ifndef UserFactory_hpp
#define UserFactory_hpp

#include <stdio.h>

#include <iostream>
#include "Admin.hpp"
#include "Worker.hpp"
using namespace std;
#include <ctime>


class UserFactory {
public:
    static User* make_users(string which);

};


#endif