//
// Created by rnetuka on 07.12.19.
//

#pragma once

#include "../intcode/computer.h"

namespace day7 {

    class amplifier_io : public input, public output
    {
    private:
        std::deque<int> values_;

    public:
        amplifier_io() = default;
        amplifier_io(std::initializer_list<int> init_list) : values_ { init_list } {

        }

        void operator<<(int i) override {
            values_.push_back(i);
        }

        void operator>>(int& ref) override {
            if (values_.empty())
                throw no_input_exception();
            ref = values_.front();
            values_.pop_front();
        }

        std::vector<int> values() const override {
            return { values_.front(), values_.back() };
        }
    };

    class amplifier {
    private:
        intcode_machine machine;

    public:
        amplifier(amplifier_io& input, amplifier_io& output) : machine { input, output } {

        }

        bool finished() const {
            return machine.finished();
        }

        void run_code(const intcode& code) {
            machine.run_code(code);
        }

        void set_code(const intcode& code) {
            machine.set_code(code);
        }

        void run() {
            machine.run();
        }
    };

}