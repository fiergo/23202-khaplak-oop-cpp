cmake_minimum_required(VERSION 3.28)
project(task_1)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(task_1
        src/main.cpp
        src/BitArray.cpp
        src/BitArray.h
)