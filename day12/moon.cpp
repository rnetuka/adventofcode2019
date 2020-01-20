//
// Created by rnetuka on 10.01.20.
//

#include <sstream>
#include <tuple>

#include "../math/math.h"
#include "../utils.h"
#include "moon.h"

using namespace std;


moon::moon(int x, int y, int z) : x { x }, y { y }, z { z }, init_x { x }, init_y { y }, init_z { z } {

}

void moon::apply_velocity() {
    x += vx;
    y += vy;
    z += vz;
}

void moon::apply_gravity(const moon& other) {
    vx += sig(other.x - x);
    vy += sig(other.y - y);
    vz += sig(other.z - z);
}

int moon::potential_energy() const {
    return abs(x) + abs(y) + abs(z);
}

int moon::kinetic_energy() const {
    return abs(vx) + abs(vy) + abs(vz);
}

int moon::total_energy() const {
    return potential_energy() * kinetic_energy();
}

vector<moon> read_moons() {
    vector<string> lines = read_lines<string>("day12/res/input.txt");
    vector<moon> moons;

    for (const string& line : lines) {
        string x, y, z;
        stringstream stream { line };
        stream.ignore("<x="s.length());
        getline(stream, x, ',');
        stream.ignore(" y="s.length());
        getline(stream, y, ',');
        stream.ignore(" z="s.length());
        getline(stream, z, '>');
        moons.emplace_back(stoi(x), stoi(y), stoi(z));
    }
    return moons;
}