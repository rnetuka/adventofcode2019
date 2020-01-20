//
// Created by rnetuka on 05.12.19.
//

#pragma once

#include <deque>
#include <functional>
#include <vector>

#include "memory.h"

namespace intcode {

    using listener_t = std::function<void(value_t)>;

    struct output
    {
        std::deque<value_t> values;
        std::vector<listener_t> listeners;

        void operator<<(value_t value);

        bool empty() const;
        int size() const;
        value_t pop_front();
        value_t front() const;
        value_t back() const;
        void clear();
        value_t operator[](int i) const;

    };

    inline output std_output;

}