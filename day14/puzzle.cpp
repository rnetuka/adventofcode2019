//
// Created by rnetuka on 14.12.19.
//

#include <sstream>
#include <vector>

#include "../utils.h"
#include "nanofactory.h"

using namespace nanofactory;
using namespace std;

namespace day14 {

    vector<formula_t> read_formulas()
    {
        vector<formula_t> formulas;
        vector<string> lines = read_lines<string>("day14/res/input.txt");

        for (const string& line : lines) {
            formula_t formula;
            stringstream stream { line };
            stream >> formula;
            formulas.push_back(formula);
        }

        return formulas;
    }

    int calculate_required_ore()
    {
        if (formulas.empty())
            formulas = read_formulas();

        formula_t formula = formula_for("FUEL");
        expand(formula);
        return formula.ingredients[0].count;
    }

    long calculate_produced_fuel(long guess, long capacity, int window_size = 1)
    {
        long max_ore = 0;
        long max_i = 0;

        for (long i = guess; i < guess + window_size; i++)
        {
            formula_t formula = formula_for("FUEL");
            formula *= i;
            expand(formula);

            long ore = formula.ingredients[0].count;

            if (ore > max_ore && ore < capacity) {
                max_ore = ore;
                max_i = i;
            }
        }
        return max_i;
    }

    long calculate_produced_fuel()
    {
        if (formulas.empty())
            formulas = read_formulas();

        int window_size = 100;

        long capacity = 1'000'000'000'000;
        long min_guess = capacity / calculate_required_ore();
        long max_guess = min_guess + 1'000'000;

        while (true) {
            long guess = min_guess + ((max_guess - min_guess) / 2);
            long b = calculate_produced_fuel(guess, capacity);

            if (b > 0)
                min_guess = guess;
            else
                max_guess = guess;

            if (max_guess - min_guess <= window_size)
                return calculate_produced_fuel(min_guess, capacity, window_size);
        }
    }

}