//
// Created by rnetuka on 12.12.19.
//

#pragma once

#include "puzzle.h"

int system_total_energy();
long steps_to_repeat();

struct day12 : public puzzle {

    std::optional<std::string> expected_answer(int n) const override {
        switch (n) {
            case 1:  return "7077";
            case 2:  return "402951477454512";
            default: return std::nullopt;
        }
    }

    std::string answer(int n) const override {
        switch (n) {
            case 1:  return std::to_string(system_total_energy());
            case 2:  return std::to_string(steps_to_repeat());
            default: return no_answer;
        }
    }

};