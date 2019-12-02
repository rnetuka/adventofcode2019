//
// Created by rnetuka on 28.11.19.
//

// https://adventofcode.com/2019/day/1

#include <fstream>
#include <vector>

using namespace std;

namespace day1 {

    vector<int> get_modules()
    {
        vector<int> modules;
        ifstream stream { "day01/res/input.txt" };
        while (stream)
        {
            int mass = 0;
            stream >> mass;
            if (mass > 0)
                modules.push_back(mass);
        }
        stream.close();
        return modules;
    }

    int calculate_fuel()
    {
        int result = 0;

        for (int mass : get_modules())
            result += mass / 3 - 2;

        return result;
    }

    int recalculate_fuel(int mass)
    {
        int fuel = 0;
        for (int i = mass / 3 - 2; i > 0; i = i / 3 - 2)
            fuel += i;
        return fuel;
    }

    int recalculate_fuel()
    {
        int result = 0;

        for (int mass : get_modules())
            result += recalculate_fuel(mass);

        return result;
    }

}