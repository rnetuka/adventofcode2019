//
// Created by rnetuka on 06.12.19.
//

#pragma once

#include "puzzle.h"

int orbit_count_checksum();
int steps_required_to_reach_santa();

struct day6 : public puzzle {

    std::optional<std::string> expected_answer(int n) const override {
        switch (n) {
            case 1:  return "295834";
            case 2:  return "361";
            default: return std::nullopt;
        }
    }

    std::string answer(int n) const override {
        switch (n) {
            case 1:  return std::to_string(orbit_count_checksum());
            case 2:  return std::to_string(steps_required_to_reach_santa());
            default: return no_answer;
        }
    }

};