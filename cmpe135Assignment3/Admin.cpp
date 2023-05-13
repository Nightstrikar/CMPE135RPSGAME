#include "Admin.hpp"
#include <iostream>
#include <chrono>
#include <ctime>
using namespace std;

void Admin::clock_in() {
    auto time_now = chrono::system_clock::now();
    // Convert the time to a string
    time_t time_now_c = chrono::system_clock::to_time_t(time_now);
    cout << "You are clocking in: " << ctime(&time_now_c);
    // Store the clock-in time
    clock_in_time = time_now;
}


void Admin::clock_out() {
    auto time_now = chrono::system_clock::now();
    // Convert the time to a string
    time_t time_now_c = chrono::system_clock::to_time_t(time_now);
    cout << "You are clocking out: " << ctime(&time_now_c);
    // Store the clock-out time
    clock_out_time = time_now;
    // Calculate the shift duration
    chrono::duration<double> shift_duration = clock_out_time - clock_in_time;
    // Print the shift duration in seconds

    cout << "Shift duration: " << chrono::duration_cast<chrono::seconds>(shift_duration).count() << " seconds\n";
    setShiftDuration(chrono::duration_cast<chrono::seconds>(shift_duration).count());
}


void Admin::totalTimeShift() {
    cout << "WE are getting it" << endl;
}
void Admin::shiftTotalTime() {
    // Calculate the shift duration
    chrono::duration<double> shift_duration = clock_out_time - clock_in_time;

    // Print the shift duration in seconds
    cout << "Shift duration: " << chrono::duration_cast<chrono::seconds>(shift_duration).count() << " seconds\n";
}



