//
// Created by rnetuka on 24.12.19.
//

#pragma once

#include "../puzzle.h"

int biodiversity_rating();

struct day24 : public puzzle {

    std::optional<std::string> expected_answer(int n) const override {
        switch (n) {
            case 1:  return "32511025";
            default: return std::nullopt;
        }
    }

    std::string answer(int n) const override {
        switch (n) {
            case 1:  return std::to_string(biodiversity_rating());
            default: return no_answer;
        }
    }

};