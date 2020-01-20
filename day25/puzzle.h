//
// Created by rnetuka on 27.12.19.
//

#pragma once

#include "puzzle.h"

void find_password_for_main_airlock();

struct day25 : public  interactive_puzzle {

    std::optional<std::string> expected_answer(int n) const override {
        switch (n) {
            case 1:  return "2424308736";
            default: return std::nullopt;
        }
    }

    std::string answer(int n) const override {
        return no_answer;
    }

    void run_interactive() const override {
        find_password_for_main_airlock();
    }

};