//
// Created by rnetuka on 08.12.19.
//

#pragma once

#include <sstream>

#include "../puzzle.h"
#include "image.h"

int fewest_zero_digit_layer();
image decode_message();

struct day8 : public puzzle {

    std::optional<std::string> expected_answer(int n) const override {
        switch (n) {
            case 1:  return "1703";
            case 2:  return "\n"
                "#  #  ##   ##  #### #### \n"
                "#  # #  # #  # #    #    \n"
                "#### #    #    ###  ###  \n"
                "#  # #    # ## #    #    \n"
                "#  # #  # #  # #    #    \n"
                "#  #  ##   ### #    #### \n";
            default: return std::nullopt;
        }
    }

    std::string answer(int n) const override {
        switch (n) {
            case 1:  return std::to_string(fewest_zero_digit_layer());
            case 2:  {
                std::stringstream stream;
                stream << "\n" << decode_message();
                return stream.str();
            }
            default: return no_answer;
        }
    }

};