//
// Created by rnetuka on 05.12.19.
//

#pragma once

#include <initializer_list>
#include <queue>

namespace day5 {

    class input {
    private:
        std::queue<int> values;

    public:
        input(std::initializer_list<int> init_list) : values { init_list } {

        }

        void operator>>(int& ref) {
            ref = values.front();
            values.pop();
        }
    };

}