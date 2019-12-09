//
// Created by rnetuka on 05.12.19.
//

#pragma once

#include <vector>

#include "memory.h"

namespace intcd {

    struct output
    {
        std::vector<value_t> values;

        void operator<<(value_t value) {
            values.push_back(value);
        }
    };

    inline output std_output;

}