#ifndef User_h
#define User_h

#include <iostream>
#include <vector>
using namespace std;

class User {
public:
    virtual void clock_in() = 0;
    virtual void clock_out() = 0;
};


#endif