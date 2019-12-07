//
// Created by rnetuka on 05.12.19.
//

#pragma once

#include <vector>

namespace intcd {

    class output {
    private:
        std::vector<int> values_;

    public:
        void operator<<(int value) {
            values_.push_back(value);
        }

        std::vector<int> values() const {
            return std::vector<int> { values_ };
        }
    };

    inline output null_output;

}