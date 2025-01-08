cmake_minimum_required(VERSION 3.30)
project(table C)

set(CMAKE_C_STANDARD 11)

include_directories(src)
file(GLOB SOURCES "src/*.c" "src/dsa/*.c" "src/dsa/*.h")
add_executable(${PROJECT_NAME} ${SOURCES})
