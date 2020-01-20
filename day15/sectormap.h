//
// Created by rnetuka on 16.12.19.
//

#pragma once

#include <optional>
#include <ostream>
#include <vector>

#include "../map/coords.h"
#include "../graph/graph.h"

enum tile_value
{
    wall = 0,
    empty = 1,
    oxygen_system = 2
};

struct location
{
    int x, y;
    int value = -1;
};


class sector_map
{
private:
    int offset_x = 0;
    int offset_y = 0;
    std::vector<std::vector<tile_value>> tiles;

    void set(int x, int y, tile_value tile);

public:
    const int width;
    const int height;

    int min_x = 0;
    int max_x = min_x + width;
    int min_y = 0;
    int max_y = min_y + height;

    sector_map(int width, int height);

    tile_value get(int x, int y) const;

    std::optional<coords> find_oxygen_system() const;
    bool is_free_to_move(int x, int y) const;

    friend class sector_map_builder;
    friend std::ostream& operator<<(std::ostream& stream, const sector_map& graph);
};


class sector_map_builder
{
private:
    std::vector<location> nodes;
    int min_x = 0;
    int max_x = 0;
    int min_y = 0;
    int max_y = 0;

public:
    std::optional<tile_value> get(int x, int y) const;
    void add(int x, int y, int tile);
    bool contains(int x, int y) const;

    sector_map create_sector_map() const;
};

graph::graph<coords> graph_from_map(const sector_map& map);