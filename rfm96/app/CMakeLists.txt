include_directories(${PROJECT_SOURCE_DIR}/inc)
link_directories(${PROJECT_SOURCE_DIR}/src)

set (Tx_cpp Sending.cpp)
set (Rx_cpp Receive.cpp)
set (Thread_cpp thread.cpp)

add_executable(Tx ${Tx_cpp})
add_executable(Rx ${Rx_cpp})
add_executable(thread ${Thread_cpp})

target_link_libraries(Tx LoraLib ${wiringPiLib} Threads::Threads)
target_link_libraries(Rx LoraLib ${wiringPiLib} Threads::Threads)
target_link_libraries(thread LoraLib ${wiringPiLib} Threads::Threads)
