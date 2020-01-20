//
// Created by rnetuka on 09.01.20.
//

#pragma once

#include <map>
#include <set>
#include <stdexcept>
#include <vector>

namespace graph {

    template <typename Node>
    class tree {
    private:
        std::map<Node, Node> nodes_;
        Node root;

    public:
        tree(Node root) : root { root } {

        }

        std::set<Node> nodes() const {
            std::set<Node> result;

            for (auto& [node, _] : nodes_)
                result.insert(node);

            return result;
        }

        void append(Node node, const Node& parent)
        {
            if (nodes_.find(node) != nodes_.end())
                throw std::logic_error("Node already has a parent!");

            nodes_[node] = parent;
        }

        std::vector<Node> parents_of(const Node& node) const
        {
            std::vector<Node> parents;
            Node current = node;

            while (current != root) {
                current = nodes_.at(current);
                parents.push_back(current);
            }
            return parents;
        }
    };

}