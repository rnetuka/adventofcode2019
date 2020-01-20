//
// Created by rnetuka on 16.12.19.
//

/*
 * https://adventofcode.com/2019/day/15#part2
 *
 * --- Day 15: Oxygen System ---
 * Out here in deep space, many things can go wrong. Fortunately, many of those things have indicator lights.
 * Unfortunately, one of those lights is lit: the oxygen system for part of the ship has failed!
 *
 * According to the readouts, the oxygen system must have failed days ago after a rupture in oxygen tank two; that
 * section of the ship was automatically sealed once oxygen levels went dangerously low. A single remotely-operated
 * repair droid is your only option for fixing the oxygen system.
 *
 * The Elves' care package included an Intcode program (your puzzle input) that you can use to remotely control
 * the repair droid. By running that program, you can direct the repair droid to the oxygen system and fix the problem.
 *
 * The remote control program executes the following steps in a loop forever:
 *
 * - Accept a movement command via an input instruction.
 * - Send the movement command to the repair droid.
 * - Wait for the repair droid to finish the movement operation.
 * - Report on the status of the repair droid via an output instruction.
 *
 * Only four movement commands are understood: north (1), south (2), west (3), and east (4). Any other command is
 * invalid. The movements differ in direction, but not in distance: in a long enough east-west hallway, a series of
 * commands like 4,4,4,4,3,3,3,3 would leave the repair droid back where it started.
 *
 * The repair droid can reply with any of the following status codes:
 *
 * - 0: The repair droid hit a wall. Its position has not changed.
 * - 1: The repair droid has moved one step in the requested direction.
 * - 2: The repair droid has moved one step in the requested direction; its new position is the location of the oxygen
 *      system.
 *
 * You don't know anything about the area around the repair droid, but you can figure it out by watching the status
 * codes.
 *
 * For example, we can draw the area using D for the droid, # for walls, . for locations the droid can traverse, and
 * empty space for unexplored locations. Then, the initial state looks like this:
 *
 *
 *
 *    D
 *
 *
 * To make the droid go north, send it 1. If it replies with 0, you know that location is a wall and that the droid
 * didn't move:
 *
 *
 *    #
 *    D
 *
 *
 * To move east, send 4; a reply of 1 means the movement was successful:
 *
 *
 *    #
 *    .D
 *
 *
 * Then, perhaps attempts to move north (1), south (2), and east (4) are all met with replies of 0:
 *
 *
 *    ##
 *    .D#
 *     #
 *
 * Now, you know the repair droid is in a dead end. Backtrack with 3 (which you already know will get a reply of 1
 * because you already know that location is open):
 *
 *
 *    ##
 *    D.#
 *     #
 *
 * Then, perhaps west (3) gets a reply of 0, south (2) gets a reply of 1, south again (2) gets a reply of 0, and then
 * west (3) gets a reply of 2:
 *
 *
 *    ##
 *   #..#
 *   D.#
 *    #
 *
 * Now, because of the reply of 2, you know you've found the oxygen system! In this example, it was only 2 moves away
 * from the repair droid's starting position.
 *
 * What is the fewest number of movement commands required to move the repair droid from its starting position to
 * the location of the oxygen system?
 *
 *
 * --- Part Two ---
 * You quickly repair the oxygen system; oxygen gradually fills the area.
 *
 * Oxygen starts in the location containing the repaired oxygen system. It takes one minute for oxygen to spread to all
 * open locations that are adjacent to a location that already contains oxygen. Diagonal locations are not adjacent.
 *
 * In the example above, suppose you've used the droid to explore the area fully and have the following map (where
 * locations that currently contain oxygen are marked O):
 *
 *  ##
 * #..##
 * #.#..#
 * #.O.#
 *  ###
 *
 * Initially, the only location which contains oxygen is the location of the repaired oxygen system. However, after one
 * minute, the oxygen spreads to all open (.) locations that are adjacent to a location containing oxygen:
 *
 *  ##
 * #..##
 * #.#..#
 * #OOO#
 *  ###
 *
 * After a total of two minutes, the map looks like this:
 *
 *  ##
 * #..##
 * #O#O.#
 * #OOO#
 *  ###
 *
 * After a total of three minutes:
 *
 *  ##
 * #O.##
 * #O#OO#
 * #OOO#
 *  ###
 *
 * And finally, the whole region is full of oxygen after a total of four minutes:
 *
 *  ##
 * #OO##
 * #O#OO#
 * #OOO#
 *  ###
 *
 * So, in this example, all locations contain oxygen after 4 minutes.
 *
 * Use the repair droid to get a complete map of the area. How many minutes will it take to fill with oxygen?
 */

