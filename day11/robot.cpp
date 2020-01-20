//
// Created by rnetuka on 11.12.19.
//

#include "robot.h"
#include "spaceship.h"

using namespace intcode;
using namespace std;


struct scanner {

    value_t operator()() {
        int x = ship.robot_x;
        int y = ship.robot_y;
        int color = ship.area[x][y];
        return color;
    }

};

painting_robot::painting_robot() {
    cpu.in = scanner { };
    cpu.add_output_consumer([this](value_t value) {
        if (cpu.out.size() == 2) {
            int color = cpu.out[0];
            int turn  = cpu.out[1];
            cpu.out.clear();

            if (instruction_listener)
                (*instruction_listener)(color, turn);

            handle_instructions(color, turn);
        }
    });
}

void painting_robot::set_instruction_listener(const instruction_listener_t& listener) {
    instruction_listener = listener;
}

void painting_robot::turn_left() {
    switch (direction) {
        case up:    direction = left;  break;
        case right: direction = up;    break;
        case left:  direction = down;  break;
        case down:  direction = right; break;
    }
}

void painting_robot::turn_right() {
    switch (direction) {
        case up:    direction = right; break;
        case right: direction = down; break;
        case left:  direction = up; break;
        case down:  direction = left; break;
    }
}

void painting_robot::move_forward() {
    int dx = 0;
    int dy = 0;

    switch (direction) {
        case up:    dx =  0; dy = -1; break;
        case right: dx =  1; dy =  0; break;
        case down:  dx =  0; dy =  1; break;
        case left:  dx = -1; dy =  0; break;
    }

    ship.robot_x += dx;
    ship.robot_y += dy;

    if (ship.robot_x < 0
        || ship.robot_x >= spaceship_area_width
        || ship.robot_y < 0
        || ship.robot_y >= spaceship_area_height)
        throw logic_error("Robot tries to move out of ship area");
}

void painting_robot::paint(int color) {
    int x = ship.robot_x;
    int y = ship.robot_y;
    ship.area[x][y] = color;
}

void painting_robot::handle_instructions(int color, int turn_instruction)
{
    paint(color);

    switch (turn_instruction) {
        case 0:  turn_left();  break;
        case 1:  turn_right(); break;
        default: throw logic_error("Unknown robot instruction: " + to_string(turn_instruction));
    }
    move_forward();
}

void painting_robot::boot_up() {
    code code = read("day11/res/input.txt");
    cpu.run_code(code);
}