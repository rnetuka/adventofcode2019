//
// Created by rnetuka on 18.12.19.
//

#include <algorithm>
#include <cctype>
#include <deque>
#include <limits>
#include <stack>
#include <string>

#include "graph.h"
#include "maze.h"

using namespace day18;
using namespace std;


graph create_graph(const maze& maze);

/*[[nodiscard]]
graph reduced_graph(const maze& maze)
{
    graph original = create_graph(maze);
    graph reduced;

    reduced.add(maze.starting_position());

    for (auto& [id, coords] : maze.keys()) {
        reduced.add(coords);
    }

    for (auto& [id, coords] : maze.doors()) {
        reduced.add(coords);
    }

    for (auto& [id, dest] : maze.keys()) {
        double length = original.shortest_path(maze.starting_position(), dest);
        reduced.connect(maze.starting_position(), dest, length);
    }

    for (auto& [id, dest] : maze.doors()) {
        double length = original.shortest_path(maze.starting_position(), dest);
        reduced.connect(maze.starting_position(), dest, length);
    }

    for (auto& [id, a] : maze.keys()) {
        for (auto& [id, b] : maze.doors()) {
            int length = original.shortest_path(a, b);
            reduced.connect(a, b, length);
        }
    }
    return reduced;
}*/





class key_collector
{
private:
    string keyring;
    int x, y;

public:
    int steps = 0;
    map<array<int, 4>, int> distances;

public:
    const maze& maze_;
    const graph graph_;

    key_collector(const maze& maze) : maze_ { maze }, graph_ { create_graph(maze) } {
        keyring = "";
        auto [x, y] = maze_.starting_position();
        this->x = x;
        this->y = y;

        for (auto [node, distance] : graph_.shortest_paths({ x, y })) {
            if (maze.is_key(node.x, node.y))
                distances[{ x, y, node.x, node.y }] = distance;
        }

        for (auto [key, location] : maze_.keys()) {
            for (auto [node, distance] : graph_.shortest_paths({ location.x, location.y })) {
                if (maze.is_key(node.x, node.y) && key != node.id)
                    distances[{ location.x, location.y, node.x, node.y }] = distance;
            }
        }
    }

    void pick_up(char key) {
        auto [key_x, key_y] = maze_.keys().at(key);
        /*auto path = shortest_path({ x, y }, { key_x, key_y });
        for (const node& node : path)
            if (maze_.is_key(node.x, node.y))
                keyring += node.id;*/
        keyring += key;
        steps += distances[{ x, y, key_x, key_y }];
        x = key_x;
        y = key_y;
    }

    int steps_taken() const {
        return steps;
    }

    bool has_key(char key) const {
        return keyring.find(key) != string::npos;
    }

    bool has_key_for(char door) const {
        return has_key(tolower(door));
    }

    set<char> missing_keys() const {
        set<char> result;

        for (auto [key, location] : maze_.keys())
            if (keyring.find(key) == string::npos)
                result.insert(key);

        return result;
    }

    bool has_all_keys() const {
        return missing_keys().empty();
    }

    string reachable_keys() const {
        string result;

        map<node, bool> visits;

        stack<node> stack;
        stack.push(graph_.get(x, y));

        while (! stack.empty())
        {
            node n = stack.top();
            stack.pop();

            if (maze_.is_key(n.x, n.y) && !has_key(n.id))
                result += n.id;

            visits[n] = true;

            if (! maze_.is_door(n.x, n.y) || (maze_.is_door(n.x, n.y) && has_key_for(n.id)))
                for (const node& neighbor : graph_.neighbors_of(n))
                    if (! visits[neighbor])
                        stack.push(neighbor);
        }

        return result;
    }
};

int calculate_shortest_route(const key_collector& collector)
{
    graph graph;

    double best = infinity;

    stack<key_collector> stack;
    stack.push(collector);

    while (! stack.empty())
    {
        key_collector collector = stack.top();
        stack.pop();

        if (collector.has_all_keys()) {
            if (collector.steps_taken() < best)
                best = collector.steps_taken();
        }
        else
            for (char key : collector.reachable_keys()) {
                key_collector clone { collector };
                clone.pick_up(key);
                stack.push(clone);
            }
    }

    return best == infinity ? -1 : (int) best;
}

int shortest_path_for_all_keys()
{
    /*maze maze {
        "########################\n"
        "#@..............ac.GI.b#\n"
        "###d#e#f################\n"
        "###A#B#C################\n"
        "###g#h#i################\n"
        "########################\n"
    };*/

    maze maze {
        "#################\n"
        "#i.G..c...e..H.p#\n"
        "########.########\n"
        "#j.A..b...f..D.o#\n"
        "########@########\n"
        "#k.E..a...g..B.n#\n"
        "########.########\n"
        "#l.F..d...h..C.m#\n"
        "#################\n"
    };

    //maze maze = read("day18/res/input.txt");
    key_collector collector { maze };
    auto m = collector.missing_keys();
    auto r = collector.reachable_keys();
    return -1;
    //return calculate_shortest_route(collector);
}


graph create_graph(const maze& maze)
{
    graph graph;

    for (int x = 0; x < maze.width; x++)
        for (int y = 0; y < maze.height; y++) {
            if (! maze.is_wall(x, y))
            {
                graph.add(x, y, maze.object_id(x, y));

                int dx[] = { -1, 1,  0, 0 };
                int dy[] = {  0, 0, -1, 1 };

                for (int i = 0; i < 4; i++)
                {
                    int x2 = x + dx[i];
                    int y2 = y + dy[i];

                    if (x2 >= 0 && x2 < maze.width && y2 >= 0 && y2 < maze.height) {
                        if (! maze.is_wall(x2, y2)) {
                            graph.add(x2, y2, maze.object_id(x2, y2));
                            graph.connect({ x, y }, { x2, y2 });
                        }
                    }
                }
            }
        }
    return graph;
}

