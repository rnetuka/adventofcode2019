//
// Created by rnetuka on 07.12.19.
//

#pragma once

#include "../intcode/computer.h"

namespace day7 {

    class amplifier_io
    {
    private:
        std::deque<int> values_;

    public:
        amplifier_io() = default;
        amplifier_io(std::initializer_list<int> init_list) : values_ { init_list } {

        }

        void operator<<(int i) {
            values_.push_back(i);
        }

        void operator>>(int& ref) {
            if (values_.empty())
                throw intcd::no_input_exception();
            ref = values_.front();
            values_.pop_front();
        }

        std::vector<int> values() const {
            return { values_.front(), values_.back() };
        }
    };

    using amplifier = intcd::intcode_machine_t<amplifier_io, amplifier_io>;

}