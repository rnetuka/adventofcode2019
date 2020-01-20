//
// Created by rnetuka on 28.12.19.
//

#include "../geometry/geometry.h"
#include "../graph/graph.h"
#include "asteroid.h"

using namespace std;


bool has_line_of_sight(const asteroid& a, const asteroid& b)
{
    for (const asteroid& c : space_map.asteroids())
        if (c != a && c != b)
            if (geom::line_segment{ a, b }.contains_point(c))
                return false;

    return true;
}

asteroid_map::asteroid_map(int width, int height) : width { width }, height { height } {

}

asteroid_map asteroid_map::parse(const std::string& text) {
    set<asteroid> asteroids;

    stringstream stream { text };
    string line;
    int width = 0;
    int y = 0;

    while (stream) {
        stream >> line;
        width = max(width, (int) line.length());

        for (int x = 0; x < line.length(); x++)
            if (line[x] == asteroid_sign)
                asteroids.insert({ x, y });
        y++;
        line = "";
    }

    asteroid_map map { width, y + 1 };

    for (const asteroid& a : asteroids)
        map.graph.add_node(a);

    for (const asteroid& a : asteroids)
        for (const asteroid& b : asteroids)
            if (a != b)
                if (has_line_of_sight(a, b))
                    map.graph.connect(a, b);

    return map;
}

const set<asteroid>& asteroid_map::asteroids() const {
    return graph.nodes();
}

void asteroid_map::remove(const asteroid& asteroid) {
    graph.remove_node(asteroid);
}

set<asteroid> asteroid_map::asteroids_visible_from(const asteroid& a) const
{
    set<asteroid> result;

    for (asteroid b : asteroids())
        if (a != b)
            if (has_line_of_sight(a, b))
                result.insert(b);

    return result;
}