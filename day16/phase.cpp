//
// Created by rnetuka on 17.12.19.
//

#include <map>
#include <vector>

#include "phase.h"

using namespace std;


const vector<int> phase_pattern { 0, 1, 0, -1 };

map<int, phase_t> phase_cache;


phase_generator::phase_generator(int n) : n { n } {

}

int phase_generator::next()
{
    int result = phase_pattern[i % phase_pattern.size()];

    count++;
    if (count == n) {
        i++;
        count = 0;
    }
    return result;
}

phase_t create_phase(int size, int n)
{
    if (phase_cache.find(n) != phase_cache.end())
        return phase_cache[n];

    vector<int> values(size);
    phase_generator generator { n };
    generator.next();   // discard first value

    for (int i = 0; i < size; i++)
        values[i] = generator.next();

    phase_t result { values };
    phase_cache[n] = result;
    return result;
}