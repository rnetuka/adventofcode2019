//
// Created by rnetuka on 07.12.19.
//

#pragma once

#include "puzzle.h"

int max_thurster_signal1();
int max_thurster_signal2();

struct day7 : public puzzle {

    std::optional<std::string> expected_answer(int n) const override {
        switch (n) {
            case 1:  return "262086";
            case 2:  return "5371621";
            default: return std::nullopt;
        }
    }

    std::string answer(int n) const override {
        switch (n) {
            case 1:  return std::to_string(max_thurster_signal1());
            case 2:  return std::to_string(max_thurster_signal2());
            default: return no_answer;
        }
    }

};