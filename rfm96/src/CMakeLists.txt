include_directories(${PROJECT_SOURCE_DIR}/inc)

file (GLOB SOURCES "*.cpp")

add_library(LoraLib ${SOURCES})
