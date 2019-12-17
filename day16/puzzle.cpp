//
// Created by rnetuka on 17.12.19.
//

#include <cmath>
#include <string>
#include <vector>

#include "../utils.h"
#include "signal.h"
#include "phase.h"

using namespace std;


int first_eight_digits()
{
    string line = read_lines<string>("day16/res/input.txt")[0];

    signal_t signal = input_signal(line);
    signal_t next { signal.size };

    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < signal.size; j++) {
            phase_t phase = create_phase(signal.size, j + 1);
            next[j] = signal * phase;
        }
        signal = next;
    }

    int result = 0;
    for (int i = 0; i < 8; i++) {
        result += signal[i];
        if (i < 8 - 1)
            result *= 10;
    }
    return result;
}