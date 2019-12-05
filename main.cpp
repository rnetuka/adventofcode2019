//
// Created by rnetuka on 28.11.19.
//

#include <iostream>

#include "day01/puzzle.h"
#include "day02/puzzle.h"
#include "day03/puzzle.h"
#include "day04/puzzle.h"
#include "day05/puzzle.h"

using namespace std;
using day5::input;

int main()
{
    cout << "Day 1 1st result: " << day1::calculate_fuel() << "\n";
    cout << "Day 1 2nd result: " << day1::recalculate_fuel() << "\n";
    cout << "Day 2 1st result: " << day2::run_code() << "\n";
    cout << "Day 2 2nd result: " << day2::decode() << "\n";
    cout << "Day 3 1st result: " << day3::closest_intersection_distance() << "\n";
    cout << "Day 3 2nd result: " << day3::min_steps_to_reach_intersection() << "\n";
    cout << "Day 4 1st result: " << day4::password_combinations1() << "\n";
    cout << "Day 4 2nd result: " << day4::password_combinations2() << "\n";
    cout << "Day 5 1st result: " << day5::run_code(input { 1 }) << "\n";
    cout << "Day 5 1st result: " << day5::run_code(input { 5 }) << "\n";
}