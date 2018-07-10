cmake_minimum_required(VERSION 3.0)
project(rfm96)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(inc)

file (GLOB SOURCES "src/*.cpp")

add_executable(test_rfm96 ${SOURCES})
find_library(wiringPi_LIB  wiringPi)
target_link_libraries(test_rfm96 ${wiringPi_LIB})
add_definitions(-std=c++0x -lwiringPi -pthread)
