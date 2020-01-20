//
// Created by rnetuka on 28.12.19.
//

#include "../geometry/geometry.h"
#include "laser.h"

using namespace std;


laser::laser(const asteroid& asteroid) : location { asteroid } {
    aim = { location.x, 0 };
    calibrate();
}

laser laser::deploy(const asteroid& asteroid) {
    return { asteroid };
}

std::optional<coords> laser::next_aim_point() const {
    return (aim_points.empty()) ? nullopt : make_optional(aim_points.front());
}

optional<asteroid> laser::pick_target(const set<asteroid>& asteroids)
{
    if (aim_points.empty())
        throw logic_error("Laser needs re-calibration !");

    geom::triangle firing_cone { location, aim, *next_aim_point() };
    vector<asteroid> candidates;

    copy_if(asteroids.begin(), asteroids.end(), back_inserter(candidates), [&firing_cone](const asteroid& asteroid) {
        return firing_cone.contains_point(asteroid);
    });

    if (candidates.empty())
        return nullopt;

    auto it = min_element(candidates.begin(), candidates.end(), [this](const asteroid& a, const asteroid& b) {
        geom::line axis { aim - location };
        geom::line line_a { a - location };
        geom::line line_b { b - location };
        return axis.angle_with(line_a) < axis.angle_with(line_b);
    });

    return *it;
}

deque<coords> calculate_aim_points(coords start) {
    deque<coords> result;

    for (int x = start.x + 1; x < space_map.width; x++)
        result.push_back({ x, 0 });

    for (int y = 1; y < space_map.height; y++)
        result.push_back({ space_map.max_x, y });

    for (int x = space_map.max_x - 1; x >= 0; x--)
        result.push_back({ x, space_map.max_y });

    for (int y = space_map.max_y - 1; y >= 0; y--)
        result.push_back({ 0, y });

    for (int x = 1; x < start.x; x++)
        result.push_back({ x, 0 });

    return result;
}

void laser::calibrate() {
    aim_points = calculate_aim_points(location);
}

void laser::rotate() {
    if (aim_points.empty())
        throw logic_error("Laser needs re-calibration !");

    aim = aim_points.front();
    aim_points.pop_front();
}