cmake_minimum_required(VERSION 3.28)
project(task_2)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(task_2
        src/FileReader.cpp
        src/FileReader.h
        src/FileWriter.cpp
        src/FileWriter.h
        src/main.cpp
        src/GameEngine.h
        src/GameEngine.cpp
        src/Interface.cpp
        src/Interface.h
        src/GameOfLifeParser.h
        src/GameOfLifeParser.cpp
        src/LifeGame.h
        src/LifeGame.cpp
)