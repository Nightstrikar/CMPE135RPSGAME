#include "Admin.hpp"
#include <iostream>
#include <chrono>
#pragma warning(disable : 4996)
using namespace std;

void Admin::clock_in() {
    auto time_now = chrono::system_clock::now();

    // Convert the time to a string
    time_t time_now_c = chrono::system_clock::to_time_t(time_now);
    cout << "time_now_c: " << time_now_c << endl;
    string time_now_str = ctime(&time_now_c);

    // Store the clock-in time
    clock_in_time = chrono::system_clock::from_time_t(time_now_c);
    cout << "You are clocking in: " << ctime(&time_now_c) << endl;
}


void Admin::clock_out() {

    // Get the current time
    auto time_now = chrono::system_clock::now();

    // Convert the time to a string
    time_t time_now_c = chrono::system_clock::to_time_t(time_now);
    string time_now_str = ctime(&time_now_c);

    // Store the clock-out time
    clock_out_time = chrono::system_clock::from_time_t(time_now_c);
    cout << "You are clocking out: " << ctime(&time_now_c) << endl;
}


void Admin::totalTimeShift() {
    cout << "WE are getting it" << endl;
}
void Admin::shiftTotalTime() {
    int shift_total_time = 9;
    // Calculate the difference between the clock-in and clock-out times
    auto time_diff = chrono::duration_cast<chrono::seconds>(clock_out_time - clock_in_time);
    shift_total_time = time_diff.count();
    // Display the difference in seconds
    cout << "Shift duration: " << time_diff.count() << " seconds" << endl;


    /*
    auto time_in = chrono::system_clock::from_time_t(chrono::system_clock::to_time_t(clock_in_time));
    cout << "time in: " << chrono::system_clock::to_time_t(time_in) << endl;

    auto time_out = chrono::system_clock::from_time_t(chrono::system_clock::to_time_t(clock_out_time));
    auto duration = chrono::duration_cast<chrono::seconds>(time_out - time_in);
    setShiftDuration(duration.count());
    cout << "Shift duration: " << duration.count() << " seconds" << endl;
     */
}



