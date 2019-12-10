//
// Created by rnetuka on 10.12.19.
//

#pragma once

#include <algorithm>
#include <cmath>
#include <deque>
#include <optional>
#include <vector>

#include "asteroid.h"
#include "geometry.h"

namespace day10 {

    struct laser;
    void calibrate(laser& laser);
    std::deque<coords> aim_points(coords start);

    struct laser {
        int x, y;
        int aim_x = x;
        int aim_y = 0;
        std::deque<coords> aim_points_;

        laser(const asteroid& base) : x { base.x }, y { base.y } {
            calibrate(*this);
        }
    };

    void calibrate(laser& laser) {
        laser.aim_points_ = aim_points({ laser.x, laser.y });
    }

    void rotate(laser& laser)
    {
        auto aim_point = laser.aim_points_.front();
        laser.aim_x = aim_point.x;
        laser.aim_y = aim_point.y;
        laser.aim_points_.pop_front();
    }

    axis aim_axis(const laser& laser) {
        return axis_between({ laser.x, laser.y }, { laser.aim_x, laser.aim_y });
    }

    double target_distance(const laser& laser, const asteroid& target) {
        auto [a, b, c] = aim_axis(laser);
        double dist = abs(a * target.x + b * target.y + c) / (sqrt(a * a + b * b));
        return dist;
    }

    bool is_in_firing_cone(const laser& laser, const asteroid& target) {
        int ax = laser.x;
        int ay = laser.y;
        int bx = laser.aim_x;
        int by = laser.aim_y;
        int cx = laser.aim_points_.front().x;
        int cy = laser.aim_points_.front().y;
        int dx = target.x;
        int dy = target.y;

        if (target == asteroid { ax, ay } || target == asteroid { bx, by } || target == asteroid { cx, cy })
            return true;

        if (lies_on_line_segment({ax, ay}, {bx, by}, {target.x, target.y}))
            return true;

        if (lies_on_line_segment({ax, ay}, {cx, cy}, {target.x, target.y}))
            return true;

        double s1 = triangle_s({ax, ay}, {bx, by}, {cx, cy});
        double s2 = triangle_s({ax, ay}, {bx, by}, {dx, dy});
        double s3 = triangle_s({bx, by}, {cx, cy}, {dx, dy});
        double s4 = triangle_s({cx, cy}, {ax, ay}, {dx, dy});

        if (s1 > 0 && s2 > 0 && s3 > 0 && s4 > 0)
            return true;

        if (s1 < 0 && s2 < 0 && s3 < 0 && s4 < 0)
            return true;

        return false;
    }

    std::deque<coords> aim_points(coords start) {
        std::deque<coords> result;

        for (int x = start.x + 1; x < space_map.width; x++)
            result.push_back({ x, 0 });

        for (int y = 1; y < space_map.height; y++)
            result.push_back({ asteroid_map_max_x, y });

        for (int x = asteroid_map_max_x - 1; x >= 0; x--)
            result.push_back({ x, asteroid_map_max_y });

        for (int y = asteroid_map_max_y - 1; y >= 0; y--)
            result.push_back({ 0, y });

        for (int x = 1; x < start.x; x++)
            result.push_back({ x, 0 });

        return result;
    }

    std::optional<asteroid> pick_target(const laser& laser, std::vector<asteroid>& asteroids)
    {
        std::vector<asteroid> targets;
        std::copy_if(asteroids.begin(), asteroids.end(), std::back_inserter(targets), [&laser](const asteroid& a) {
            return is_in_firing_cone(laser, a);
        });

        if (targets.empty())
            return std::nullopt;

        auto it = std::min_element(targets.begin(), targets.end(), [&laser](const asteroid& a, const asteroid& b) {
            return target_distance(laser, a) < target_distance(laser, b);
        });

        return std::make_optional(*it);
    }

}