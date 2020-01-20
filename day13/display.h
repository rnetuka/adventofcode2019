//
// Created by rnetuka on 10.01.20.
//

#pragma once

#include <ostream>
#include <sstream>

#include "game.h"

std::ostream& operator<<(std::ostream& stream, const game_t& game);

inline std::stringstream no_display;