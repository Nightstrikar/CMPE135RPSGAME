#include "Admin.hpp"
#include "PaySettings.hpp"
#include <iostream>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
using namespace std;

void Admin::clock_in() {
    auto time_now = chrono::system_clock::now();
    // Convert the time to a string
    time_t time_now_c = chrono::system_clock::to_time_t(time_now);
    cout << "You are clocking in: " << ctime(&time_now_c);
    // Store the clock-in time
    clock_in_time = time_now;
}

string Admin::getClock_in() {
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

string Admin::getClock_out() {
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

void Admin::totalTimeShift() {
    cout << "WE are getting it" << endl;
}
void Admin::shiftTotalTime() {
    // Calculate the shift duration
    chrono::duration<double> shift_duration = clock_out_time - clock_in_time;

    // Print the shift duration in seconds
    cout << "Shift duration: " << chrono::duration_cast<chrono::seconds>(shift_duration).count() << " seconds\n";
}
void Admin::setWorkerPay(PaySettings& workerPaySettings, double pay, double rate, string period, double overtimeRate) {
    cout << "Are we here???" << endl;
    workerPaySettings.set_pay_period(pay);
    workerPaySettings.set_hourly_rate(rate);
    workerPaySettings.set_overtime_rate(overtimeRate);
    workerPaySettings.setPayPeriod(period);
    cout<< "Pay: "<<pay << "rate: "<< rate << "overtime: " << overtimeRate << "period " <<period <<endl;
}

double Admin::getWorkerPay(PaySettings& adminPaySettings) {
    cout << "Are we here???" << endl;
    double pay = adminPaySettings.get_pay_period();
    double hourly_Rate = adminPaySettings.get_pay_hourly_rate();
    double overtime_rate = adminPaySettings.get_overime_rate();
    return 0;
}



