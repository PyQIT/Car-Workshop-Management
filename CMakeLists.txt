cmake_minimum_required(VERSION 3.8)
project(Car_Workshop_Management_v_0_1)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c sqlite3.c)
add_executable(Car_Workshop_Management_v_0_1 ${SOURCE_FILES})