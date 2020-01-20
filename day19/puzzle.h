//
// Created by rnetuka on 19.12.19.
//

#pragma once

#include "../puzzle.h"

int tractor_beam_points();
int santas_ship_coords();

struct day19 : public puzzle {

    std::optional<std::string> expected_answer(int n) const override {
        switch (n) {
            case 1:  return "114";
            case 2:  return "10671712";
            default: return std::nullopt;
        }
    }

    std::string answer(int n) const override {
        switch (n) {
            case 1:  return std::to_string(tractor_beam_points());
            case 2:  return std::to_string(santas_ship_coords());
            default: return no_answer;
        }
    }

};