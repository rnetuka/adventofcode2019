//
// Created by rnetuka on 27.12.19.
//

#include <stdexcept>

#include "../utils.h"
#include "graph.h"

using namespace std;


orbit_map_t read_orbit_map()
{
    orbit_map_t result { "COM" };

    for (const string& line : read_lines<string>("day06/res/input.txt"))
    {
        int i = line.find(')');

        if (i == string::npos)
            throw logic_error("Invalid text for parsing space object: " + line);

        string parent = line.substr(0, i);
        string child  = line.substr(i + 1);

        result.append(child, parent);
    }
    return result;
}