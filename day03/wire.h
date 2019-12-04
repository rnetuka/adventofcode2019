//
// Created by rnetuka on 04.12.19.
//

#pragma once

#include <functional>
#include <map>
#include <string>
#include <vector>

#include "../utils.h"
#include "coords.h"

using namespace std;


namespace day3 {

    const coords central_point { 0, 0 };

    map<char, function<coords(coords, int)>> directions {
            { 'R', [](coords start, int distance) { return coords { start.x + distance, start.y }; } },
            { 'L', [](coords start, int distance) { return coords { start.x - distance, start.y }; } },
            { 'U', [](coords start, int distance) { return coords { start.x, start.y + distance }; } },
            { 'D', [](coords start, int distance) { return coords { start.x, start.y - distance }; } }
    };

    vector<coords> read_wire(const string& path) {
        auto wire_description = read_csv_input<string>(path);
        vector<coords> wire { central_point };

        for (const string& component : wire_description)
        {
            char direction = component[0];
            int distance = stoi(component.substr(1));

            for (int i = 0; i < distance; i++) {
                auto f = directions[direction];
                wire.push_back(f(wire.back(), 1));
            }
        }
        return wire;
    }

}