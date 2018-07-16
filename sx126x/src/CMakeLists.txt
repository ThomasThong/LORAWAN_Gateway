include_directories(${PROJECT_SOURCE_DIR}/inc)

file (GLOB SOURCES "*.c")

add_library(LoraLib ${SOURCES})
target_link_libraries(LoraLib m)
