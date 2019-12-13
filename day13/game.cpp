//
// Created by rnetuka on 13.12.19.
//

#include "game.h"

using namespace std;

namespace day13 {

    void game_t::set_tile(int x, int y, tile tile) {
        width  = max(width,  x + 1);
        height = max(height, y + 1);

        tiles.resize(width);
        for (auto& column : tiles)
            column.resize(height);

        tiles[x][y] = tile;
    }

    ostream& operator<<(ostream& stream, const game_t& game) {
        for (int y = 0; y < game.height; y++) {
            for (int x = 0; x < game.width; x++) {
                switch (game.tiles[x][y]) {
                    case empty:  stream << ' '; break;
                    case wall:   stream << '+'; break;
                    case block:  stream << 'o'; break;
                    case paddle: stream << '_'; break;
                    case ball:   stream << '*'; break;
                }
            }
            stream << "\n";
        }
        return stream;
    }

    ostream& operator<<(ostream& stream, const coords& coords) {
        return stream << "[" << coords.x << ", " << coords.y << "]";
    }

    int count_tiles(const game_t& game, tile tile) {
        int count = 0;

        for (int x = 0; x < game.width; x++)
            for (int y = 0; y < game.height; y++)
                if (game.tiles[x][y] == tile)
                    count++;

        return count;
    }

    coords tile_position(const game_t& game, tile tile) {
        for (int x = 0; x < game.width; x++)
            for (int y = 0; y < game.height; y++)
                if (game.tiles[x][y] == tile)
                    return { x, y };
        return { -1, -1 };
    }

    coords ball_position(const game_t& game) {
        return tile_position(game, ball);
    }

    coords paddle_position(const game_t& game) {
        return tile_position(game, paddle);
    }

}