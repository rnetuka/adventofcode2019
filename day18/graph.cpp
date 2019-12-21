//
// Created by rnetuka on 19.12.19.
//

#include <algorithm>
#include <stdexcept>
#include <string>

#include "graph.h"

using namespace std;

namespace day18 {

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

    bool operator!=(const node& a, const node& b) {
        return !(a == b);
    }

    void graph::add(int x, int y, char id)
    {
        if (! contains(x, y))
            nodes_.insert({ x, y, id });
    }

    void graph::connect(coords a, coords b, double length)
    {
        if (! contains(a.x, a.y))
            throw logic_error("Graph doesn't contain node: [" + to_string(a.x) + ", " + to_string(a.y) + "]");

        if (! contains(b.x, b.y))
            throw logic_error("Graph doesn't contain node: [" + to_string(b.x) + ", " + to_string(b.y) + "]");

        node& n1 = const_cast<node&>(*nodes_.find(node { a.x, a.y }));
        node& n2 = const_cast<node&>(*nodes_.find(node { b.x, b.y }));
        n1.neighbors[{ b.x, b.y }] = length;
        n2.neighbors[{ a.x, a.y }] = length;
    }

    const node& graph::get(int x, int y) const
    {
        return *find(nodes_.begin(), nodes_.end(), node { x, y });
    }

    const node& graph::get(coords coords) const
    {
        return get(coords.x, coords.y);
    }

    bool graph::contains(int x, int y) const {
        return find(nodes_.begin(), nodes_.end(), node { x, y }) != nodes_.end();
    }

    const set<node>& graph::nodes() const {
        return nodes_;
    }

    set<node> graph::neighbors_of(const node& n) const {
        set<node> result;

        for (auto [coords, distance] : n.neighbors)
            result.insert(get(coords.x, coords.y));

        return result;
    }

    double graph::edge_length(const node& a, const node& b) const {
        return a.neighbors.at({ b.x, b.y });
    }

    map<node, double> graph::shortest_paths(coords from) const
    {
        node source = get(from.x, from.y);
        //node destination = get(to.x, to.y);

        set<node> unvisited;

        map<node, double> dist;
        map<node, optional<node>> prev;

        for (const node& node : nodes_) {
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

            for (const node& neighbor: neighbors_of(current)) {
                double alt = dist[current] + edge_length(current, neighbor);
                if (alt < dist[neighbor]) {
                    dist[neighbor] = alt;
                    prev[neighbor] = current;
                }
            }
        }

        //return dist[destination];
        return dist;
    }

}