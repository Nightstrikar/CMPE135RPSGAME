#ifndef User_hpp
#define User_hpp
#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

class User {
public:
    int shift_duration = 13;
    virtual void clock_in() = 0;
    virtual void clock_out() = 0;
    virtual void shiftTotalTime() = 0;
    virtual string getClock_in() = 0;
    virtual string getClock_out() = 0;
    int getShiftDuration() const { return shift_duration; }
    void setShiftDuration(int duration) {
        shift_duration = duration;
    }

};


#endif