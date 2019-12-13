//
// Created by rnetuka on 13.12.19.
//

#pragma once

namespace day13 {

    enum joystick_position {
        left   = -1,
        center =  0,
        right  =  1
    };

    struct joystick_t
    {
        int position = 0;

        void operator>>(int& ref) {
            ref = position;
        }
    };

}