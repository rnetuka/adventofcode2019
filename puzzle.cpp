//
// Created by rnetuka on 08.01.20.
//

#include <iomanip>
#include <sstream>

#include "puzzle.h"
#include "utils.h"

using namespace std;


string puzzle_description(int day) {
    // use leading zeros for one digit numbers to match directories day01-day09
    stringstream stream;
    stream << setw(2) << setfill('0') << day;
    return read_file("day" + stream.str() + "/res/description.txt");
}

string wrap_answer(const puzzle& puzzle, int n) {
    stringstream stream;
    string answer = puzzle.answer(n);

    stream << "Answer " << n << ": " << answer;

    if (string expected = puzzle.expected_answer(n).value_or(""); puzzle.expected_answer(n)) {
        if (answer == expected)
            stream << " (OK)";
        else
            stream << " (Failed! Expected: " << expected << ")";
    }
    return stream.str();
}