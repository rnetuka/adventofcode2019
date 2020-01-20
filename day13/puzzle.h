//
// Created by rnetuka on 13.12.19.
//

#pragma once

#include "../puzzle.h"

int count_block_tiles();
int beat_the_game();
void play();

struct day13 : public puzzle {

    std::optional<std::string> expected_answer(int n) const override {
        switch (n) {
            case 1:  return "341";
            case 2:  return "17138";
            default: return std::nullopt;
        }
    }

    std::string answer(int n) const override {
        switch (n) {
            case 1:  return std::to_string(count_block_tiles());
            case 2:  return std::to_string(beat_the_game());
            default: return no_answer;
        }
    }

};