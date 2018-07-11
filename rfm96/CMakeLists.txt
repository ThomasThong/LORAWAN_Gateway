cmake_minimum_required(VERSION 3.0)
project(rfm96)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_VERBOSE_MAKEFILE on)

include_directories(inc)
MESSAGE("${CMAKE_SOURCE_DIR}")

find_library(wiringPiLib  wiringPi)
find_package(Threads REQUIRED)
add_definitions(-std=c++0x -lwiringPi -pthread)
add_subdirectory(src)
add_subdirectory(app)
