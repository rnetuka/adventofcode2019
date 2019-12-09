 //
// Created by rnetuka on 07.12.19.
//

#include <map>
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

    std::map<int, int> operands {
        { fin,     0 },
        { add,     3 },
        { mul,     3 },
        { in,      1 },
        { out,     1 },
        { jmp_if,  2 },
        { jmp_ifn, 2 },
        { less,    3 },
        { eq,      3 },
        { rel,     1 }
    };

    operation parse_operation(const intcode& code, int i)
    {
        instruction instruction { (int) code[i] };

        int opcode = instruction.opcode();
        int n = operands[opcode];

        vector<parameter> parameters;
        for (int j = 0; j < n; j++)
            parameters.push_back({ code[i + j + 1], instruction.param_mode(j) });

        return { opcode, move(parameters) };
    }

}