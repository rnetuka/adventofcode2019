//
// Created by rnetuka on 11.12.19.
//

#pragma once

#include "robot.h"

namespace day11 {

    constexpr static int spaceship_area_width  = 1000;
    constexpr static int spaceship_area_height = 1000;

    struct spaceship_t {
        int area[spaceship_area_width][spaceship_area_height];

        robot_t* robot = nullptr;
        int robot_x = 0;
        int robot_y = 0;

        spaceship_t();
    };

    inline spaceship_t ship;

    void repaint_black(spaceship_t& spaceship);
    std::string registration_id(const spaceship_t& spaceship);

}