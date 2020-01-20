//
// Created by rnetuka on 21.12.19.
//

#pragma once

#include "./puzzle.h"

int hull_damage_reported();
int hull_damage_reported2();

struct day21 : public puzzle {

    std::optional<std::string> expected_answer(int n) const override {
        switch (n) {
            case 1:  return "19360288";
            case 2:  return "1143814750";
            default: return std::nullopt;
        }
    }

    std::string answer(int n) const override {
        switch (n) {
            case 1:  return std::to_string(hull_damage_reported());
            case 2:  return std::to_string(hull_damage_reported2());
            default: return no_answer;
        }
    }

};