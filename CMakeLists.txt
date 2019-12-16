cmake_minimum_required(VERSION 3.9)
project(adventofcode2019)

set(CMAKE_CXX_STANDARD 17)

add_executable(adventofcode2019
        main.cpp
        utils.h utils.cpp
        intcode/computer.h intcode/computer.cpp
        intcode/instruction.h intcode/instruction.cpp
        intcode/operation.h intcode/operation.cpp
        intcode/output.h
        intcode/input.h
        intcode/parameter.h
        day01/puzzle.h day01/puzzle.cpp
        day02/puzzle.h day02/puzzle.cpp
        day03/puzzle.h day03/puzzle.cpp
        day03/coords.h
        day03/wire.h
        day04/puzzle.h day04/puzzle.cpp
        day05/puzzle.h day05/puzzle.cpp
        day06/graph.h
        day06/puzzle.h day06/puzzle.cpp
        day07/amplifier.h
        day07/puzzle.h day07/puzzle.cpp
        day08/puzzle.h day08/puzzle.cpp
        day09/puzzle.h day09/puzzle.cpp
        day10/asteroid.h
        day10/laser.h
        day10/geometry.h
        day10/puzzle.h day10/puzzle.cpp
        day11/spaceship.h day11/spaceship.cpp
        day11/robot.h day11/robot.cpp
        day11/puzzle.h day11/puzzle.cpp
        day12/puzzle.h day12/puzzle.cpp
        day13/game.h day13/game.cpp
        day13/joystick.h
        day13/puzzle.h day13/puzzle.cpp
        day14/nanofactory.h day14/nanofactory.cpp
        day14/puzzle.h day14/puzzle.cpp
        day15/sectormap.h day15/sectormap.cpp
        day15/graph.h day15/graph.cpp
        day15/puzzle.h day15/puzzle.cpp)