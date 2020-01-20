//
// Created by rnetuka on 10.01.20.
//

#pragma once

#include <functional>

#include "../intcode/computer.h"
#include "display.h"
#include "joystick.h"
#include "game.h"

using display_t = std::ostream&;

struct gaming_console
{
    display_t display;

    intcode::computer computer;
    intcode::code code;

    game_t game_;

    gaming_console(display_t display = no_display);

    game_t& game();
    void insert_coin();
    void play_game();
};
