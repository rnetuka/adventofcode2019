//
// Created by rnetuka on 07.12.19.
//

#include "instruction.h"

using namespace std;

namespace intcd {

    string padded_instruction_str(int value)
    {
        string result = to_string(value);
        result.insert(result.begin(), instruction_length - result.length(), '0');
        return result;
    }

    instruction::instruction(int value) : value { padded_instruction_str(value) } {

    }

    int instruction::opcode() const {
        return stoi(value.substr(value.length() - opcode_length));
    }

    int instruction::operator[](int i) const {
        if (i < 0)
            return value[i] - '0';
        return value[i] - '0';
    }

    int instruction::param_mode(int i) const {
        return (*this)[value.length() - opcode_length - 1 - i];
    }

}