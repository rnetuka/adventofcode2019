//
// Created by rnetuka on 28.12.19.
//

#pragma once

#include <ostream>
#include <vector>

#include "layer.h"

struct image {
    layer data;
};

image flatten(const std::vector<layer>& layers);
image negative(const image& img);

std::ostream& operator<<(std::ostream& stream, const image& img);