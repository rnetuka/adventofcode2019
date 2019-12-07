//
// Created by rnetuka on 05.12.19.
//

#pragma once

#include <utility>
#include <initializer_list>
#include <deque>
#include <stdexcept>

namespace day7 {

    class no_input_exception : public std::logic_error {
    public:
        no_input_exception() : std::logic_error("No input available") {

        }
    };


    class input {
    public:
        virtual void operator>>(int& ref) = 0;
    };


    class null_input_t : public input {
    public:
        void operator>>(int& ref) override {
            throw no_input_exception();
        }
    } null_input;


    class std_input : public input {
    private:
        std::deque<int> values;

    public:
        std_input(std::initializer_list<int> init_list) : values { init_list } {

        }

        void operator>>(int& ref) override {
            if (values.empty())
                throw no_input_exception();
            ref = values.front();
            values.pop_front();
        }
    };

}