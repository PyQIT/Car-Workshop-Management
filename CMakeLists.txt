<<<<<<< HEAD
cmake_minimum_required(VERSION 3.8)
project(Car_Workshop_Management_v_0_1)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c sqlite3.c client_management.h print_database.h menu.h notification.h)
add_executable(Car_Workshop_Management_v_0_1 ${SOURCE_FILES} client_management.h main.c)
=======
cmake_minimum_required(VERSION 3.10)
project(Car_Workshop_Management_v_0_1_1 C)

set(CMAKE_C_STANDARD 99)

add_executable(Car_Workshop_Management_v_0_1_1 main.c sqlite3.c sqlite3.h)
>>>>>>> d7996431e865c372b3a724d76ffc3b671386044c
