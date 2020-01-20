//
// Created by rnetuka on 02.12.19.
//

#pragma once

#include "puzzle.h"

int closest_intersection_distance();
int min_steps_to_reach_intersection();

struct day3 : public puzzle {

    std::optional<std::string> expected_answer(int n) const override {
        switch (n) {
            case 1:  return "280";
            case 2:  return "10554";
            default: return std::nullopt;
        }
    }

    std::string answer(int n) const override {
        switch (n) {
            case 1:  return std::to_string(closest_intersection_distance());
            case 2:  return std::to_string(min_steps_to_reach_intersection());
            default: return no_answer;
        }
    }

};