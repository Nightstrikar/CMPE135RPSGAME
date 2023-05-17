#ifndef PaySettings_hpp
#define PaySettings_hpp
#include "Worker.hpp"
#include "Admin.hpp"
#include "User.hpp"
#include <iostream>
#include <chrono>
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

using namespace std;

class PaySettings {
private:
    double hourly_rate;
    double overtime_rate;
    double pay_period;
    string payPeriod;

public:

    PaySettings() {
        cout << "Are we here???" << endl;
        hourly_rate = 0.0; //the amount worker is paid per hour they work such as 17.25
        pay_period = 0.0; //the amount worker can get pay up to 10000
        overtime_rate = 0.0; //worker will get pay $200 more if they work overtime such as 200.25
        payPeriod = "payperiod";

    }


    void setPayPeriod(string period) {
        cout << "Are we here???" << endl;
        payPeriod = period;
    }

    string getPayPeriod() {
        cout << "Are we here???" << endl;
        return payPeriod;
    }


    //to set and get the hourly_rate
    void set_hourly_rate(double rate) {
        cout << "Are we here???" << endl;
        hourly_rate = rate;
    }
    double get_pay_hourly_rate() const {
        cout << "Are we here???" << endl;
        return hourly_rate;
    }
    //to set and get the ovettime rate
    void set_overtime_rate(double overtimerate) {
        cout << "Are we here???" << endl;
        overtime_rate = overtimerate;
    }
    double get_overime_rate() const {
        cout << "Are we here???" << endl;
        return overtime_rate;
    }

    //to set and get the pay_period
    void set_pay_period(double pay) {
        cout << "Are we here???" << endl;
        pay_period = pay;


    }
    double get_pay_period() const {
        cout << "Are we here???" << endl;
        //The worker works from Monday to Friday
        int daysWorked = 5;
        //the payment for the daily when worker works within 8h/per day
        double dailyPay = hourly_rate * 8;
        // Calculate overtime hours
        double overtimeHours = 0.0;
        double overtimePay = 0.0;
        if (daysWorked > 5) {
            overtimeHours = daysWorked - 5;
            overtimePay = overtimeHours * overtime_rate* 2; //the overtime will be pay within 2 weeks
        }
        //the worker gets pay by biweekly
        double pay_period = (dailyPay * daysWorked*2) + overtimePay;
        return pay_period;
    }



};
#endif
