//
// Created by rnetuka on 18.12.19.
//

#include <algorithm>
#include <cctype>
#include <sstream>
#include <vector>

#include "../utils.h"
#include "maze.h"

using namespace std;

int maze_width(const string& string) {
    return (int) string.find('\n');
}

int maze_height(const string& string) {
    return count(string.begin(), string.end(), '\n');
}

bool is_start(char tile) {
    return tile == '@';
}

bool is_key(char tile) {
    return islower(tile);
}

bool is_door(char tile) {
    return isupper(tile);
}

maze::maze(const string &str) : width { maze_width(str) }, height { maze_height(str) }
{
    stringstream stream { str };
    vector<string> lines;
    while (stream) {
        string line;
        getline(stream, line);
        lines.push_back(line);
    }

    resize(tiles, width, height);

    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++) {
            char tile = lines[y][x];

            if (is_start(tile))
                start = { x, y };

            else if (::is_key(tile))
                keys_[tile] = { x, y };

            else if (::is_door(tile))
                doors_[tile] = { x, y };

            tiles[x][y] = tile;
        }
}

bool maze::is_wall(int x, int y) const {
    return tiles[x][y] == '#';
}

bool maze::is_door(int x, int y) const {
    return ::is_door(tiles[x][y]);
}

bool maze::is_key(int x, int y) const {
    return ::is_key(tiles[x][y]);
}

char maze::object_id(int x, int y) const {
    if (is_door(x, y) || is_key(x, y))
        return tiles[x][y];

    return 0;
}

const map<char, coords>& maze::keys() const {
    return keys_;
}

const map<char, coords>& maze::doors() const {
    return doors_;
}

coords maze::starting_position() const {
    return start;
}

maze read(const std::string& path) {
    stringstream stream;
    for (const string& line : read_lines<string>(path))
        stream << line << "\n";
    return maze { stream.str() };
}