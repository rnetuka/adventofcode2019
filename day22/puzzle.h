//
// Created by rnetuka on 22.12.19.
//

#pragma once

#include "../puzzle.h"

int position_of_2019();
long position_of_2020();

struct day22 : public puzzle {

    std::optional<std::string> expected_answer(int n) const override {
        switch (n) {
            case 1:  return "2939";
            default: return std::nullopt;
        }
    }

    std::string answer(int n) const override {
        switch (n) {
            case 1:  return std::to_string(position_of_2019());
            default: return no_answer;
        }
    }

};