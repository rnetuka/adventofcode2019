//
// Created by rnetuka on 05.12.19.
//

#pragma once

#include <vector>

#include "memory.h"

namespace intcd {

    class output {
    private:
        std::vector<value_t> values_;

    public:
        void operator<<(value_t value) {
            values_.push_back(value);
        }

        std::vector<value_t> values() const {
            return std::vector<value_t> { values_ };
        }
    };

    inline output null_output;

}