//
// Created by rnetuka on 07.12.19.
//

#include <stdexcept>
#include <string>

#include "instruction.h"
#include "operation.h"

using namespace std;

namespace intcd {

    operation::operation(int code) : code { code }, parameters { } {

    }

    operation::operation(int code, vector<parameter>&& parameters) : code { code }, parameters { move(parameters) } {

    }

    operation parse_operation(const vector<int>& code, int i)
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

        else throw logic_error("Unknown opcode: " + to_string(opcode));
    }

}