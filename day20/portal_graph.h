//
// Created by rnetuka on 20.12.19.
//

#pragma once

#include <map>
#include <set>
#include <string>

#include "../map/coords.h"
#include "portal_maze.h"

struct portal_graph_node
{
    int x, y;
    std::string id;
    std::map<coords, int> neighbors;
};


bool operator<(const portal_graph_node& a, const portal_graph_node& b);
bool operator==(const portal_graph_node& a, const portal_graph_node& b);


class portal_graph
{
private:
    std::set<portal_graph_node> nodes;
    coords entrance;
    coords exit;

    portal_graph_node& get_node(const coords& coords) const;

public:
    explicit portal_graph(const portal_maze& maze);

    void add(int x, int y, const std::string& id = "");
    void connect(coords a, coords b);
    double shortest_path(coords from, coords to) const;
    double shortest_path() const;
};
