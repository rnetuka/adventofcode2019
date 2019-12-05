cmake_minimum_required(VERSION 3.9)
project(adventofcode2019)

set(CMAKE_CXX_STANDARD 17)

add_executable(adventofcode2019
        main.cpp
        utils.h utils.cpp
        day01/puzzle.h day01/puzzle.cpp
        day02/puzzle.h day02/puzzle.cpp
        day03/puzzle.h day03/puzzle.cpp
        day03/coords.h
        day03/wire.h
        day04/puzzle.h day04/puzzle.cpp
        day05/input.h
        day05/output.h
        day05/instruction.h
        day05/operation.h
        day05/parameter.h
        day05/puzzle.h day05/puzzle.cpp)