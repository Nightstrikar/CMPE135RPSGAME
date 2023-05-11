
#ifndef Admin_hpp
#define Admin_hpp

#include <stdio.h>
#include "User.h"
using namespace std;

class Admin : public User {
private:
    string admin_id;
    string username;
    string password;
public:
    void clock_in();
    void clock_out();
    void create_worker(string username, string password, string employee_id);
    //void delete_Worker(Worker);
    //Worker find_worker(string employee_id);
};

#endif
