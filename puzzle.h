//
// Created by rnetuka on 08.01.20.
//

#pragma once

#include <optional>
#include <string>

const inline std::string no_answer = "?";

struct puzzle {

    virtual std::optional<std::string> expected_answer(int n) const {
        return std::nullopt;
    }

    virtual std::string answer(int n) const = 0;

    virtual bool is_interactive() const {
        return false;
    }

};

struct interactive_puzzle : public puzzle {

    bool is_interactive() const override {
        return true;
    }

    virtual void run_interactive() const = 0;

};

std::string puzzle_description(int day);
std::string wrap_answer(const puzzle& puzzle, int n);