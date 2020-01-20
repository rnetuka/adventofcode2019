//
// Created by rnetuka on 05.12.19.
//

#pragma once

#include <initializer_list>
#include <deque>
#include <stdexcept>

#include "memory.h"

namespace intcode {

    struct no_input_exception : public std::logic_error {
        no_input_exception();
    };


    class input {
        std::deque<value_t> values;
    public:
        input() = default;
        input(std::initializer_list<value_t> init_list);
        value_t operator()();
        void operator<<(value_t value);
    };

    inline input null_input { };

}