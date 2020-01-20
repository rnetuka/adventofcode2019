//
// Created by rnetuka on 13.12.19.
//

#include <iostream>

#include "game.h"

using namespace std;


void game_t::set_tile(int x, int y, tile tile) {
    width_  = max(width_,  x + 1);
    height_ = max(height_, y + 1);

    tiles.resize(width_);
    for (auto& column : tiles)
        column.resize(height_);

    tiles[x][y] = tile;
}

void game_t::set_score(int score) {
    score_ = score;
}

int count_tiles(const game_t& game, tile tile) {
    int count = 0;

    for (int x = 0; x < game.width(); x++)
        for (int y = 0; y < game.height(); y++)
            if (game.tile_at(x, y) == tile)
                count++;

    return count;
}

coords find_tile(const game_t& game, tile tile) {
    for (int x = 0; x < game.width(); x++)
        for (int y = 0; y < game.height(); y++)
            if (game.tile_at(x, y) == tile)
                return { x, y };
    return { -1, -1 };
}

coords game_t::ball() {
    return find_tile(*this, tile::ball);
}

coords game_t::paddle() {
    return find_tile(*this, tile::paddle);
}

tile game_t::tile_at(int x, int y) const {
    return tiles[x][y];
}

int game_t::width() const {
    return width_;
}

int game_t::height() const {
    return height_;
}

int game_t::score() const {
    return score_;
}