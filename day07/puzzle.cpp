//
// Created by rnetuka on 07.12.19.
//

#include <vector>

#include "../intcode/computer.h"
#include "amplifier.h"

using namespace std;


namespace day7 {

    using phase = vector<int>;

    vector<phase> phase_combinations(int min, int max) {
        vector<phase> result;
        for (int a = min; a < max + 1; a++)
            for (int b = min; b < max + 1; b++)
                if (b != a)
                    for (int c = min; c < max + 1; c++)
                        if (c != b && c != a)
                            for (int d = min; d < max + 1; d++)
                                if (d != c && d != b && d != a)
                                    for (int e = min; e < max + 1; e++)
                                        if(e != d && e != c && e != b && e != a)
                                            result.push_back({ a, b, c, d, e });
        return result;
    }

    int max_thurster_signal(int min_phase, int max_phase)
    {
        intcode code = read("day07/res/input.txt");
        int max_output = -1;

        for (auto phase : phase_combinations(min_phase, max_phase)) {
            amplifier_io a_b { phase[1] };
            amplifier_io b_c { phase[2] };
            amplifier_io c_d { phase[3] };
            amplifier_io d_e { phase[4] };
            amplifier_io e_a { phase[0], 0 };

            amplifier a { e_a, a_b };
            amplifier b { a_b, b_c };
            amplifier c { b_c, c_d };
            amplifier d { c_d, d_e };
            amplifier e { d_e, e_a };

            vector<amplifier*> amplifiers = { &a, &b, &c, &d, &e };

            for (auto amp : amplifiers)
                amp->set_code(code);

            while (! e.finished()) {
                for (auto amp : amplifiers) {
                    try {
                        amp->run();
                    } catch (no_input_exception& ex) {
                        // no input at current phase
                        // run next amplifier to possibly produce input values
                        continue;
                    }
                }
            }
            max_output = max(max_output, e_a.values().back());
        }
        return max_output;
    }

}