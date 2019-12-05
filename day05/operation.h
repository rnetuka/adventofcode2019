//
// Created by rnetuka on 05.12.19.
//

#pragma once

#include <functional>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

#include "parameter.h"

namespace day5 {

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

    std::map<int, calculation> calculations {
        { add, [](int a, int b) { return a + b; } },
        { mul, [](int a, int b) { return a * b; } }
    };

    std::map<int, check> checks {
        {jmp_if,  [](int cond) { return  cond; } },
        {jmp_ifn, [](int cond) { return !cond; } }
    };

    std::map<int, comparison> comparisons {
        { less, [](int a, int b) { return a < b; } },
        { eq,   [](int a, int b) { return a == b; } }
    };

    struct operation
    {
        const int code;
        const std::vector<parameter> parameters;

        operation(int code) : code { code }, parameters { } {

        }

        operation(int code, std::vector<parameter>&& parameters) : code { code }, parameters { std::move(parameters) } {

        }
    };

    operation parse_operation(const std::vector<int>& code, int i)
    {
        instruction instruction { code[i] };

        int opcode = instruction.opcode();

        if (opcode == fin)
            return { opcode };

        if (opcode == add || opcode == mul)
        {
            parameter a   { code[i + 1], instruction.param_mode(0) };
            parameter b   { code[i + 2], instruction.param_mode(1) };
            parameter res { code[i + 3], instruction.param_mode(2) };
            return { opcode, { a, b, res} };
        }

        if (opcode == in)
        {
            parameter res { code[i + 1], position };
            return { opcode, { res } };
        }

        if (opcode == out)
        {
            parameter val { code[i + 1], instruction.param_mode(0) };
            return { opcode, { val } };
        }

        if (opcode == jmp_if || opcode == jmp_ifn)
        {
            parameter check  { code[i + 1], instruction.param_mode(0) };
            parameter target { code[i + 2], instruction.param_mode(1) };
            return { opcode, { check, target } };
        }

        if (opcode == less || opcode == eq)
        {
            parameter a   { code[i + 1], instruction.param_mode(0) };
            parameter b   { code[i + 2], instruction.param_mode(1) };
            parameter res { code[i + 3], instruction.param_mode(2) };
            return { opcode, { a, b, res} };
        }

        else throw std::logic_error("Unknown opcode: " + std::to_string(opcode));
    }

}