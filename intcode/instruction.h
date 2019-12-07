//
// Created by rnetuka on 05.12.19.
//

#pragma once

#include <string>

namespace intcd {

    constexpr int opcode_length = 2;
    constexpr int instruction_length = 5;

    std::string padded_instruction_str(int value);

    struct instruction
    {
        const std::string value;

        instruction(int value);

        int opcode() const;
        int operator[](int i) const;
        int param_mode(int i) const;
    };

}