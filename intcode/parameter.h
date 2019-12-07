//
// Created by rnetuka on 05.12.19.
//

#pragma once

namespace intcd {

    enum parameter_mode
    {
        position  = 0,
        immediate = 1
    };

    struct parameter
    {
        const int value;
        const int mode;

        parameter(int value, int mode) : value { value }, mode { mode } {

        }

        operator int() const {
            return value;
        }
    };

}