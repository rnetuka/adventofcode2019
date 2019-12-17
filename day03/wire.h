//
// Created by rnetuka on 04.12.19.
//

#pragma once

#include <functional>
#include <map>
#include <string>
#include <vector>

#include "../map/coords.h"
#include "../utils.h"

using namespace std;

const coords central_point { 0, 0 };

map<char, function<coords(coords)>> directions {
    { 'R', [](coords start) { return coords { start.x + 1, start.y }; } },
    { 'L', [](coords start) { return coords { start.x - 1, start.y }; } },
    { 'U', [](coords start) { return coords { start.x, start.y + 1 }; } },
    { 'D', [](coords start) { return coords { start.x, start.y - 1 }; } }
};

vector<coords> read_wire(const string& path)
{
    auto description = read_csv_input<string>(path);
    vector<coords> wire { central_point };

    for (const string& component : description)
    {
        char direction = component[0];
        int distance = stoi(component.substr(1));

        for (int i = 0; i < distance; i++) {
            auto f = directions[direction];
            wire.push_back(f(wire.back()));
        }
    }
    return wire;
}