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
        cmpe135Assignment3/main.cpp)


find_package(wxWidgets CONFIG REQUIRED)
target_link_libraries(CMPE135RPSGAME PRIVATE wx::core wx::base)