//
// Created by rnetuka on 10.12.19.
//

#include <algorithm>
#include <vector>

#include "asteroid.h"
#include "laser.h"

using namespace std;


int max_visible_asteroids()
{
    auto& asteroids = space_map.asteroids();

    asteroid max = *max_element(asteroids.begin(), asteroids.end(), [](const asteroid& a, const asteroid& b) {
        return space_map.graph.degree_of(a) < space_map.graph.degree_of(b);
    });
    return space_map.graph.degree_of(max);
}

int destroyed_asteroid_number()
{
    // base asteroid for the laser was calculated during finding answer for question 1
    asteroid base = { 23, 19 };
    auto laser = laser::deploy(base);

    set<asteroid> targets = space_map.asteroids_visible_from(base);
    int destroyed = 0;

    while (! targets.empty()) {
        auto target = laser.pick_target(targets);

        if (target) {
            targets.erase(*target);
            space_map.remove(*target);
            destroyed++;

            if (destroyed == 200)
                return target->x * 100 + target->y;
        }
        else {
            laser.rotate();

            if (! laser.next_aim_point()) {
                laser.calibrate();
                targets = space_map.asteroids_visible_from(base);
            }
        }
    }
    return -1;
}