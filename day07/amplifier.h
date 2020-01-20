//
// Created by rnetuka on 07.12.19.
//

#pragma once

#include <deque>

#include "../intcode/computer.h"


class amplifier_input
{
    std::deque<intcode::value_t> values;
    std::optional<intcode::output*> supplier;

public:
    amplifier_input() = default;
    amplifier_input(intcode::output& supplier);

    intcode::value_t operator()();
    amplifier_input& operator<<(intcode::value_t value);
};

amplifier_input connect(intcode::output& supplier);

using amplifier = intcode::intcode_machine_t<amplifier_input>;