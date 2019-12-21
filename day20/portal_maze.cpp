//
// Created by rnetuka on 20.12.19.
//

#include <vector>

#include "portal_maze.h"

using namespace std;


int portal_maze::width() const {
    return width_;
}

int portal_maze::height() const {
    return height_;
}

bool portal_maze::is_empty(int x, int y) const {
    return tiles[x][y] == ".";
}

bool portal_maze::is_wall(int x, int y) const {
    return tiles[x][y] == "#";
}

bool portal_maze::is_portal(int x, int y) const {
    return tiles[x][y].length() == 2;
}

string portal_maze::id_of(int x, int y) const {
    return (tiles[x][y] == "." || tiles[x][y] == "#") ? "" : tiles[x][y];
}

coords portal_maze::entrance() const {
    return entrance_;
}

coords portal_maze::exit() const {
    return exit_;
}

set<string> portal_maze::portals() const {
    set<string> result;
    for (int x = 0; x < width_; x++)
        for (int y = 0; y < height_; y++)
            if (is_portal(x, y) && tiles[x][y] != "AA" && tiles[x][y] != "ZZ")
                result.insert(tiles[x][y]);
    return result;
}

pair<coords, coords> portal_maze::portal_exits(const std::string& id) const {
    vector<coords> exits;

    for (int x = 0; x < width_; x++)
        for (int y = 0; y < height_; y++)
            if (tiles[x][y] == id)
                exits.push_back({ x, y });

    return { exits[0], exits[1] };
}

bool is_id(char c) {
    return c >= 'A' && c <= 'Z';
}

istream& operator>>(istream& stream, portal_maze& maze)
{
    vector<string> lines;

    while (stream) {
        string line;
        getline(stream, line);
        lines.push_back(line);
    }

    maze.height_ = lines.size();
    maze.width_ = lines[0].length();
    resize(maze.tiles, maze.width_, maze.height_);

    for (int x = 0; x < maze.width_; x++) {
        for (int y = 0; y < maze.height_; y++) {
            char tile = lines[y][x];

            if (tile == '#')
                maze.tiles[x][y] = tile;

            else if (tile == '.') {
                maze.tiles[x][y] = tile;

                if (char n1 = lines[y - 1][x], n2 = lines[y - 2][x]; is_id(n1) && is_id(n2)) {
                    string id { n2, n1 };
                    maze.tiles[x][y] = id;

                    if (id == "AA")
                        maze.entrance_ = { x, y };
                    else if (id == "ZZ")
                        maze.exit_ = { x, y };
                }

                if (char n1 = lines[y + 1][x], n2 = lines[y + 2][x]; is_id(n1) && is_id(n2)) {
                    string id { n1, n2 };
                    maze.tiles[x][y] = id;

                    if (id == "AA")
                        maze.entrance_ = { x, y };
                    else if (id == "ZZ")
                        maze.exit_ = { x, y };
                }

                if (char n1 = lines[y][x - 1], n2 = lines[y][x - 2]; is_id(n1) && is_id(n2)) {
                    string id { n2, n1 };
                    maze.tiles[x][y] = id;

                    if (id == "AA")
                        maze.entrance_ = { x, y };
                    else if (id == "ZZ")
                        maze.exit_ = { x, y };
                }

                if (char n1 = lines[y][x + 1], n2 = lines[y][x + 2]; is_id(n1) && is_id(n2)) {
                    string id { n1, n2 };
                    maze.tiles[x][y] = id;

                    if (id == "AA")
                        maze.entrance_ = { x, y };
                    else if (id == "ZZ")
                        maze.exit_ = { x, y };
                }
            }
        }
    }

    return stream;
}