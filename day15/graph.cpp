//
// Created by rnetuka on 16.12.19.
//

#include <algorithm>
#include <climits>
#include <map>
#include <set>
#include <stdexcept>

#include "graph.h"

using namespace std;


bool operator<(const node& a, const node& b) {
    if (a.x < b.x)
        return true;
    else if (a.x == b.x)
        return a.y < b.y;
    else
        return false;
}

bool operator==(const node& a, const node& b) {
    return a.x == b.x && a.y == b.y;
}

graph graph::from_map(const sector_map& map)
{
    graph graph;

    for (int x = map.min_x + 1; x < map.max_x; x++)
        for (int y = map.min_y + 1; y < map.max_y; y++) {
            if (map.is_free_to_move(x, y))
            {
                graph.add(x, y);

                // north
                if (map.is_free_to_move(x, y - 1)) {
                    graph.add(x, y - 1);
                    graph.connect(x, y, x, y - 1);
                }

                // west
                if (map.is_free_to_move(x + 1, y)) {
                    graph.add(x + 1, y);
                    graph.connect(x, y, x + 1, y);
                }

                // south
                if (map.is_free_to_move(x, y + 1)) {
                    graph.add(x, y + 1);
                    graph.connect(x, y, x, y + 1);
                }

                // east
                if (map.is_free_to_move(x - 1, y)) {
                    graph.add(x - 1, y);
                    graph.connect(x, y, x - 1, y);
                }
            }
        }

    return graph;
}

void graph::add(int x, int y)
{
    if (! contains(x, y))
        nodes.insert({ x, y });
}

const node& graph::get(int x, int y) const
{
    return *find(nodes.begin(), nodes.end(), node { x, y });
}

void graph::connect(int ax, int ay, int bx, int by)
{
    if (! contains(ax, ay))
        throw logic_error("Graph doesn't contain node: [" + to_string(ax) + ", " + to_string(ay) + "]");

    if (! contains(bx, by))
        throw logic_error("Graph doesn't contain node: [" + to_string(bx) + ", " + to_string(by) + "]");

    node& a = const_cast<node&>(*nodes.find(node { ax, ay }));
    node& b = const_cast<node&>(*nodes.find(node { bx, by }));
    a.neighbors.insert({ bx, by });
    b.neighbors.insert({ ax, ay });
}

bool graph::contains(int x, int y) const {
    return find(nodes.begin(), nodes.end(), node { x, y }) != nodes.end();
}

int graph::shortest_path(int from_x, int from_y, int to_x, int to_y) const
{
    set<node> unvisited { nodes.begin(), nodes.end() };

    map<node, bool> visits;
    map<node, int> distances;

    for (const node& node : nodes) {
        visits[node] = false;
        distances[node] = INT_MAX;
    }

    distances[{ from_x, from_y }] = 0;

    int current_x = from_x;
    int current_y = from_y;

    node destination { to_x, to_y };

    while (! unvisited.empty()) {
        auto& current = get(current_x, current_y);

        for (auto [neighbor_x, neighbor_y] : current.neighbors) {
            auto neighbor = get(neighbor_x, neighbor_y);
            if (! visits[neighbor]) {
                distances[neighbor] = min(distances[neighbor], distances[current] + 1);
            }
        }

        visits[current] = true;
        unvisited.erase(current);

        if (visits[destination])
            break;

        auto next = min_element(unvisited.begin(), unvisited.end(), [&distances](const node& a, const node& b) {
             return distances[a] < distances[b];
        });
        current_x = next->x;
        current_y = next->y;
    }
    return distances[{ to_x, to_y }];
}