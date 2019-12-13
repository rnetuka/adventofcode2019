//
// Created by rnetuka on 12.12.19.
//

#include <cstdlib>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include <iostream>

using namespace std;

namespace day12 {

    struct moon {
        int x, y, z;
        int vx, vy, vz = 0;
    };

    const moon Io       { -1,  7,   3 };
    const moon Europa   { 12,  2, -13 };
    const moon Ganymede { 14, 18,  -8 };
    const moon Callisto { 17,  4,  -4 };

    int sig(int a) {
        return (a == 0) ? 0 : (a < 0 ? -1 : 1);
    }

    void apply_gravity(moon& a, moon& b) {
        a.vx += sig(b.x - a.x);
        b.vx += sig(a.x - b.x);

        a.vy += sig(b.y - a.y);
        b.vy += sig(a.y - b.y);

        a.vz += sig(b.z - a.z);
        b.vz += sig(a.z - b.z);
    };

    void apply_velocity(moon& moon) {
        moon.x += moon.vx;
        moon.y += moon.vy;
        moon.z += moon.vz;
    }

    void tick(const vector<moon*>& moon_ps) {
        moon& a = *moon_ps[0];
        moon& b = *moon_ps[1];
        moon& c = *moon_ps[2];
        moon& d = *moon_ps[3];

        apply_gravity(a, b);
        apply_gravity(a, c);
        apply_gravity(a, d);

        apply_gravity(b, c);
        apply_gravity(b, d);

        apply_gravity(c, d);

        apply_velocity(a);
        apply_velocity(b);
        apply_velocity(c);
        apply_velocity(d);
    }

    int potential_energy(const moon& moon) {
        return abs(moon.x) + abs(moon.y) + abs(moon.z);
    }

    int kinetic_energy(const moon& moon) {
        return abs(moon.vx) + abs(moon.vy) + abs(moon.vz);
    }

    int total_energy(const moon& moon) {
        return potential_energy(moon) * kinetic_energy(moon);
    }

    int system_total_energy() {
        vector<moon> moons { Io, Europa, Ganymede, Callisto };
        vector<moon*> moon_ps { &moons[0], &moons[1], &moons[2], &moons[3] };

        for (int i = 0; i < 1000; i++)
            tick(moon_ps);

        int t1 = total_energy(moons[0]);
        int t2 = total_energy(moons[1]);
        int t3 = total_energy(moons[2]);
        int t4 = total_energy(moons[3]);

        return t1+t2+t3+t4;
    }

}