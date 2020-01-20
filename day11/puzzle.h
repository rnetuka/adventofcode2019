//
// Created by rnetuka on 11.12.19.
//

#pragma once

#include "../puzzle.h"

int count_painted_panels();
std::string get_registration_identifier();

struct day11 : public puzzle {

    std::optional<std::string> expected_answer(int n) const override {
        switch (n) {
            case 1:  return "1686";
            default: return std::nullopt;
        }
    }

    std::string answer(int n) const override {
        switch (n) {
            case  1: return std::to_string(count_painted_panels());
            case  2: return "\n" + get_registration_identifier();
            default: return no_answer;
        }
    }

};