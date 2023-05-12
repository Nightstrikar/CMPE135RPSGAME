#include "UserFactory.hpp"
#include <iostream>
#include <vector>
//#include "UserFactory.h"
#include "User.h"
#include "Worker.hpp"
#include "Admin.hpp"

using namespace std;

User* UserFactory::make_users(std::string which) {
    if (which == "worker") {
        return new Worker();
    }

    else if (which == "admin") {
        return new Admin();
    }
    else {
        return nullptr;
    }
}
