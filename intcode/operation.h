//
// Created by rnetuka on 05.12.19.
//

#pragma once

#include <functional>
#include <map>
#include <vector>

#include "memory.h"
#include "parameter.h"

namespace intcd {

    using calculation = std::function<value_t(value_t, value_t)>;
    using check       = std::function<bool(value_t)>;
    using comparison  = std::function<bool(value_t, value_t)>;

    enum opcode
    {
        add     = 1,
        mul     = 2,
        in      = 3,
        out     = 4,
        jmp_if  = 5,
        jmp_ifn = 6,
        less    = 7,
        eq      = 8,
        rel     = 9,
        fin     = 99
    };

    inline std::map<int, calculation> calculations {
        { add, [](value_t a, value_t b) { return a + b; } },
        { mul, [](value_t a, value_t b) { return a * b; } }
    };

    inline std::map<int, check> checks {
        { jmp_if,  [](value_t cond) { return  cond; } },
        { jmp_ifn, [](value_t cond) { return !cond; } }
    };

    inline std::map<int, comparison> comparisons {
        { less, [](value_t a, value_t b) { return a < b; } },
        { eq,   [](value_t a, value_t b) { return a == b; } }
    };

    struct operation
    {
        const int code;
        const std::vector<parameter> parameters;

        operation(int code);
        operation(int code, std::vector<parameter>&& parameters);
    };

    operation parse_operation(const intcode& code, int i);

}