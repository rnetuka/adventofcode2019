//
// Created by rnetuka on 20.12.19.
//

#pragma once

#include "../puzzle.h"

int shortest_path_through_portal_maze();

struct day20 : public puzzle {

    std::optional<std::string> expected_answer(int n) const override {
        switch (n) {
            case 1:  return "636";
            default: return std::nullopt;
        }
    }

    std::string answer(int n) const override {
        switch (n) {
            case 1:  return std::to_string(shortest_path_through_portal_maze());
            default: return no_answer;
        }
    }

};