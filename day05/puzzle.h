//
// Created by rnetuka on 04.12.19.
//

#pragma once

#include "puzzle.h"

int diagnostic_code_for_1();
int diagnostic_code_for_5();

struct day5 : public puzzle {

    std::optional<std::string> expected_answer(int n) const override {
        switch (n) {
            case 1:  return "12428642";
            case 2:  return "918655";
            default: return std::nullopt;
        }
    }

    std::string answer(int n) const override {
        switch (n) {
            case 1:  return std::to_string(diagnostic_code_for_1());
            case 2:  return std::to_string(diagnostic_code_for_5());
            default: return no_answer;
        }
    }

};