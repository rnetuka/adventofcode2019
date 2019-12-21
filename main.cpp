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
#include "day17/puzzle.h"
#include "day18/puzzle.h"
#include "day19/puzzle.h"
#include "day20/puzzle.h"
#include "day21/puzzle.h"

using namespace std;

template <typename T>
void display_answer(int n, const T& result, const T& expected)
{
    if (result != expected)
        throw logic_error("Result is not equal to expected value");

    cout << "Answer " << n << ": " << result << " OK\n";
}

template <typename T>
void display_answer(int n, const T& result)
{
    cout << "Answer " << n << ": " << result << " (?)\n";
}

int main()
{
    cout << "--- Day 1: The Tyranny of the Rocket Equation ---\n";
    display_answer(1, calculate_fuel(), 3087896);
    display_answer(2, recalculate_fuel(), 4628989);
    cout << "\n";

    cout << "--- Day 2: 1202 Program Alarm ---\n";
    display_answer(1, value_at_position_0(), 3931283);
    display_answer(2, decode_output(), 6979);
    cout << "\n";

    cout << "--- Day 3: Crossed Wires ---\n";
    display_answer(1, closest_intersection_distance(), 280);
    display_answer(2, min_steps_to_reach_intersection(), 10554);
    cout << "\n";

    cout << "--- Day 4: Secure Container ---\n";
    display_answer(1, day4::password_combinations1(), 1154);
    display_answer(2, day4::password_combinations2(), 750);
    cout << "\n";

    cout << "--- Day 5: Sunny with a Chance of Asteroids ---\n";
    display_answer(1, day5::run_code(intcd::input { 1 }), 12428642);
    display_answer(2, day5::run_code(intcd::input { 5 }), 918655);
    cout << "\n";

    cout << "--- Day 6: Universal Orbit Map ---\n";
    display_answer(1, day6::orbit_count_checksum(), 295834);
    display_answer(2, day6::steps_required(), 361);
    cout << "\n";

    cout << "--- Day 7: Amplification Circuit ---\n";
    display_answer(1, day7::max_thurster_signal(0, 4), 262086);
    display_answer(2, day7::max_thurster_signal(5, 9), 5371621);
    cout << "\n";

    cout << "--- Day 8: Space Image Format ---\n";
    display_answer(1, day8::fewest_zero_digit_layer(), 1703);
    cout << "Answer 2:\n" << day8::decode_message() << "\n";    //HCGFE
    cout << "\n";

    cout << "--- Day 9: Sensor Boost ---\n";
    display_answer(1, day9::get_boost_keycode(), 2457252183LL);
    display_answer(2, day9::distress_signal_coordinates(), 70634LL);
    cout << "\n";

    cout << "--- Day 10: Monitoring Station ---\n";
    display_answer(1, day10::count_asteroids(), 278);
    display_answer(2, day10::destroyed_asteroid_number(), 1417);
    cout << "\n";

    cout << "--- Day 11: Space Police ---\n";
    display_answer(1, day11::count_painted_panels(), 1686);
    cout << "Answer 2:\n" << day11::get_registration_identifier() << "\n";
    cout << "\n";

    cout << "--- Day 12: The N-Body Problem ---\n";
    display_answer(1, day12::system_total_energy(), 7077);
    display_answer(2, day12::steps_to_repeat(), 402951477454512L);
    cout << "\n";

    cout << "--- Day 13: Care Package ---\n";
    display_answer(1, day13::count_block_tiles(), 341);
    display_answer(2, day13::beat_the_game(), 17138);
    cout << "\n";

    cout << "--- Day 14: Space Stoichiometry ---\n";
    display_answer(1, day14::calculate_required_ore(), 892207);
    display_answer(2, day14::calculate_produced_fuel(), 1935265L);
    cout << "\n";

    cout << "--- Day 15: Oxygen System ---\n";
    display_answer(1, steps_to_oxygen_storage(), 224);
    display_answer(2, minutes_to_fill_with_oxygen(), 284);
    cout << "\n";

    cout << "--- Day 16: Flawed Frequency Transmission ---\n";
    display_answer(1, first_eight_digits(), 82525123);
    cout << "\n";

    cout << "--- Day 17: Set and Forget ---\n";
    display_answer(1, sum_alignment_parameters(), 13580);
    display_answer(2, collected_space_dust(), 1063081);
    cout << "\n";

    cout << "--- Day 18: Many-Worlds Interpretation ---\n";
    //display_answer(1, shortest_path_for_all_keys());
    cout << "\n";

    cout << "--- Day 19: Tractor Beam ---\n";
    display_answer(1, tractor_beam_points(), 114);
    //display_answer(2, santas_ship_coords());
    cout << "\n";

    cout << "--- Day 20: Donut Maze ---\n";
    display_answer(1, shortest_path_through_portal_maze(), 636);    // Takes forever to complete
    cout << "\n";

    cout << "--- Day 21: Springdroid Adventure ---\n";
    display_answer(1, hull_damage_reported(), 19360288);
    display_answer(2, hull_damage_reported2(), 1143814750);
    cout << "\n";
}