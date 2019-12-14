//
// Created by rnetuka on 14.12.19.
//

#pragma once

#include <istream>
#include <string>
#include <vector>

namespace nanofactory {

    struct formula_part
    {
        std::string chemical;
        long count;
    };

    formula_part operator*(const formula_part& part, long n);
    void operator*=(formula_part& part, long n);

    struct formula_t
    {
        std::vector<formula_part> ingredients;
        formula_part result;
    };

    inline std::vector<formula_t> formulas;

    std::istream& operator>>(std::istream& stream, formula_t& ref);
    void operator*=(formula_t& formula, long n);

    formula_t formula_for(const std::string& chemical);

    void aggregate_ingredients(formula_t& formula);

    int weight(const formula_t& formula);

    void expand(formula_t& formula, int level);
    void expand(formula_t& formula);

}