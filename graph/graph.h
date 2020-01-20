//
// Created by rnetuka on 08.01.20.
//

#pragma once

#include <algorithm>
#include <climits>
#include <map>
#include <set>

namespace graph {

    template <typename Node>
    struct edge_t {
        Node from;
        Node to;
    };

    template <typename Node>
    class graph
    {
        using edge = edge_t<Node>;

        std::set<Node> nodes_;
        std::set<edge> edges_;

    public:
        const std::set<Node>& nodes() const {
            return nodes_;
        }

        void add_node(const Node& node) {
            nodes_.insert({ node });
        }

        void remove_node(const Node& node) {
            nodes_.erase(node);

            // TODO replace with set::erase_if in C++20
            for (auto it = edges_.begin(); it != edges_.end(); it++) {
                if (auto edge = *it; edge.from == node || edge.to == node) {
                    edges_.erase(it);
                }
            }
        }

        void connect(const Node& a, const Node& b) {
            edges_.insert({ a, b });
        }

        std::set<Node> neighbors_of(const Node& n) const {
            std::set<Node> neighbors;
            for (auto& edge : edges_)
            {
                if (edge.from == n)
                    neighbors.insert(edge.to);

                if (edge.to == n)
                    neighbors.insert(edge.from);
            }
            return neighbors;
        }

        int degree_of(const Node& node) const {
            return neighbors_of(node).size();
        }

        int shortest_path(const Node& from, const Node& destination) const
        {
            std::set<Node> unvisited { nodes_.begin(), nodes_.end() };

            std::map<Node, bool> visits;
            std::map<Node, int> distances;

            for (auto& node : nodes_) {
                visits[node] = false;
                distances[node] = INT_MAX;
            }

            distances[from] = 0;
            Node current = from;

            while (! unvisited.empty()) {
                for (auto& neighbor : neighbors_of(current))
                    if (! visits[neighbor])
                        distances[neighbor] = std::min(distances[neighbor], distances[current] + 1);

                visits[current] = true;
                unvisited.erase(current);

                if (visits[destination])
                    break;

                auto next = *std::min_element(unvisited.begin(), unvisited.end(), [&distances](const Node& a, const Node& b) {
                    return distances[a] < distances[b];
                });
                current = next;
            }
            return distances[destination];
        }
    };

}

template <typename Node>
bool operator==(const graph::edge_t<Node>& a, const graph::edge_t<Node>& b) {
    return (a.from == b.from && a.to == b.to) || (a.from == b.to || a.to == b.from);
}

template <typename Node>
bool operator<(const graph::edge_t<Node>& a, const graph::edge_t<Node>& b) {
    if (a == b)
        return false;
    else
        return (a.from == b.from) ? a.to < b.to : a.from < b.from;
}