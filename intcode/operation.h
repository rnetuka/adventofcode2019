//
// Created by rnetuka on 05.12.19.
//

#pragma once

#include <functional>
#include <map>
#include <vector>

#include "parameter.h"

namespace intcd {

    using calculation = std::function<int(int, int)>;
    using check = std::function<bool(int)>;
    using comparison = std::function<bool(int, int)>;

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
        fin     = 99
    };

    inline std::map<int, calculation> calculations {
        { add, [](int a, int b) { return a + b; } },
        { mul, [](int a, int b) { return a * b; } }
    };

    inline std::map<int, check> checks {
        {jmp_if,  [](int cond) { return  cond; } },
        {jmp_ifn, [](int cond) { return !cond; } }
    };

    inline std::map<int, comparison> comparisons {
        { less, [](int a, int b) { return a < b; } },
        { eq,   [](int a, int b) { return a == b; } }
    };

    struct operation
    {
        const int code;
        const std::vector<parameter> parameters;

        operation(int code);
        operation(int code, std::vector<parameter>&& parameters);
    };

    operation parse_operation(const std::vector<int>& code, int i);

}