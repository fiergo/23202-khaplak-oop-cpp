cmake_minimum_required(VERSION 3.28)
project(task_0)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(task_0
        src/main.cpp
        src/FileReader.cpp
        src/FileWriter.cpp
        src/FileWriter.h
        src/WordStatistics.cpp
        src/WordStatistics.h
        src/TextParser.cpp
        src/TextParser.h
)
