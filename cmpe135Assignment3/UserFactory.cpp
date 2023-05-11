#include "UserFactory.hpp"
#include <iostream>
#include <vector>
#include "UserFactory.h"
#include "User.h"

using namespace std;

User* UserFactory::make_user(string which) {
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
