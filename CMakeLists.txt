cmake_minimum_required(VERSION 3.25)
project(s)

set(CMAKE_CXX_STANDARD 11)

add_executable(s main.cpp include/myconio_mac.cpp snake.h)
