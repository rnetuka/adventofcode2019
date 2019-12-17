//
// Created by rnetuka on 28.11.19.
//

#include <iostream>

#include "intcode/input.h"
#include "day01/puzzle.h"
#include "day02/puzzle.h"
#include "day03/puzzle.h"
#include "day04/puzzle.h"
#include "day05/puzzle.h"
#include "day06/puzzle.h"
#include "day07/puzzle.h"
#include "day08/puzzle.h"
#include "day09/puzzle.h"
#include "day10/puzzle.h"
#include "day11/puzzle.h"
#include "day12/puzzle.h"
#include "day13/puzzle.h"
#include "day14/puzzle.h"
#include "day15/puzzle.h"
#include "day16/puzzle.h"

using namespace std;
using intcd::input;

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
    cout << "Day 6 1st result: " << day6::orbit_count_checksum() << "\n";
    cout << "Day 6 2nd result: " << day6::steps_required() << "\n";
    cout << "Day 7 1st result: " << day7::max_thurster_signal(0, 4) << "\n";
    cout << "Day 7 2nd result: " << day7::max_thurster_signal(5, 9) << "\n";
    cout << "Day 8 1st result: " << day8::fewest_zero_digit_layer() << "\n";
    cout << "Day 8 2nd result:\n" << day8::decode_message() << "\n";
    cout << "Day 9 1st result: " << day9::get_boost_keycode() << "\n";
    cout << "Day 9 2nd result: " << day9::distress_signal_coordinates() << "\n";
    cout << "Day 10 1st result: " << day10::count_asteroids() << "\n";
    cout << "Day 10 2nd result: " << day10::destroyed_asteroid_number() << "\n";
    cout << "Day 11 1st result: " << day11::count_painted_panels() << "\n";
    cout << "Day 11 2nd result:\n" << day11::get_registration_identifier() << "\n";
    cout << "Day 12 1st result: " << day12::system_total_energy() << "\n";
    cout << "Day 12 2nd result: " << day12::steps_to_repeat() << "\n";
    cout << "Day 13 1st result: " << day13::count_block_tiles() << "\n";
    cout << "Day 13 2nd result: " << day13::beat_the_game() << "\n";
    cout << "Day 14 1st result: " << day14::calculate_required_ore() << "\n";
    cout << "Day 14 2nd result: " << day14::calculate_produced_fuel() << "\n";
    cout << "Day 15 1st result: " << steps_to_oxygen_storage() << "\n";
    cout << "Day 15 2nd result: " << minutes_to_fill_with_oxygen() << "\n";
    cout << "Day 16 1st result: " << first_eight_digits() << "\n";
}