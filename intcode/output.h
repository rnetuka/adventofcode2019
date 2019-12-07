//
// Created by rnetuka on 05.12.19.
//

#pragma once

#include <vector>

namespace day7 {

    class output {
    public:
        virtual void operator<<(int value) = 0;
        virtual std::vector<int> values() const = 0;
    };


    class null_output_t : public output {
    public:
        void operator<<(int value) override {
            // ignore output values
        }
        std::vector<int> values() const override {
            return { };
        }
    } null_output;


    class std_output : public output {
    private:
        std::vector<int> values_;

    public:
        void operator<<(int value) override {
            values_.push_back(value);
        }

        std::vector<int> values() const override {
            return std::vector<int> { values_ };
        }
    };

}