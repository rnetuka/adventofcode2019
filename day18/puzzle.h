//
// Created by rnetuka on 18.12.19.
//

#pragma once

#include "../puzzle.h"

int shortest_path_for_all_keys();

struct day18 : public puzzle {

    std::optional<std::string> expected_answer(int n) const override {
        return std::nullopt;
    }

    std::string answer(int n) const override {
        return no_answer;
    }

};