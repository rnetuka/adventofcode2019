//
// Created by rnetuka on 21.12.19.
//

#pragma once

#include <string>
#include <vector>

#include "../intcode/computer.h"


class springscript
{
private:
    std::vector<std::string> commands;
    int i = 0;
    int j = 0;

public:
    springscript() = default;
    springscript(const std::initializer_list<std::string>& commands);

    char operator()();
};

using interpreter = intcode::intcode_machine_t<springscript>;