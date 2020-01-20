//
// Created by rnetuka on 10.12.19.
//

#pragma once

#include "../puzzle.h"

int max_visible_asteroids();
int destroyed_asteroid_number();

struct day10 : public puzzle {

    std::optional<std::string> expected_answer(int n) const override {
        switch (n) {
            case 1:  return "278";
            case 2:  return "1417";
            default: return std::nullopt;
        }
    }

    std::string answer(int n) const override {
        switch (n) {
            case 1:  return std::to_string(max_visible_asteroids());
            case 2:  return std::to_string(destroyed_asteroid_number());
            default: return no_answer;
        }
    }

};