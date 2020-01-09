cmake_minimum_required(VERSION 3.6)
project(l09_sockclient)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c)
add_executable(l09_sockclient ${SOURCE_FILES})