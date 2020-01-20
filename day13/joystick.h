//
// Created by rnetuka on 13.12.19.
//

#pragma once

#include <functional>
#include <optional>

#include "../intcode/memory.h"


enum joystick_position {
    left   = -1,
    center =  0,
    right  =  1
};

struct joystick {
    int operator()() const;
};