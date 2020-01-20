//
// Created by rnetuka on 28.11.19.
//

#include <algorithm>
#include <deque>
#include <iostream>
#include <memory>
#include <string>

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
#include "day22/puzzle.h"
#include "day23/puzzle.h"
#include "day24/puzzle.h"
#include "day25/puzzle.h"

using namespace std;


unique_ptr<puzzle> puzzle_for(int day) {
    switch (day) {
        case  1: return make_unique<day1>();
        case  2: return make_unique<day2>();
        case  3: return make_unique<day3>();
        case  4: return make_unique<day4>();
        case  5: return make_unique<day5>();
        case  6: return make_unique<day6>();
        case  7: return make_unique<day7>();
        case  8: return make_unique<day8>();
        case  9: return make_unique<day9>();
        case 10: return make_unique<day10>();
        case 11: return make_unique<day11>();
        case 12: return make_unique<day12>();
        case 13: return make_unique<day13>();
        case 14: return make_unique<day14>();
        case 15: return make_unique<day15>();
        case 16: return make_unique<day16>();
        case 17: return make_unique<day17>();
        case 18: return make_unique<day18>();
        case 19: return make_unique<day19>();
        case 20: return make_unique<day20>();
        case 21: return make_unique<day21>();
        case 22: return make_unique<day22>();
        case 23: return make_unique<day23>();
        case 24: return make_unique<day24>();
        case 25: return make_unique<day25>();
        default: throw invalid_argument("Invalid day number: " + to_string(day));
    }
}

int main(int argc, char* argv[])
{
    if (argc >= 2) {
        deque<string> args { argv + 1, argv + argc };

        // display solution for specific day
        int day = stoi(args.back());
        auto puzzle = puzzle_for(day);

        if (find(args.begin(), args.end(), "-i") != args.end()) {
            if (puzzle->is_interactive())
                dynamic_cast<interactive_puzzle&>(*puzzle).run_interactive();
        } else {
            cout << puzzle_description(day) << "\n";
            cout << wrap_answer(*puzzle, 1) << "\n";
            cout << wrap_answer(*puzzle, 2) << "\n";
            return 0;
        }
    }
    else {
        // display solution for all available days
        for (int day = 1; day <= 25; day++) {
            auto puzzle = puzzle_for(day);
            cout << "Day " << day << ": " << wrap_answer(*puzzle, 1) << "\n";
            cout << "Day " << day << ": " << wrap_answer(*puzzle, 2) << "\n";
        }
    }

}