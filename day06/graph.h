//
// Created by rnetuka on 06.12.19.
//

#pragma once

#include <map>
#include <stdexcept>
#include <string>
#include <vector>

namespace day6 {

    struct node {
        std::string name;
        node* parent = nullptr;
    };

    bool operator==(const node& a, const node& b) {
        return a.name == b.name;
    }

    struct graph {
        std::map<std::string, node> nodes;

        graph() {
            for (const std::string& line : read_lines<std::string>("day06/res/input.txt"))
                process_input(line);
        }

        void process_input(const std::string& text) {
            int i = text.find(')');

            if (i == std::string::npos)
                throw std::invalid_argument("Invalid text for parsing space object: " + text);

            std::string parent = text.substr(0, i);
            std::string child = text.substr(i + 1);

            if (! contains(parent))
                add({ parent });

            add({ child, get(parent) });
        }

        bool contains(const std::string& node_name) const {
            return nodes.find(node_name) != nodes.end();
        }

        node* get(const std::string& node_name) {
            return contains(node_name) ? &nodes[node_name] : nullptr;
        }

        void add(node&& node) {
            nodes[node.name] = std::move(node);
        }
    } graph;

    std::vector<node> parent_list(const node& n)
    {
        std::vector<node> parents;

        for (node* parent = n.parent; parent; parent = parent->parent)
            parents.push_back(*parent);

        return parents;
    }

}