#include <fstream>
#include <queue>
#include <stack>
#include <stdexcept>
#include <string>

#include "../intcode/computer.h"
#include "sectormap.h"

using namespace intcode;
using namespace std;


struct command
{
    int id;
    int dx = 0, dy = 0;
    bool backtrack = false;
};

enum command_id
{
    north = 1,
    south = 2,
    west = 3,
    east = 4
};

const command N { north, 0, -1 };
const command S { south, 0, +1 };
const command W { west, -1,  0 };
const command E { east, +1,  0 };

bool operator!=(const command& a, const command& b) {
    return a.id != b.id;
}

command oposite(const command& command) {
    switch (command.id) {
        case north:     return S;
        case south:     return N;
        case west:      return E;
        case east:      return W;
        default:        throw logic_error("Unknown command id: " + to_string(command.id));
    }
}

command backtrack(const command& command) {
    return { command.id, command.dx, command.dy, true };
}

struct movement_commands
{
    queue<command> commands;

    value_t operator()()
    {
        if (commands.empty())
            throw no_input_exception();

        command command = commands.front();
        commands.pop();
        if (command.backtrack)
            return oposite(command).id;
        else
            return command.id;
    }

    void operator<<(const command& order) {
        commands.push(order);
    }
};

struct repair_droid
{
    int x = 0;
    int y = 0;
    movement_commands commands;
    intcode::computer cpu;


    repair_droid() {
        cpu.set_code(read("day15/res/input.txt"));
        cpu.in = [this]() {
            return commands();
        };
    }


    int move(const command& command)
    {
        try {
            commands << command;
            cpu.run();
            return -1;
        }
        catch (const no_input_exception& ex)
        {
            int result = cpu.out.front();

            if (result != wall) {
                if (command.backtrack) {
                    x += oposite(command).dx;
                    y += oposite(command).dy;
                }
                else {
                    x += command.dx;
                    y += command.dy;
                }
            }
            cpu.out.clear();
            return result;
        }
    }

};

void push_commands(const command& move, stack<command>& commands)
{
    vector<command> pool { N, E, S, W };

    commands.push(backtrack(move));

    for (const command& command : pool)
        if (command != oposite(move))
            commands.push(command);
}

sector_map scout_sector()
{
    repair_droid droid;

    sector_map_builder map_builder;
    map_builder.add(droid.x, droid.y, ::empty);

    stack<command> stack;
    stack.push(W);
    stack.push(S);
    stack.push(E);
    stack.push(N);

    while (! stack.empty())
    {
        command command = stack.top();
        stack.pop();

        int x = droid.x + command.dx;
        int y = droid.y + command.dy;

        if (command.backtrack) {
            droid.move(command);
            continue;
        }

        if (map_builder.contains(x, y))
            continue;

        int result = droid.move(command);
        map_builder.add(x, y, result);

        if (result != wall)
            push_commands(command, stack);
    }

    auto map = map_builder.create_sector_map();

    fstream file { "day15/res/sector_map.txt", ios::out };
    file << map;
    file.close();

    return map;
}

int steps_to_oxygen_storage()
{
    auto sector_map = scout_sector();
    auto graph = graph_from_map(sector_map);
    coords start { 0, 0 };
    coords oxygen_system = *sector_map.find_oxygen_system();
    return graph.shortest_path(start, oxygen_system);
}

int minutes_to_fill_with_oxygen()
{
    auto sector_map = scout_sector();
    auto graph = graph_from_map(sector_map);
    coords oxygen_system = *sector_map.find_oxygen_system();

    set<coords> oxygen_spreading_nodes;
    oxygen_spreading_nodes.insert(oxygen_system);

    map<coords, bool> oxygen;
    oxygen[oxygen_system] = true;

    int minutes = 0;

    while (true)
    {
        set<coords> next_oxygen_spreading_nodes;

        for (auto& node : oxygen_spreading_nodes)
            for (auto& neighbor : graph.neighbors_of(node))
                if (! oxygen[neighbor]) {
                    oxygen[neighbor] = true;
                    next_oxygen_spreading_nodes.insert(neighbor);
                }

        if (next_oxygen_spreading_nodes.empty())
            break;

        oxygen_spreading_nodes = next_oxygen_spreading_nodes;
        minutes++;
    }

    return minutes;
}
