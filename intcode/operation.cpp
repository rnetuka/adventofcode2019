 //
// Created by rnetuka on 07.12.19.
//

#include <map>
#include <stdexcept>
#include <string>

#include "instruction.h"
#include "operation.h"

using namespace std;

namespace intcode {

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

    operation parse_operation(const code& code, int i)
    {
        instruction instruction { (int) code[i] };

        int opcode = instruction.opcode();
        int n = operands[opcode];

        vector<parameter> parameters(n);
        for (int j = 0; j < n; j++) {
            parameter p { code[i + j + 1], instruction.param_mode(j) };
            parameters[j] = p;
        }

        return { opcode, move(parameters) };
    }

}