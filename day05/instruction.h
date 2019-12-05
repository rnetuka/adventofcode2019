//
// Created by rnetuka on 05.12.19.
//

#pragma once

#include <string>

namespace day5 {

    constexpr int opcode_length = 2;
    constexpr int instruction_length = 5;

    std::string padded_instruction_str(int value)
    {
        std::string result = std::to_string(value);
        result.insert(result.begin(), instruction_length - result.length(), '0');
        return result;
    }

    struct instruction
    {
        const std::string value;

        instruction(int value) : value { padded_instruction_str(value) } {

        }

        int opcode() const {
            return std::stoi(value.substr(value.length() - opcode_length));
        }

        int operator[](int i) const {
            if (i < 0)
                return value[i] - '0';
            return value[i] - '0';
        }

        int param_mode(int i) const {
            return (*this)[value.length() - opcode_length - 1 - i];
        }
    };

}