//
// Created by rnetuka on 27.12.19.
//

#include <map>

#include "../utils.h"
#include "wire.h"

using namespace std;


coords direction(char c) {
    static map<char, coords> directions {
        { 'R', {  1,  0 } },
        { 'L', { -1,  0 } },
        { 'U', {  0,  1 } },
        { 'D', {  0, -1 } }
    };
    return directions.at(c);
}

wire read_wire(const string& path)
{
    auto components = read_csv_input<string>(path);
    wire wire { central_point };

    for (const string& component : components)
    {
        auto next = direction(component[0]);
        int distance = stoi(component.substr(1));

        for (int i = 0; i < distance; i++)
            wire += next;
    }
    return wire;
}

void operator+=(wire& wire, const coords& next) {
    wire.push_back(wire.back() + next);
}