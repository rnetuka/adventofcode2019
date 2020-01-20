//
// Created by rnetuka on 16.12.19.
//

#include <algorithm>

#include "sectormap.h"

using namespace std;


bool operator==(const location& a, const location& b) {
    return a.x == b.x && a.y == b.y;
}

sector_map::sector_map(int width, int height) : width { width }, height { height }
{
    tiles.resize(width);
    for (vector<tile_value >& column : tiles)
        column.resize(height);
}

void sector_map::set(int x, int y, tile_value tile) {
    tiles[x + offset_x][y + offset_y] = tile;
}

tile_value sector_map::get(int x, int y) const {
    return tiles[x + offset_x][y + offset_y];
}

optional<coords> sector_map::find_oxygen_system() const
{
    for (int x = min_x; x <= max_x; x++)
        for (int y = min_y; y <= max_y; y++)
            if (get(x, y) == oxygen_system)
                return coords { x, y };

    return nullopt;
}

bool sector_map::is_free_to_move(int x, int y) const
{
    return get(x, y) != wall;
}

ostream& operator<<(ostream& stream, const sector_map& map)
{
    for (int y = map.min_y; y <= map.max_y; y++) {
        for (int x = map.min_x; x <= map.max_x; x++) {
            if (x == 0 && y == 0)
                stream << 'o';
            else {
                auto tile = map.get(x, y);
                switch (tile) {
                    case ::empty:       stream << ' '; break;
                    case wall:          stream << '#'; break;
                    case oxygen_system: stream << '.'; break;
                }
            }
        }
        stream << "\n";
    }
    return stream;
}

sector_map sector_map_builder::create_sector_map() const
{
    int width  = max_x - min_x + 1;
    int height = max_y - min_y + 1;
    sector_map map { width, height };
    map.min_x = min_x;
    map.max_x = max_x;
    map.min_y = min_y;
    map.max_y = max_y;
    map.offset_x = -min_x;
    map.offset_y = -min_y;

    for (int x = min_x; x <= max_x; x++)
        for (int y = min_y; y <= max_y; y++) {
            auto tile = get(x, y).value_or(wall);
            map.set(x, y, tile);
        }

    return map;
}

void sector_map_builder::add(int x, int y, int tile) {
    nodes.push_back({ x, y, tile });
    min_x = min(min_x, x);
    max_x = max(max_x, x);
    min_y = min(min_y, y);
    max_y = max(max_y, y);
}

bool sector_map_builder::contains(int x, int y) const {
    return find(nodes.begin(), nodes.end(), location { x, y }) != nodes.end();
}

optional<tile_value> sector_map_builder::get(int x, int y) const {
    auto it = find(nodes.begin(), nodes.end(), location { x, y });
    if (it != nodes.end())
        return (tile_value) it->value;
    else
        return nullopt;
}

graph::graph<coords> graph_from_map(const sector_map& map)
{
    graph::graph<coords> graph;

    for (int x = map.min_x + 1; x < map.max_x; x++)
        for (int y = map.min_y + 1; y < map.max_y; y++) {
            if (map.is_free_to_move(x, y))
            {
                graph.add_node({ x, y });

                // north
                if (map.is_free_to_move(x, y - 1)) {
                    graph.add_node({ x, y - 1 });
                    graph.connect({ x, y }, { x, y - 1 });
                }

                // west
                if (map.is_free_to_move(x + 1, y)) {
                    graph.add_node({ x + 1, y });
                    graph.connect({ x, y }, { x + 1, y });
                }

                // south
                if (map.is_free_to_move(x, y + 1)) {
                    graph.add_node({ x, y + 1 });
                    graph.connect({ x, y }, { x, y + 1 });
                }

                // east
                if (map.is_free_to_move(x - 1, y)) {
                    graph.add_node({ x - 1, y });
                    graph.connect({ x, y }, { x - 1, y });
                }
            }
        }

    return graph;
}