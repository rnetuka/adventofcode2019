//
// Created by rnetuka on 06.12.19.
//

#pragma once

#include <string>

#include "../graph/tree.h"

using orbit_map_t = graph::tree<std::string>;

orbit_map_t read_orbit_map();

inline orbit_map_t orbit_map = read_orbit_map();