cmake_minimum_required(VERSION 3.0)
project (sx126x_gateway)

set(CMAKE_C_STANDARD 99)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories(inc)

find_library(wiringPiLIb wiringPi)
find_package(Threads REQUIRED)
add_definitions(-lwiringPi -pthread)
#add_subdirectory(app)
add_subdirectory(src)
