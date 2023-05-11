#ifndef User_h
#define User_h

#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

class User {
public:
    std::chrono::system_clock::time_point clock_in_time;
    std::chrono::system_clock::time_point clock_out_time;
    int shift_duration;
    virtual void clock_in() = 0;
    virtual void clock_out() = 0;
    virtual void shiftTotalTime() = 0;
};


#endif