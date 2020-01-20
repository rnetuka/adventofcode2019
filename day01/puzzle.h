//
// Created by rnetuka on 28.11.19.
//

#pragma once

#include "../puzzle.h"

int calculate_fuel();
int recalculate_fuel();

struct day1 : public puzzle {

    std::optional<std::string> expected_answer(int n) const override {
        switch (n) {
            case 1:  return "3087896";
            case 2:  return "4628989";
            default: return std::nullopt;
        }
    }

    std::string answer(int n) const override {
        switch (n) {
            case 1:  return std::to_string(calculate_fuel());
            case 2:  return std::to_string(recalculate_fuel());
            default: return no_answer;
        }
    }

};