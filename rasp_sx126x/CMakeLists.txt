cmake_minimum_required(VERSION 2.8.9)
project(lora_gateway)

include_directories(inc)

file(GLOB SOURCES "src/*.c")

#set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

add_executable(test1 ${SOURCES})
