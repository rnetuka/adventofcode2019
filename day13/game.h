//
// Created by rnetuka on 13.12.19.
//

#pragma once

#include <array>
#include <ostream>
#include <vector>

namespace day13 {

    enum tile
    {
        empty  = 0,
        wall   = 1,
        block  = 2,
        paddle = 3,
        ball   = 4
    };

    struct game_t
    {
        int width  = 0;
        int height = 0;
        std::vector<std::vector<tile>> tiles;
        int score = 0;

        void set_tile(int x, int y, tile tile);
    };

    std::ostream& operator<<(std::ostream& stream, const game_t& game);

    struct coords {
        int x, y;
    };

    std::ostream& operator<<(std::ostream& stream, const coords& coords);

    coords ball_position(const game_t& game);
    coords paddle_position(const game_t& game);

    int count_tiles(const game_t& game, tile tile);

}