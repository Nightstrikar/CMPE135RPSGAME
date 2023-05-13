#include "Worker.hpp"
#include <iostream>
#include <chrono>
#pragma warning(disable : 4996)
using namespace std;

void Worker::clock_in() {
    // Get the current time
    auto time_now = chrono::system_clock::now();
    /*
    // Convert the time to a string
    time_t time_now_c = chrono::system_clock::to_time_t(time_now);
    string time_now_str = ctime(&time_now_c);

    // Store the clock-in time
    clock_in_time = time_now_str;
     */
    //clock_in_time = time_now;
    clock_in_time = chrono::system_clock::now();
}

void Worker::clock_out() {
    auto time_now = chrono::system_clock::now();
    clock_out_time = time_now;
    auto time_now_c = chrono::system_clock::to_time_t(time_now);
    cout << "You are clocking out: " << ctime(&time_now_c);

    shiftTotalTime();
    cout << "Here we have the shift duration: " << shift_duration << endl;

    // Store the clock-in time
    //clock_out_time = time_now;
}

void Worker::shiftTotalTime() {
    auto duration = chrono::duration_cast<chrono::minutes>(clock_out_time - clock_in_time);
    shift_duration = duration.count();
    //auto time_in = chrono::system_clock::from_time_t(chrono::system_clock::to_time_t(clock_out_time));
    //auto time_out = chrono::system_clock::from_time_t(chrono::system_clock::to_time_t(clock_out_time));
    //auto duration = chrono::duration_cast<chrono::minutes>(time_out - time_in);
    //shift_duration = duration.count();
}