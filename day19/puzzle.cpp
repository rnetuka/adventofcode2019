//
// Created by rnetuka on 19.12.19.
//

#include <algorithm>
#include <fstream>
#include <ostream>
#include <set>

#include "../intcode/computer.h"
#include "../map/coords.h"

using namespace intcd;
using namespace std;


struct tractor_beam
{
    int max_x;
    int max_y;
    set<coords> points;
};

tractor_beam detect_tractor_beam(int max_x, int max_y)
{
    intcode code = read("day19/res/input.txt");
    set<coords> points;

    for (int x = 0; x <= max_x; x++) {
        for (int y = 0; y <= max_y; y++) {
            input in { x, y };
            output out;
            intcode_machine computer { in, out };
            computer.run_code(code);

            if (out.values.front() == 1) {
                points.insert({ x, y });
            }
        }
    }
    return { max_x, max_y, points };
}

ostream& operator<<(ostream& stream, const tractor_beam& beam)
{
    for (int y = 0; y <= beam.max_y; y++) {
        for (int x = 0; x <= beam.max_x; x++) {
            if (beam.points.find({ x, y }) == beam.points.end())
                stream << ' ';
            else
                stream << '#';
        }
        stream << '\n';
    }
    return stream;
}

int tractor_beam_points() {
    return detect_tractor_beam(49, 49).points.size();
}

int santas_ship_coords()
{
    /*intcode code = read("day19/res/input.txt");
    input in { x, y };
    output out;
    intcode_machine computer { in, out };
    computer.run_code(code);*/

    tractor_beam beam = detect_tractor_beam(49, 49);
    fstream file { "day19/res/beam.txt", fstream::out };
    file << beam;
    file.close();
    return -1;
}