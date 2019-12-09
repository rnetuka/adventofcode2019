//
// Created by rnetuka on 05.12.19.
//

#pragma once

namespace intcd {

    enum parameter_mode
    {
        position  = 0,
        immediate = 1,
        relative  = 2
    };

    struct parameter
    {
        const long value;
        const int mode;

        parameter(long value, int mode) : value { value }, mode { mode } {

        }

        operator int() const {
            return value;
        }
    };

}