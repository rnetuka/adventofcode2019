//
// Created by rnetuka on 04.12.19.
//

#pragma once

#include <string>
#include <vector>

#include "../map/coords.h"

using wire = std::vector<coords>;

const coords central_point { 0, 0 };

wire read_wire(const std::string& path);
void operator+=(wire& wire, const coords& next);