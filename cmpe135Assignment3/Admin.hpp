
#ifndef Admin_hpp
#define Admin_hpp

#include <stdio.h>
#include "User.hpp"
using namespace std;

class Admin : public User {
private:
    string admin_id;
    string username;
    string password;
    chrono::system_clock::time_point clock_in_time;
    chrono::system_clock::time_point clock_out_time;
    
public:
    void clock_in();
    void clock_out();
    void shiftTotalTime();
    void totalTimeShift();
    void create_worker(string username, string password, string employee_id);
    //void delete_Worker(Worker);
    //Worker find_worker(string employee_id);
};

#endif

