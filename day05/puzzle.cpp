//
// Created by rnetuka on 04.12.19.
//

#include "../intcode/computer.h"

using namespace std;
using namespace intcode;


int run_code(int value)
{
    code code = read("day05/res/input.txt");
    intcode::machine computer;
    computer.in << value;
    computer.run_code(code);
    return computer.out.values.back();
}

int diagnostic_code_for_1() {
    return run_code(1);
}

int diagnostic_code_for_5() {
    return run_code(5);
}