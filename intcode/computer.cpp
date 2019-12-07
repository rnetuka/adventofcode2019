//
// Created by rnetuka on 07.12.19.
//

#include "../utils.h"
#include "computer.h"

using namespace std;

namespace intcd {

    intcode read(const string& path) {
        return read_csv_input<int>(path);
    }

    int extract_value(intcode code, parameter parameter) {
        return parameter.mode == immediate ? parameter.value : code[parameter.value];
    }


    template <>
    intcode_machine_t<input, output>::intcode_machine_t() : input_ { &null_input }, output_ { &null_output } {

    };

}