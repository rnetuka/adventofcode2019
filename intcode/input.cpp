//
// Created by rnetuka on 10.01.20.
//

#include "input.h"

using namespace std;


namespace intcode {

    input::input(initializer_list<value_t> init_list) : values { init_list } {

    }

    value_t input::operator()() {
        if (values.empty())
            throw no_input_exception();

        value_t value = values.front();
        values.pop_front();
        return value;
    }

    void input::operator<<(value_t value) {
        values.push_back(value);
    }

    no_input_exception::no_input_exception() : logic_error("No input available") {

    }

}