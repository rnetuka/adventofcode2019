//
// Created by rnetuka on 28.12.19.
//

#include "amplifier.h"

using namespace std;
using namespace intcode;


amplifier_input::amplifier_input(output& supplier) : supplier { make_optional(&supplier) } {

}

value_t amplifier_input::operator()() {
    if (values.empty()) {
        if (supplier && ! (*supplier)->empty())
            values.push_back((*supplier)->pop_front());
        else
            throw no_input_exception();
    }
    value_t value = values.front();
    values.pop_front();
    return value;
}

amplifier_input& amplifier_input::operator<<(value_t value) {
    values.push_back(value);
    return *this;
}

amplifier_input connect(output& supplier) {
    return { supplier };
}