//
// Created by rnetuka on 28.11.19.
//

// https://adventofcode.com/2019/day/2

#include <fstream>
#include <functional>
#include <map>
#include <string>
#include <vector>

using namespace std;

namespace day2 {

    constexpr int add = 1;
    constexpr int mul = 2;
    constexpr int fin = 99;


    map<int, function<int(int, int)>> operations {
            { add, [](int a, int b) { return a + b; } },
            { mul, [](int a, int b) { return a * b; } }
    };


    vector<int> read_input()
    {
        ifstream stream { "day02/res/input.txt" };

        vector<int> result;
        string token;
        while (getline(stream, token, ','))
            result.push_back(stoi(token));

        stream.close();
        return result;
    }

    int run_code(int noun, int verb)
    {
        vector<int> input = read_input();

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

    int decode()
    {
        int expected_result = 19690720;

        for (int noun = 0; noun < 99; noun++)
            for (int verb = 0; verb < 99; verb++)
                if (run_code(noun, verb) == expected_result)
                    return 100 * noun + verb;

        return -1;
    }

}