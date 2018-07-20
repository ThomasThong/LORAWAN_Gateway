include_directories(${PROJECT_SOURCE_DIR}/inc)
link_directories(${PROJECT_SOURCE_DIR}/src)

set (Tx_c Tx.c)
set (Rx_c Rx.c)

add_executable(Tx ${Tx_c})
add_executable(Rx ${Rx_c})

target_link_libraries (Tx LoraLib ${wiringPiLib})
target_link_libraries (Rx LoraLib ${wiringPiLib})
