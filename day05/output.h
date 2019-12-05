//
// Created by rnetuka on 05.12.19.
//

#pragma once

#include <vector>

namespace day5 {

    class output
    {
    private:
        std::vector<int> values;

    public:
        void operator<<(int value) {
            values.push_back(value);
        }

        int back() const {
            return values.back();
        }
    } output;

}