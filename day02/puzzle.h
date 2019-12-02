//
// Created by rnetuka on 28.11.19.
//

#pragma once

#include <vector>

namespace day2 {

    std::vector<int> read_input();
    int run_code(std::vector<int> input = read_input(), int noun = 12, int verb = 2);
    int decode(std::vector<int> input = read_input());

}