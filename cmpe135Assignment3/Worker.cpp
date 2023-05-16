#include "Worker.hpp"
#include <iostream>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#pragma warning(disable : 4996)
using namespace std;

void Worker::clock_in() {
    auto time_now = chrono::system_clock::now();
    // Convert the time to a string
    time_t time_now_c = chrono::system_clock::to_time_t(time_now);
    cout << "You are clocking in: " << ctime(&time_now_c);
    // Store the clock-in time
    clock_in_time = time_now;
}

string Worker::getClock_in() {
    // Convert the time_point to a time_t value
    time_t time = chrono::system_clock::to_time_t(clock_in_time);
    // Convert time_t to a tm value
    tm* timeinfo = localtime(&time);
    // Format the time using put_time
    stringstream ss;
    ss << put_time(timeinfo, "%Y-%m-%d %H:%M:%S");
    // Get the string representation
    string str_time = ss.str();
    return str_time;
}

void Worker::clock_out() {
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

string Worker::getClock_out() {
    // Convert the time_point to a time_t value
    time_t time = chrono::system_clock::to_time_t(clock_out_time);
    // Convert time_t to a tm value
    tm* timeinfo = localtime(&time);
    // Format the time using put_time
    stringstream ss;
    ss << put_time(timeinfo, "%Y-%m-%d %H:%M:%S");
    // Get the string representation
    string str_time = ss.str();
    return str_time;
}

void Worker::shiftTotalTime() {
    // Calculate the shift duration

    // Print the shift duration in seconds
    cout << "Shifts Entire duration: " << shift_duration << " seconds\n";
}