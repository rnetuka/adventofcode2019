//
// Created by rnetuka on 14.12.19.
//

#include <cmath>
#include <map>
#include <numeric>
#include <sstream>
#include <stdexcept>

#include "nanofactory.h"

using namespace std;

namespace nanofactory {

    istream& operator>>(istream& stream, formula_t& ref)
    {
        string str;
        getline(stream, str);

        string pre;
        string post;

        int i = str.find("=>");
        pre = str.substr(0, i);
        post = str.substr(i + 2);

        stringstream pre_stream { pre };
        string token;
        vector<string> tokens;
        while (getline(pre_stream, token, ',')) {
            int count = 0;
            string chemical;

            stringstream part_stream { token };
            part_stream >> count;
            part_stream >> chemical;

            ref.ingredients.push_back({ chemical, count });
        }

        stringstream post_stream { post };
        post_stream >> ref.result.count;
        post_stream >> ref.result.chemical;

        return stream;
    }

    formula_part operator*(const formula_part& part, long n)
    {
        formula_part result;
        result.chemical = part.chemical;
        result.count = n * part.count;
        return result;
    }

    void operator*=(formula_part& part, long n) {
        part.count *= n;
    }

    void operator*=(formula_t& formula, long n)
    {
        formula.result.count *= n;
        for (auto& requirement : formula.ingredients)
            requirement *= n;
    }

    formula_t formula_for(const std::string& chemical) {
        for (auto& formula : formulas) {
            if (formula.result.chemical == chemical) {
                return formula;
            }
        }
        throw logic_error("No formula exists for creating " + chemical);
    }

    void aggregate_ingredients(formula_t& formula)
    {
        map<string, long> aggregated_ingredients;

        for (auto& requirement : formula.ingredients)
            aggregated_ingredients[requirement.chemical] += requirement.count;

        formula.ingredients.clear();

        for (auto& [chemical, count] : aggregated_ingredients)
            formula.ingredients.push_back({ chemical, count });
    }

    int weight(const formula_t& formula)
    {
        if (formula.ingredients.size() == 1 && formula.ingredients[0].chemical == "ORE")
            return 1;
        else
        {
            int n = -1;

            for (const formula_part& requirement : formula.ingredients)
                n = max(n, weight(formula_for(requirement.chemical)));

            return n + 1;
        }
    }

    void expand(formula_t& formula, int level)
    {
        vector<formula_part> expanded_ingredients;

        for (auto it = formula.ingredients.begin(); it != formula.ingredients.end(); it++)
        {
            formula_part requirement = *it;

            if (requirement.chemical != "ORE") {
                if (auto requirement_formula = formula_for(requirement.chemical); weight(requirement_formula) == level)
                {
                    long multiplier = ceil((long double) requirement.count / requirement_formula.result.count);

                    for (formula_part& part : requirement_formula.ingredients)
                        expanded_ingredients.push_back(part * multiplier);

                }
                else
                    expanded_ingredients.push_back(requirement);
            }
        }
        formula.ingredients = expanded_ingredients;
    }

    void expand(formula_t& formula)
    {
        for (int n = weight(formula); n >= 1; n--)
        {
            expand(formula, n);
            aggregate_ingredients(formula);
        }
    }

}