//
// Created by rnetuka on 13.12.19.
//

/*
 * https://adventofcode.com/2019/day/13
 *
 * --- Day 13: Care Package ---
 * As you ponder the solitude of space and the ever-increasing three-hour roundtrip for messages between you and Earth,
 * you notice that the Space Mail Indicator Light is blinking. To help keep you sane, the Elves have sent you a care
 * package.
 *
 * It's a new game for the ship's arcade cabinet! Unfortunately, the arcade is all the way on the other end of the ship.
 * Surely, it won't be hard to build your own - the care package even comes with schematics.
 *
 * The arcade cabinet runs Intcode software like the game the Elves sent (your puzzle input). It has a primitive screen
 * capable of drawing square tiles on a grid. The software draws tiles to the screen with output instructions: every
 * three output instructions specify the x position (distance from the left), y position (distance from the top), and
 * tile id. The tile id is interpreted as follows:
 *
 * 0 is an empty tile. No game object appears in this tile.
 * 1 is a wall tile. Walls are indestructible barriers.
 * 2 is a block tile. Blocks can be broken by the ball.
 * 3 is a horizontal paddle tile. The paddle is indestructible.
 * 4 is a ball tile. The ball moves diagonally and bounces off objects.
 *
 * For example, a sequence of output values like 1,2,3,6,5,4 would draw a horizontal paddle tile (1 tile from the left
 * and 2 tiles from the top) and a ball tile (6 tiles from the left and 5 tiles from the top).
 *
 * Start the game. How many block tiles are on the screen when the game exits?
 *
 * --- Part Two ---
 * The game didn't run because you didn't put in any quarters. Unfortunately, you did not bring any quarters. Memory
 * address 0 represents the number of quarters that have been inserted; set it to 2 to play for free.
 *
 * The arcade cabinet has a joystick that can move left and right. The software reads the position of the joystick with
 * input instructions:
 *
 * If the joystick is in the neutral position, provide 0.
 * If the joystick is tilted to the left, provide -1.
 * If the joystick is tilted to the right, provide 1.
 *
 * The arcade cabinet also has a segment display capable of showing a single number that represents the player's current
 * score. When three output instructions specify X=-1, Y=0, the third output instruction is not a tile; the value
 * instead specifies the new score to show in the segment display. For example, a sequence of output values like
 * -1,0,12345 would show 12345 as the player's current score.
 *
 * Beat the game by breaking all the blocks. What is your score after the last block is broken?
 */

#include "../intcode/computer.h"
#include "game.h"
#include "joystick.h"

using namespace intcd;
using namespace std;

namespace day13 {

    game_t draw_game()
    {
        intcode code = read("day13/res/input.txt");

        game_t game;
        output output;

        intcode_machine computer { null_input, output };
        computer.add_output_listener([&game, &output](int value)
        {
            if (output.values.size() == 3)
            {
                int x = output.values[0];
                int y = output.values[1];
                int id = output.values[2];
                game.set_tile(x, y, (tile) id);
                output.clear();
            }
        });
        computer.run_code(code);
        return game;
    }

    int count_block_tiles()
    {
        game_t game = draw_game();
        return count_tiles(game, block);
    }

    int beat_the_game()
    {
        intcode code = read("day13/res/input.txt");
        code[0] = 2;

        game_t game;

        joystick_t joystick;
        output output;

        intcode_machine_t<joystick_t, struct output> computer { joystick, output };
        computer.add_input_listener([&game, &joystick]()
        {
            coords ball_pos = ball_position(game);
            coords paddle_pos = paddle_position(game);

            if (paddle_pos.x < ball_pos.x)
                joystick.position = right;
            else if (paddle_pos.x > ball_pos.x)
                joystick.position = left;
            else
                joystick.position = center;
        });
        computer.add_output_listener([&game, &output](int value)
        {
            if (output.values.size() == 3)
            {
                int x = output.values[0];
                int y = output.values[1];

                if (x == -1 && y == 0)
                    game.score = output.values[2];
                else
                    game.set_tile(x, y, (tile) output.values[2]);

                output.clear();
            }
        });
        computer.run_code(code);
        return game.score;
    }

}