//
// Created by rnetuka on 10.01.20.
//

#include "display.h"

using namespace std;


ostream& operator<<(ostream& stream, const game_t& game)
{
    for (int y = 0; y < game.height(); y++) {
        for (int x = 0; x < game.width(); x++) {
            switch (game.tile_at(x, y)) {
                case tile::empty:  stream << ' '; break;
                case tile::wall:   stream << '+'; break;
                case tile::block:  stream << 'o'; break;
                case tile::paddle: stream << '^'; break;
                case tile::ball:   stream << '*'; break;
            }
        }
        stream << "\n";
    }
    return stream;
}