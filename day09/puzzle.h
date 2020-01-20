//
// Created by rnetuka on 09.12.19.
//

#pragma once

#include "../intcode/memory.h"
#include "../puzzle.h"

intcode::value_t get_boost_keycode();
intcode::value_t distress_signal_coordinates();

struct day9 : public puzzle {

    std::optional<std::string> expected_answer(int n) const override {
        switch (n) {
            case 1:  return "2457252183";
            case 2:  return "70634";
            default: return std::nullopt;
        }
    }

    std::string answer(int n) const override {
        switch (n) {
            case 1:  return std::to_string(get_boost_keycode());
            case 2:  return std::to_string(distress_signal_coordinates());
            default: return no_answer;
        }
    }

};