cmake_minimum_required(VERSION 3.28)
project(task_2)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(task_2
        src/FilerReader.cpp
        src/FilerReader.h
        src/FileWriter.cpp
        src/FileWriter.h
        src/main.cpp

)