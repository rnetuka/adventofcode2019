//
// Created by rnetuka on 17.12.19.
//

#pragma once

#include "puzzle.h"

int sum_alignment_parameters();
int collected_space_dust();

struct day17 : public puzzle {

    std::optional<std::string> expected_answer(int n) const override {
        switch (n) {
            case 1:  return "13580";
            case 2:  return "1063081";
            default: return std::nullopt;
        }
    }

    std::string answer(int n) const override {
        switch (n) {
            case 1:  return std::to_string(sum_alignment_parameters());
            case 2:  return std::to_string(collected_space_dust());
            default: return no_answer;
        }
    }

};