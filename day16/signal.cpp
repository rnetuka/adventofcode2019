//
// Created by rnetuka on 17.12.19.
//

#include <cmath>

#include "signal.h"

using namespace std;


signal_t input_signal(const string& line)
{
    vector<int> signal;

    for (char digit : line)
        signal.push_back(digit - '0');

    return { signal };
}

int operator*(const signal_t& signal, const phase_t& phase)
{
    int result = 0;

    for (int i = 0; i < signal.size; i++)
        result += signal[i] * phase[i];

    return abs(result) % 10;
}