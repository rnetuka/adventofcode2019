//
// Created by rnetuka on 05.12.19.
//

#pragma once

#include <utility>
#include <initializer_list>
#include <deque>
#include <stdexcept>

namespace intcd {

    class no_input_exception : public std::logic_error {
    public:
        no_input_exception() : std::logic_error("No input available") {

        }
    };


    struct input
    {
        std::deque<int> values;

        input(std::initializer_list<int> init_list) : values { init_list } {

        }

        void operator>>(int& ref)
        {
            if (values.empty())
                throw no_input_exception();

            ref = values.front();
            values.pop_front();
        }
    };

    inline input null_input { };

}