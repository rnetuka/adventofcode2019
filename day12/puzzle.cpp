//
// Created by rnetuka on 12.12.19.
//

#include <algorithm>
#include <functional>
#include <optional>
#include <vector>

#include "../math/math.h"
#include "moon.h"

using namespace std;


void move(vector<moon>& moons)
{
    for (int i = 0; i < moons.size(); i++)
        for (int j = 0; j < moons.size(); j++)
            if (i != j)
                moons[i].apply_gravity(moons[j]);

    for (auto& moon : moons)
        moon.apply_velocity();
}

int system_total_energy() {
    vector<moon> moons = read_moons();

    for (int i = 0; i < 1000; i++)
        move(moons);

    int result = 0;
    for (auto& moon : moons)
        result += moon.total_energy();

    return result;
}

bool check_axis(const vector<moon>& moons, const function<bool(const moon& moon)>& predicate) {
    return all_of(moons.begin(), moons.end(), predicate);
}

long steps_to_repeat() {
    vector<moon> moons = read_moons();

    long i = 0;
    optional<long> x_axis_i;
    optional<long> y_axis_i;
    optional<long> z_axis_i;

    while (true) {
        i++;
        move(moons);

        if (!x_axis_i && check_axis(moons, [](auto& moon) { return moon.x == moon.init_x && moon.vx == 0; }))
            x_axis_i = i;

        if (!y_axis_i && check_axis(moons, [](auto& moon) { return moon.y == moon.init_y && moon.vy == 0; }))
            y_axis_i = i;

        if (!z_axis_i && check_axis(moons, [](auto& moon) { return moon.z == moon.init_z && moon.vz == 0; }))
            z_axis_i = i;

        if (x_axis_i && y_axis_i && z_axis_i)
            break;
    }
    return lcm(*x_axis_i, *y_axis_i, *z_axis_i);;
}