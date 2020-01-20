//
// Created by rnetuka on 10.01.20.
//

#pragma once

#include <vector>

struct moon {
    int init_x, init_y, init_z;
    int x, y, z;
    int vx = 0, vy = 0, vz = 0;

    moon(int x, int y, int z);

    void apply_velocity();
    void apply_gravity(const moon& other);
    int potential_energy() const;
    int kinetic_energy() const;
    int total_energy() const;
};

std::vector<moon> read_moons();