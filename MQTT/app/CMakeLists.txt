include_directories(${PROJECT_SOURCE_DIR}/inc)

set (pub_c simple_publisher.c)
set (sub_c simple_subscriber.c)

find_package (Threads)

add_executable(pub ${pub_c})
target_link_libraries(pub MQTT ${CMAKE_THREAD_LIBS_INIT})

add_executable(sub ${sub_c})
target_link_libraries(sub MQTT ${CMAKE_THREAD_LIBS_INIT})
