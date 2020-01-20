//
// Created by rnetuka on 10.12.19.
//

#pragma once

#include <algorithm>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include <vector>

#include "../graph/graph.h"
#include "../map/coords.h"
#include "../utils.h"

using asteroid = coords;
using asteroid_graph = graph::graph<asteroid>;

constexpr char asteroid_sign = '#';


class asteroid_map {
public:
    const int width;
    const int height;
    const int max_x = width  - 1;
    const int max_y = height - 1;

    asteroid_graph graph;

private:
    asteroid_map(int width, int height);

public:
    static asteroid_map parse(const std::string& str);

    const std::set<asteroid>& asteroids() const;
    void remove(const asteroid& asteroid);
    std::set<asteroid> asteroids_visible_from(const asteroid& a) const;
};

inline auto space_map = asteroid_map::parse(read_file("day10/res/input.txt"));