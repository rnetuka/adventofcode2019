//
// Created by rnetuka on 11.12.19.
//

#include <sstream>
#include <string>
#include <string_view>

#include "spaceship.h"

using namespace std;

namespace day11 {

    const string whitespace_chars = "\t\n\v\f\r ";

    spaceship_t::spaceship_t() {
        repaint_black(*this);
    }

    void repaint_black(spaceship_t& spaceship) {
        for (int y = 0; y < spaceship_area_height; y++)
            for (int x = 0; x < spaceship_area_width; x++)
                ship.area[x][y] = black;
    }

    vector<string> area_lines(const spaceship_t& spaceship) {
        stringstream stream;
        vector<string> lines;
        for (int y = 0; y < spaceship_area_height; y++) {
            for (int x = 0; x < spaceship_area_width; x++) {
                int color = ship.area[x][y];
                if (color == black)
                    stream << ' ';
                else
                    stream << '#';
            }
            lines.push_back(stream.str());
            stream.str("");
        }
        return lines;
    }

    string registration_id(const spaceship_t& spaceship) {
        vector<string> lines = area_lines(spaceship);

        int min_i = spaceship_area_width;
        for (const string& line : lines)
            if (int i = line.find_first_not_of(whitespace_chars); i != -1)
                min_i = min(min_i, i);

        stringstream stream;
        for (string& line : lines) {
            line = line.substr(min_i);
            line.erase(line.find_last_not_of(whitespace_chars) + 1);
            if (! line.empty())
                stream << line << "\n";
        }
        return stream.str();
    }

}