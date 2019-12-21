//
// Created by rnetuka on 20.12.19.
//

#include <algorithm>
#include <limits>
#include <map>
#include <set>

#include "../map/coords.h"
#include "portal_graph.h"

using namespace std;
using node = portal_graph_node;

const double infinity = numeric_limits<double>::infinity();


bool operator<(const portal_graph_node& a, const portal_graph_node& b) {
    return coords { a.x, a.y } < coords { b.x, b.y };
}

bool operator==(const portal_graph_node& a, const portal_graph_node& b) {
    return a.x == b.x && a.y == b.y && a.id == b.id;
}

portal_graph::portal_graph(const portal_maze& maze)
{
    for (int x = 2; x < maze.width() - 2; x++) {
        for (int y = 2; y < maze.height() - 2; y++)
        {
            if (maze.is_wall(x, y))
                continue;
            else if (maze.is_empty(x, y))
                add(x, y);
            else
                add(x, y, maze.id_of(x, y));

            int dx[] = { -1, 1,  0, 0 };
            int dy[] = {  0, 0, -1, 1 };

            for (int i = 0; i < 4; i++) {
                int x2 = x + dx[i];
                int y2 = y + dy[i];

                if (maze.is_empty(x2, y2) || maze.is_portal(x2, y2)) {
                    add(x2, y2, maze.id_of(x2, y2));
                    connect({ x, y }, { x2, y2 });
                }
            }
        }
    }
    for (const string& portal : maze.portals()) {
        auto [side_a, side_b] = maze.portal_exits(portal);
        connect(side_a, side_b);
    }
    entrance = maze.entrance();
    exit = maze.exit();
}

void portal_graph::add(int x, int y, const std::string& id) {
    nodes.insert({ x, y, id });
}

void portal_graph::connect(coords a, coords b) {
    get_node(a).neighbors[b] = 1;
    get_node(b).neighbors[a] = 1;
}

node& portal_graph::get_node(const coords& coords) const {
    return const_cast<node&>(*nodes.find({ coords.x, coords.y }));
}

double portal_graph::shortest_path(coords from, coords to) const {
    node source = get_node(from);
    node destination = get_node(to);

    set<node> unvisited;

    map<node, double> dist;
    map<node, optional<node>> prev;

    for (const node& node : nodes) {
        dist[node] = infinity;
        prev[node] = nullopt;
        unvisited.insert(node);
    }

    dist[source] = 0;

    while (! unvisited.empty()) {
        node current = *min_element(unvisited.begin(), unvisited.end(), [&dist](const node& a, const node& b) {
            return dist[a] < dist[b];
        });

        unvisited.erase(current);

        for (auto [coords, distance] : current.neighbors) {
            node neighbor = get_node(coords);
            double alt = dist[current] + distance;
            if (alt < dist[neighbor]) {
                dist[neighbor] = alt;
                prev[neighbor] = current;
            }
        }
    }

    return dist[destination];
}

double portal_graph::shortest_path() const {
    return shortest_path(entrance, exit);
}