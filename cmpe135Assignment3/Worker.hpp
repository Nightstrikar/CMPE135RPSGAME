
#ifndef Worker_hpp
#define Worker_hpp

#include <stdio.h>
#include "User.h"
using namespace std;

class Worker : public User {
private:
    string employee_id;
    string username;
    string password;
public:
    void clock_in();
    void clock_out();
};

#endif