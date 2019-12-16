//
// Created by rnetuka on 16.12.19.
//

#pragma once

#include <set>
#include "sectormap.h"

struct node
{
    int x, y;
    std::set<std::pair<int, int>> neighbors;
};

bool operator<(const node& a, const node& b);
bool operator==(const node& a, const node& b);

class graph
{
private:
    std::set<node> nodes;

    graph() = default;


public:
    static graph from_map(const sector_map& map);

    void add(int x, int y);
    void connect(int ax, int bx, int ay, int by);
    bool contains(int x, int y) const;
    int shortest_path(int from_x, int from_y, int to_x, int to_y) const;
    const node& get(int x, int y) const;
};