cmake_minimum_required(VERSION 3.9)
project(adventofcode2019)

set(CMAKE_CXX_STANDARD 17)
set(THREADS_PREFER_PTHREAD_FLAG ON)

add_executable(adventofcode2019
        main.cpp
        puzzle.h puzzle.cpp
        2darray/2darray.h
        utils.h utils.cpp
        intcode/computer.h intcode/computer.cpp
        intcode/memory.h
        intcode/instruction.h intcode/instruction.cpp
        intcode/operation.h intcode/operation.cpp
        intcode/parameter.h
        intcode/input.h intcode/input.cpp
        intcode/output.h intcode/output.cpp
        geometry/point.h
        geometry/line.h geometry/line.cpp
        geometry/vector.h geometry/vector.cpp
        geometry/triangle.h geometry/triangle.cpp
        geometry/geometry.h
        math/matrix.h
        graph/graph.h
        graph/tree.h
        math/math.h math/math.cpp
        map/coords.h map/coords.cpp
        day01/puzzle.h day01/puzzle.cpp
        day02/puzzle.h day02/puzzle.cpp
        day03/puzzle.h day03/puzzle.cpp
        day03/wire.h day03/wire.cpp
        day04/puzzle.h day04/puzzle.cpp
        day05/puzzle.h day05/puzzle.cpp
        day06/graph.h day06/orbit_map.cpp
        day06/puzzle.h day06/puzzle.cpp
        day07/amplifier.h day07/amplifier.cpp
        day07/puzzle.h day07/puzzle.cpp
        day08/layer.h day08/layer.cpp
        day08/image.h day08/image.cpp
        day08/puzzle.h day08/puzzle.cpp
        day09/puzzle.h day09/puzzle.cpp
        day10/asteroid.h day10/asteroid.cpp
        day10/laser.h day10/laser.cpp
        day10/puzzle.h day10/puzzle.cpp
        day11/spaceship.h day11/spaceship.cpp
        day11/robot.h day11/robot.cpp
        day11/puzzle.h day11/puzzle.cpp
        day12/moon.h day12/moon.cpp
        day12/puzzle.h day12/puzzle.cpp
        day13/game.h day13/game.cpp
        day13/joystick.h day13/joystick.cpp
        day13/display.h day13/display.cpp
        day13/console.h day13/console.cpp
        day13/puzzle.h day13/puzzle.cpp
        day14/nanofactory.h day14/nanofactory.cpp
        day14/puzzle.h day14/puzzle.cpp
        day15/sectormap.h day15/sectormap.cpp
        day15/puzzle.h day15/puzzle.cpp
        day16/phase.h day16/phase.cpp
        day16/puzzle.h day16/puzzle.cpp
        day17/puzzle.h day17/puzzle.cpp
        day18/maze.h day18/maze.cpp
        day18/graph.h day18/graph.cpp
        day18/puzzle.h day18/puzzle.cpp
        day19/beam.h
        day19/puzzle.h day19/puzzle.cpp
        day20/portal_maze.h day20/portal_maze.cpp
        day20/portal_graph.h day20/portal_graph.cpp
        day20/puzzle.h day20/puzzle.cpp
        day21/springdroid.h day21/springdroid.cpp
        day21/puzzle.h day21/puzzle.cpp
        day22/puzzle.h day22/puzzle.cpp
        day23/network_adapter.h day23/network_adapter.cpp
        day23/computer.h day23/computer.cpp
        day23/inetwork.h
        day23/network.h day23/network.cpp
        day23/puzzle.h day23/puzzle.cpp
        day23/nat.h day23/nat.cpp
        day24/puzzle.h day24/puzzle.cpp
        day25/puzzle.h day25/puzzle.cpp)

find_package(Threads REQUIRED)
target_link_libraries(adventofcode2019 Threads::Threads)