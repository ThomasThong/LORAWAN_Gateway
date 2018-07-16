include_directories(${PROJECT_SOURCE_DIR}/inc)
link_directories(${PROJECT_SOURCE_DIR}/src)

set (Tx_c Tx.c)

add_executable(Tx ${Tx_c})

target_link_libraries (Tx LoraLib ${wiringPiLib})
