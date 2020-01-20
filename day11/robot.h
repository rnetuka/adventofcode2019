//
// Created by rnetuka on 11.12.19.
//

#pragma once

#include <functional>
#include <optional>

#include "../intcode/computer.h"


enum color {
    black = 0,
    white = 1
};

enum direction_t {
    up,
    right,
    down,
    left
};

class painting_robot {
    using instruction_listener_t = std::function<void(int, int)>;

private:
    intcode::computer cpu;

    std::optional<instruction_listener_t> instruction_listener;

    direction_t direction = up;

    void handle_instructions(int color, int turn_instruction);

public:
    painting_robot();

    void set_instruction_listener(const instruction_listener_t& listener);

    void turn_left();
    void turn_right();
    void move_forward();
    void paint(int color);
    void boot_up();
};