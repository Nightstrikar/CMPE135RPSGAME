#include "Admin.hpp"
#include <iostream>
#include <chrono>
using namespace std;

void Admin::clock_in() {
    // Get the current time
    auto time_now = chrono::system_clock::now();

    // Convert the time to a string
    time_t time_now_c = chrono::system_clock::to_time_t(time_now);
    string time_now_str = ctime(&time_now_c);

    // Store the clock-in time
    clock_in_time = time_now_str;
}

void Admin::clock_out() {
    // Get the current time
    auto time_now = chrono::system_clock::now();

    // Convert the time to a string
    time_t time_now_c = chrono::system_clock::to_time_t(time_now);
    string time_now_str = ctime(&time_now_c);

    // Store the clock-in time
    clock_out_time = time_now_str;
}
