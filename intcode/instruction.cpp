//
// Created by rnetuka on 07.12.19.
//

#include "instruction.h"

using namespace std;

namespace intcd {

    string padded_instruction_str(int value)
    {
        string result = to_string(value);
        int n = instruction_length - result.length();
        result.insert(result.begin(), n, '0');
        return result;
    }

    instruction::instruction(int value) : value { padded_instruction_str(value) } {

    }

    int instruction::opcode() const {
        return stoi(value.substr(value.length() - opcode_length));
    }

    int instruction::param_mode(int i) const {
        int j = value.length() - opcode_length - 1 - i;
        return value[j] - '0';
    }

}