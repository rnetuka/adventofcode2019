//
// Created by rnetuka on 10.12.19.
//

#include <algorithm>
#include <vector>

#include "../utils.h"
#include "asteroid.h"
#include "laser.h"

using namespace std;

namespace day10 {

    bool has_line_of_sight(const asteroid& a, const asteroid& b)
    {
        vector<asteroid> other_asteroids;
        copy_if(space_map.begin(), space_map.end(), back_inserter(other_asteroids), [&a, &b](const asteroid& other) {
            return a != other && b != other;
        });

        for (const asteroid& c : other_asteroids)
            if (lies_on_line_segment({ a.x, a.y }, { b.x, b.y }, { c.x, c.y }))
                return false;

        return true;
    }

    vector<asteroid> asteroids_visible_from(const vector<asteroid>& asteroids, asteroid a)
    {
        vector<asteroid> other_asteroids;
        vector<asteroid> result;

        copy_if(asteroids.begin(), asteroids.end(), back_inserter(other_asteroids), [&a](const asteroid& other) {
            return a != other;
        });

        for (asteroid b : other_asteroids)
            if (has_line_of_sight(a, b))
                result.push_back(b);

        return result;
    }

    vector<asteroid> asteroids_visible_from(asteroid a) {
        return asteroids_visible_from(space_map.asteroids, a);
    }

    int count_asteroids()
    {
        asteroid max = *max_element(space_map.begin(), space_map.end(), [](const asteroid& a, const asteroid& b) {
            return asteroids_visible_from(a).size() < asteroids_visible_from(b).size();
        });
        return asteroids_visible_from(max).size();
    }

    int destroyed_asteroid_number()
    {
        asteroid base { 23, 19 };
        laser laser { base };

        vector<asteroid> asteroids = space_map.asteroids;
        vector<asteroid> targets = asteroids_visible_from(asteroids, base);
        int destroyed = 0;

        while (! targets.empty()) {
            auto target = pick_target(laser, targets);
            if (target.has_value()) {
                asteroids.erase(find(asteroids.begin(), asteroids.end(), *target));
                targets.erase(find(targets.begin(), targets.end(), *target));
                destroyed++;

                if (destroyed == 200)
                    return target->x * 100 + target->y;
            } else {
                if (laser.aim_points_.empty()) {
                    calibrate(laser);
                    targets = asteroids_visible_from(asteroids, base);
                }
                rotate(laser);
            }
        }
        return -1;
    }

}