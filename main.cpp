//
// Created by rnetuka on 28.11.19.
//

#include <iostream>

#include "day01/puzzle.h"
#include "day02/puzzle.h"
#include "day03/puzzle.h"

using namespace std;

int main()
{
    cout << "Day 1 1st result: " << day1::calculate_fuel() << "\n";
    cout << "Day 1 2nd result: " << day1::recalculate_fuel() << "\n";
    cout << "Day 2 1st result: " << day2::run_code() << "\n";
    cout << "Day 2 2nd result: " << day2::decode() << "\n";
}