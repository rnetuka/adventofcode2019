//
// Created by rnetuka on 07.12.19.
//

#include "../utils.h"
#include "computer.h"

using namespace std;

namespace intcode {

    code read(const string& path) {
        return read_csv_input<value_t>(path);
    }

}