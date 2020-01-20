//
// Created by rnetuka on 03.12.19.
//

#pragma once

#include "puzzle.h"

int password_combinations1();
int password_combinations2();

struct day4 : public puzzle {

    std::optional<std::string> expected_answer(int n) const override {
        switch (n) {
            case 1:  return "1154";
            case 2:  return "750";
            default: return std::nullopt;
        }
    }

    std::string answer(int n) const override {
        switch (n) {
            case 1:  return std::to_string(password_combinations1());
            case 2:  return std::to_string(password_combinations2());
            default: return no_answer;
        }
    }

};