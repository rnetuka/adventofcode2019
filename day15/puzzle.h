//
// Created by rnetuka on 16.12.19.
//

#pragma once

#include "../puzzle.h"

int steps_to_oxygen_storage();
int minutes_to_fill_with_oxygen();

struct day15 : public puzzle {

    std::optional<std::string> expected_answer(int n) const override {
        switch (n) {
            case 1:  return "224";
            case 2:  return "284";
            default: return std::nullopt;
        }
    }

    std::string answer(int n) const override {
        switch (n) {
            case 1:  return std::to_string(steps_to_oxygen_storage());
            case 2:  return std::to_string(minutes_to_fill_with_oxygen());
            default: return no_answer;
        }
    }

};