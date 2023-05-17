
#ifndef Worker_hpp
#define Worker_hpp

#include <stdio.h>
#include "User.hpp"
using namespace std;

class Worker : public User {
private:
    string employee_id;
    string username;
    string password;
    chrono::system_clock::time_point clock_in_time;
    chrono::system_clock::time_point clock_out_time;
public:
    void clock_in();
    void clock_out();
    string getClock_in();
    string getClock_out();
    void shiftTotalTime();
    int getShiftTotalTime();
};

#endif