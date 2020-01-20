//
// Created by rnetuka on 05.12.19.
//

#pragma once

namespace intcode {

    enum parameter_mode
    {
        position  = 0,
        immediate = 1,
        relative  = 2
    };

    struct parameter
    {
        long value;
        int mode;

        parameter() : value { 0 }, mode { 0 } {

        }
        parameter(long value, int mode) : value { value }, mode { mode } {

        }
        parameter(const parameter& other) : value { other.value }, mode { other.mode } {

        }
    };

}