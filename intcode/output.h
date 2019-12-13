//
// Created by rnetuka on 05.12.19.
//

#pragma once

#include <functional>
#include <vector>

#include "memory.h"

namespace intcd {

    using listener_t = std::function<void(value_t)>;

    struct output
    {
        std::vector<value_t> values;
        std::vector<listener_t> listeners;

        void operator<<(value_t value) {
            values.push_back(value);
            for (auto& listener : listeners)
                listener(value);
        }

        void clear() {
            values.clear();
        }
    };

    inline output std_output;

}