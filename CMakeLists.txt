cmake_minimum_required(VERSION 3.25)
project(CMPE135RPSGAME)

set(CMAKE_CXX_STANDARD 14)

include_directories(cmpe135Assignment3)

add_executable(CMPE135RPSGAME
        cmpe135Assignment3/Chooser.h
        cmpe135Assignment3/ChooserFactory.cpp
        cmpe135Assignment3/ChooserFactory.h
        cmpe135Assignment3/ChooserFactory.hpp
        cmpe135Assignment3/ChooserRandom.cpp
        cmpe135Assignment3/ChooserRandom.hpp
        cmpe135Assignment3/ChooserSmart.cpp
        cmpe135Assignment3/ChooserSmart.hpp
        cmpe135Assignment3/main.cpp
        cmpe135Assignment3/UserFactory.cpp
        cmpe135Assignment3/Worker.cpp
        cmpe135Assignment3/Workers.hpp
        cmpe135Assignment3/Admin.cpp
        cmpe135Assignment3/Admin.hpp
        cmpe135Assignment3/User.hpp cmpe135Assignment3/PaySettings.hpp)


find_package(wxWidgets CONFIG REQUIRED)
target_link_libraries(CMPE135RPSGAME PRIVATE wx::core wx::base)