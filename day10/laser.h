//
// Created by rnetuka on 10.12.19.
//

#pragma once

#include <deque>
#include <optional>
#include <set>

#include "asteroid.h"

class laser {
private:
    coords aim;
    std::deque<coords> aim_points;

    laser(const asteroid& base);

public:
    const coords location;

    static laser deploy(const asteroid& asteroid);

    std::optional<coords> next_aim_point() const;
    std::optional<asteroid> pick_target(const std::set<asteroid>& asteroids);
    void calibrate();
    void rotate();
};