//
// Created by rnetuka on 24.12.19.
//

#include <array>
#include <cmath>
#include <fstream>
#include <iostream>
#include <set>

using namespace std;

constexpr int grid_width = 5;
constexpr int grid_height = 5;

using grid_t = array<array<bool, grid_height>, grid_width>;


ostream& operator<<(ostream& stream, const grid_t& grid)
{
    for (int y = 0; y < grid_height; y++) {
        for (int x = 0; x < grid_width; x++)
            stream << (grid[x][y] ? '#' : '.');
        stream << "\n";
    }
    return stream;
}

istream& operator>>(istream& stream, grid_t& grid)
{
    for (int y = 0; y < grid_height; y++) {
        string line;
        stream >> line;
        for (int x = 0; x < grid_width; x++)
            grid[x][y] = (line[x] == '#');
    }
    return stream;
}

bool is_in_bounds(int x, int y) {
    return x >= 0 && x < grid_width && y >= 0 && y < grid_height;
}

int neighbor_count(const grid_t& grid, int x, int y)
{
    int count = 0;
    int dx[] = { -1, 1,  0, 0 };
    int dy[] = {  0, 0, -1, 1 };
    for (int i = 0; i < 4; i++) {
        int x2 = x + dx[i];
        int y2 = y + dy[i];
        if (is_in_bounds(x2, y2) && grid[x2][y2])
            count++;
    }
    return count;
}

grid_t do_tick(const grid_t& grid)
{
    grid_t result { };

    for (int x = 0; x < grid_width; x++)
        for (int y = 0; y < grid_height; y++) {
            int count = neighbor_count(grid, x, y);

            if (grid[x][y])
                result[x][y] = (count == 1);
            else
                result[x][y] = (count == 1 || count == 2);
        }
    return result;
}

int biodiversity(const grid_t& grid)
{
    int biodiversity = 0;

    for (int x = 0; x < grid_width; x++) {
        for (int y = 0; y < grid_height; y++)
            if (grid[x][y]) {
                int i = y * grid_height + x;
                biodiversity += pow(2, i);
            }
    }
    return biodiversity;
}

int biodiversity_rating()
{
    grid_t grid;
    fstream file { "day24/res/input.txt" };
    file >> grid;
    file.close();

    set<grid_t> history;

    while (true) {
        if (history.find(grid) != history.end())
            return biodiversity(grid);

        history.insert(grid);
        grid = do_tick(grid);
    }
}