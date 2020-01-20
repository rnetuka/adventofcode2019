//
// Created by rnetuka on 13.12.19.
//

#pragma once

#include <vector>

#include "../map/coords.h"

enum tile {
    empty  = 0,
    wall   = 1,
    block  = 2,
    paddle = 3,
    ball   = 4
};

class game_t
{
    int width_  = 0;
    int height_ = 0;
    std::vector<std::vector<tile>> tiles;
    int score_ = 0;

public:
    void set_tile(int x, int y, tile tile);
    void set_score(int score);
    tile tile_at(int x, int y) const;
    int width() const;
    int height() const;
    int score() const;
    coords ball();
    coords paddle();
};

int count_tiles(const game_t& game, tile tile);