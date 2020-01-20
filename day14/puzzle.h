//
// Created by rnetuka on 14.12.19.
//

#include "../puzzle.h"

int calculate_required_ore();
long calculate_produced_fuel();

struct day14 : public puzzle {

    std::optional<std::string> expected_answer(int n) const override {
        switch (n) {
            case 1:  return "892207";
            case 2:  return "1935265";
            default: return std::nullopt;
        }
    }

    std::string answer(int n) const override {
        switch (n) {
            case 1:  return std::to_string(calculate_required_ore());
            case 2:  return std::to_string(calculate_produced_fuel());
            default: return no_answer;
        }
    }

};