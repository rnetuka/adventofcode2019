//
// Created by rnetuka on 11.12.19.
//

#pragma once

#include <functional>

#include "../intcode/memory.h"

namespace day11 {

    enum color
    {
        black = 0,
        white = 1
    };

    enum direction_t {
        up,
        right,
        down,
        left
    };

    struct robot_t {
        direction_t direction = up;
    };

    struct scanner_t {
        void operator>>(int& ref);
    };

    inline scanner_t scanner;

    void deploy(robot_t& robot, int x, int y);
    void turn_left(robot_t& robot);
    void turn_right(robot_t& robot);
    void move_forward(robot_t& robot);
    void paint(robot_t& robot, int color);

    using listener_t = std::function<void(int, int)>;

    struct robot_output_t
    {
        std::vector<value_t> values;
        std::vector<listener_t> listeners;

        void operator<<(value_t value);
    };

    void handle_robot(robot_t& robot, int color, int turn_instruction);

}