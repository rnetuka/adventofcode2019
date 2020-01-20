//
// Created by rnetuka on 17.12.19.
//

#pragma once

#include "../puzzle.h"

int first_eight_digits();
int decoded_message();

struct day16 : public puzzle {

    std::optional<std::string> expected_answer(int n) const override {
        switch (n) {
            case 1:  return "82525123";
            default: return std::nullopt;
        }
    }

    std::string answer(int n) const override {
        switch (n) {
            case 1:  return std::to_string(first_eight_digits());
            case 2:  return std::to_string(decoded_message());
            default: return no_answer;
        }
    }

};