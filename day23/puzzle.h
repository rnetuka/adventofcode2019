//
// Created by rnetuka on 23.12.19.
//

#pragma once

#include "../puzzle.h"

int value_sent_to_nat();
int value_delivered_by_nat();

struct day23 : public puzzle {

    std::optional<std::string> expected_answer(int n) const override {
        switch (n) {
            case 1:  return "23886";
            case 2:  return "18333";
            default: return std::nullopt;
        }
    }

    std::string answer(int n) const override {
        switch (n) {
            case 1:  return std::to_string(value_sent_to_nat());
            case 2:  return std::to_string(value_delivered_by_nat());
            default: return no_answer;
        }
    }

};