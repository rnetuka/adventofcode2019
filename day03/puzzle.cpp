//
// Created by rnetuka on 02.12.19.
//

/*
 * --- Day 3: Crossed Wires ---
 * The gravity assist was successful, and you're well on your way to the Venus refuelling station. During the rush back
 * on Earth, the fuel management system wasn't completely installed, so that's next on the priority list.
 *
 * Opening the front panel reveals a jumble of wires. Specifically, two wires are connected to a central port and extend
 * outward on a grid. You trace the path each wire takes as it leaves the central port, one wire per line of text (your
 * puzzle input).
 *
 * The wires twist and turn, but the two wires occasionally cross paths. To fix the circuit, you need to find the
 * intersection point closest to the central port. Because the wires are on a grid, use the Manhattan distance for this
 * measurement. While the wires do technically cross right at the central port where they both start, this point does
 * not count, nor does a wire count as crossing with itself.
 *
 * For example, if the first wire's path is R8,U5,L5,D3, then starting from the central port (o), it goes right 8, up 5,
 * left 5, and finally down 3:
 *
 * ...........
 * ...........
 * ...........
 * ....+----+.
 * ....|....|.
 * ....|....|.
 * ....|....|.
 * .........|.
 * .o-------+.
 * ...........
 *
 * Then, if the second wire's path is U7,R6,D4,L4, it goes up 7, right 6, down 4, and left 4:
 *
 * ...........
 * .+-----+...
 * .|.....|...
 * .|..+--X-+.
 * .|..|..|.|.
 * .|.-X--+.|.
 * .|..|....|.
 * .|.......|.
 * .o-------+.
 * ...........
 *
 * These wires cross at two locations (marked X), but the lower-left one is closer to the central port: its distance is
 * 3 + 3 = 6.
 *
 * Here are a few more examples:
 *
 * R75,D30,R83,U83,L12,D49,R71,U7,L72
 * U62,R66,U55,R34,D71,R55,D58,R83 = distance 159
 * R98,U47,R26,D63,R33,U87,L62,D20,R33,U53,R51
 * U98,R91,D20,R16,D67,R40,U7,R15,U6,R7 = distance 135
 * What is the Manhattan distance from the central port to the closest intersection?
 *
 * --- Part Two ---
 * It turns out that this circuit is very timing-sensitive; you actually need to minimize the signal delay.
 *
 * To do this, calculate the number of steps each wire takes to reach each intersection; choose the intersection where
 * the sum of both wires' steps is lowest. If a wire visits a position on the grid multiple times, use the steps value
 * from the first time it visits that position when calculating the total value of a specific intersection.
 *
 * The number of steps a wire takes is the total number of grid squares the wire has entered to get to that location,
 * including the intersection being considered. Again consider the example from above:
 *
 * ...........
 * .+-----+...
 * .|.....|...
 * .|..+--X-+.
 * .|..|..|.|.
 * .|.-X--+.|.
 * .|..|....|.
 * .|.......|.
 * .o-------+.
 * ...........
 *
 * In the above example, the intersection closest to the central port is reached after 8+5+5+2 = 20 steps by the first
 * wire and 7+6+4+3 = 20 steps by the second wire for a total of 20+20 = 40 steps.
 *
 * However, the top-right intersection is better: the first wire takes only 8+5+2 = 15 and the second wire takes only
 * 7+6+2 = 15, a total of 15+15 = 30 steps.
 *
 * Here are the best steps for the extra examples from above:
 *
 * R75,D30,R83,U83,L12,D49,R71,U7,L72
 * U62,R66,U55,R34,D71,R55,D58,R83 = 610 steps
 * R98,U47,R26,D63,R33,U87,L62,D20,R33,U53,R51
 * U98,R91,D20,R16,D67,R40,U7,R15,U6,R7 = 410 steps
 *
 * What is the fewest combined steps the wires must take to reach an intersection?
 */

#include <algorithm>
#include <functional>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "../utils.h"

using namespace std;

namespace day3 {

    struct coords {
        int x, y;
    };

    bool operator==(const coords& a, const coords& b) {
        return a.x == b.x && a.y == b.y;
    }

    bool operator<(const coords& a, const coords& b) {
        return (a.x == b.x) ? a.y < b.y : a.x < b.x;
    }

    const coords central_point { 0, 0 };

    map<char, function<coords(coords, int)>> directions {
        { 'R', [](coords start, int distance) { return coords { start.x + distance, start.y }; } },
        { 'L', [](coords start, int distance) { return coords { start.x - distance, start.y }; } },
        { 'U', [](coords start, int distance) { return coords { start.x, start.y + distance }; } },
        { 'D', [](coords start, int distance) { return coords { start.x, start.y - distance }; } }
    };

    vector<coords> translate_to_coords(const vector<string>& wire);     // forward function declaration

    const vector<coords> wireA = translate_to_coords(read_csv_input<string>("day03/res/wire1.txt"));
    const vector<coords> wireB = translate_to_coords(read_csv_input<string>("day03/res/wire2.txt"));

    vector<coords> translate_to_coords(const vector<string>& wire)
    {
        vector<coords> result { central_point };
        coords wire_end = central_point;
        for (const string& component : wire)
        {
            char direction = component[0];
            int distance = stoi(component.substr(1));

            for (int i = 0; i < distance; i++) {
                auto f = directions[direction];
                wire_end = f(wire_end, 1);
                result.push_back(wire_end);
            }
        }
        return result;
    }

    int distance(const coords& a, const coords& b)
    {
        return abs(a.x - b.x) + abs(a.y - b.y);
    }

    vector<coords> intersection_points()
    {
        vector<coords> intersection(wireA.size());

        set<coords> wireA_set { wireA.begin() + 1, wireA.end() };
        set<coords> wireB_set { wireB.begin() + 1, wireB.end() };

        auto it = set_intersection(
                wireA_set.begin(), wireA_set.end(),
                wireB_set.begin(), wireB_set.end(),
                intersection.begin());

        intersection.resize(it - intersection.begin());
        return intersection;
    }

    int steps_to_reach_point(const vector<coords>& wire, const coords& point)
    {
        auto it = find(wire.begin(), wire.end(), point);

        if (it == wire.end())
            throw invalid_argument("Wire doesn't reach specified point");

        return distance(wire.begin(), it);
    }

    int steps_to_reach_intersection(const coords& point)
    {
        return steps_to_reach_point(wireA, point) + steps_to_reach_point(wireB, point);
    }

    int closest_intersection_distance()
    {
        auto points = intersection_points();

        coords closest = *min_element(points.begin(), points.end(), [](const coords& a, const coords& b) {
            return distance(a, central_point) < distance(b, central_point);
        });

        return distance(closest, central_point);
    }

    int min_steps_to_reach_intersection()
    {
        auto points = intersection_points();

        coords nearest = *min_element(points.begin(), points.end(), [](const coords& a, const coords& b) {
            return steps_to_reach_intersection(a) < steps_to_reach_intersection(b);
        });

        return steps_to_reach_intersection(nearest);
    }

}