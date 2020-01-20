//
// Created by rnetuka on 28.11.19.
//

#pragma once

#include "../puzzle.h"

int value_at_position_0();
int decode_output();

struct day2 : public puzzle {

    std::optional<std::string> expected_answer(int n) const override {
        switch (n) {
            case 1:  return "3931283";
            case 2:  return "6979";
            default: return std::nullopt;
        }
    }

    std::string answer(int n) const override {
        switch (n) {
            case 1:  return std::to_string(value_at_position_0());
            case 2:  return std::to_string(decode_output());
            default: return no_answer;
        }
    }

};