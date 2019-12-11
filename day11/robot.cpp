//
// Created by rnetuka on 11.12.19.
//

using namespace std;

#include "robot.h"
#include "spaceship.h"

namespace day11 {

    void scanner_t::operator>>(int& ref)
    {
        int x = ship.robot_x;
        int y = ship.robot_y;
        int color = ship.area[x][y];
        ref = color;
    }

    void robot_output_t::operator<<(value_t value) {
        values.push_back(value);

        if (values.size() == 2)
        {
            for (auto& listener : listeners) {
                int color = values[0];
                int turn  = values[1];
                listener(color, turn);
            }
            values.clear();
        }
    }

    void deploy(robot_t& robot, int x, int y) {
        ship.robot = &robot;
        ship.robot_x = x;
        ship.robot_y = y;
    }

    void turn_left(robot_t& robot) {
        switch (robot.direction) {
            case up:    robot.direction = left;  break;
            case right: robot.direction = up;    break;
            case left:  robot.direction = down;  break;
            case down:  robot.direction = right; break;
        }
    }

    void turn_right(robot_t& robot) {
        switch (robot.direction) {
            case up:    robot.direction = right; break;
            case right: robot.direction = down; break;
            case left:  robot.direction = up; break;
            case down:  robot.direction = left; break;
        }
    }

    void move_forward(robot_t& robot) {
        int dx = 0;
        int dy = 0;

        switch (robot.direction) {
            case up:    dx =  0; dy = -1; break;
            case right: dx =  1; dy =  0; break;
            case down:  dx =  0; dy =  1; break;
            case left:  dx = -1; dy =  0; break;
        }

        ship.robot_x += dx;
        ship.robot_y += dy;

        if (ship.robot_x < 0 || ship.robot_x >= spaceship_area_width || ship.robot_y < 0 || ship.robot_y >= spaceship_area_height)
            throw logic_error("Robot tries to move out of ship area");
    }

    void paint(robot_t& robot, int color) {
        int x = ship.robot_x;
        int y = ship.robot_y;
        ship.area[x][y] = color;
    }

    void handle_robot(robot_t& robot, int color, int turn_instruction)
    {
        paint(robot, color);

        switch (turn_instruction) {
            case 0:  turn_left(robot);  break;
            case 1:  turn_right(robot); break;
            default: throw logic_error("Unknown robot turn instruction: " + to_string(turn_instruction));
        }

        move_forward(robot);
    }

}