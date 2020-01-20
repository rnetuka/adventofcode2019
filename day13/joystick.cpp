//
// Created by rnetuka on 10.01.20.
//

#include <iostream>

#include "joystick.h"

using namespace std;


int joystick::operator()() const {
    char c;
    cin >> c;
    if (c == 'd')
        return joystick_position::right;
    else if (c == 'a')
        return joystick_position::left;
    else
        return center;
}