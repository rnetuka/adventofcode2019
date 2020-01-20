//
// Created by rnetuka on 13.01.20.
//

#include "output.h"

namespace intcode {

    void output::operator<<(value_t value) {
        values.push_back(value);
        for (auto& listener : listeners)
            listener(value);
    }

    bool output::empty() const {
        return values.empty();
    }

    int output::size() const {
        return values.size();
    }

    value_t output::pop_front() {
        if (empty())
            throw std::logic_error("No output values");

        value_t value = values.front();
        values.pop_front();
        return value;
    }

    value_t output::front() const {
        if (empty())
            throw std::logic_error("No output values");

        return values.front();
    }

    value_t output::back() const {
        if (empty())
            throw std::logic_error("No output values");

        return values.back();
    }

    void output::clear() {
        values.clear();
    }

    value_t output::operator[](int i) const {
        return values.at(i);
    }

}