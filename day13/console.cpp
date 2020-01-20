//
// Created by rnetuka on 10.01.20.
//

#include "console.h"

using namespace intcode;
using namespace std;


gaming_console::gaming_console(ostream& display) : display { display }
{
    code = read("day13/res/input.txt");
    computer.add_input_listener([this]() {
        this->display << game_;
    });
    computer.add_output_consumer([this](value_t value) {
        if (computer.out.values.size() == 3)
        {
            int x = computer.out.values[0];
            int y = computer.out.values[1];

            if (x == -1 && y == 0)
                game_.set_score(computer.out.values[2]);
            else
                game_.set_tile(x, y, (tile) computer.out.values[2]);

            computer.out.clear();
        }
    });
}

game_t& gaming_console::game() {
    return game_;
}

void gaming_console::insert_coin() {
    code[0] = 2;
}

void gaming_console::play_game() {
    computer.run_code(code);
    display << "Game Over! Score: " << game_.score() << "\n";
}