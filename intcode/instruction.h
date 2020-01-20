//
// Created by rnetuka on 05.12.19.
//

#pragma once

#include <string>

namespace intcode {

    constexpr int opcode_length = 2;
    constexpr int instruction_length = 5;

    struct instruction
    {
        const std::string value;

        instruction(int value);

        int opcode() const;
        int param_mode(int i) const;
    };

}