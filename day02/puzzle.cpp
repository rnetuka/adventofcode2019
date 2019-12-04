//
// Created by rnetuka on 28.11.19.
//

// https://adventofcode.com/2019/day/2

#include <fstream>
#include <functional>
#include <map>
#include <string>
#include <vector>

#include "../utils.h"

using namespace std;


namespace day2 {

    enum opcode {
        add = 1, mul = 2, fin = 99
    };

    map<int, function<int(int, int)>> operations {
            { add, [](int a, int b) { return a + b; } },
            { mul, [](int a, int b) { return a * b; } }
    };


    int run_code(vector<int> input, int noun, int verb)
    {
        input[1] = noun;
        input[2] = verb;

        for (int i = 0; i < input.size(); )
        {
            int opcode = input[i];

            if (opcode == fin)
                break;

            if (opcode == add || opcode == mul)
            {
                int a_i = input[i + 1];
                int b_i = input[i + 2];
                int res_i = input[i + 3];
                auto operation = operations[opcode];
                int a = input[a_i];
                int b = input[b_i];
                input[res_i] = operation(a, b);
                i += 4;
            }
            else throw logic_error("Unknown opcode: " + to_string(opcode));
        }
        return input[0];
    }

    int run_code()
    {
        vector<int> input = read_csv_input<int>("day02/res/input.txt");
        int noun = 12;
        int verb = 2;
        return run_code(input, noun, verb);
    }

    int decode()
    {
        vector<int> input = read_csv_input<int>("day02/res/input.txt");

        int expected_result = 19690720;

        for (int noun = 0; noun < 99; noun++)
            for (int verb = 0; verb < 99; verb++)
                if (run_code(input, noun, verb) == expected_result)
                    return 100 * noun + verb;

        return -1;
    }

}