//
// Created by rnetuka on 17.12.19.
//

#include <fstream>
#include <set>
#include <sstream>
#include <vector>

#include "../intcode/computer.h"

using namespace intcd;
using namespace std;


struct area_map
{
    int width;
    int height;
    vector<vector<char>> data;

    area_map(const string& str)
    {
        vector<string> lines;
        stringstream stream { str };
        while (stream)
        {
            string line;
            getline(stream, line);
            if (! line.empty())
                lines.push_back(line);
        }
        width = lines[0].length();
        height = lines.size();

        data.resize(width);
        for (auto& column : data)
            column.resize(height);

        int x = 0;
        int y = 0;

        for (const string& line : lines) {
            for (char c : line)
                data[x++][y] = c;

            y++;
            x = 0;
        }
    }

    char get(int x, int y) const
    {
        if (x < 0 || x >= width || y < 0 || y >= height)
            return 0;

        return data[x][y];
    }
};

struct coords {
    int x, y;
};

vector<coords> scaffold_intersections(const area_map& map)
{
    vector<coords> result;

    for (int x = 0; x < map.width; x++)
        for (int y = 0; y < map.height; y++)
            if (map.get(x, y) == '#') {
                int count = 0;
                if (map.get(x - 1, y) == '#')
                    count++;
                if (map.get(x, y - 1) == '#')
                    count++;
                if (map.get(x + 1, y) == '#')
                    count++;
                if (map.get(x, y + 1) == '#')
                    count++;
                if (count >= 3)
                    result.push_back({x, y});
            }

    return result;
}


int sum_alignment_parameters()
{
    intcode code = read("day17/res/input.txt");
    output out;
    intcode_machine computer { null_input, out };
    computer.run_code(code);

    stringstream stream;
    for (char c : out.values)
        stream << c;
    string str = stream.str();

    fstream file { "day17/res/area.txt", fstream::out };
    file << str;
    file.close();

    area_map map { str };
    auto intersections = scaffold_intersections(map);

    int alignment = 0;
    for (auto [x, y] : intersections)
        alignment += x * y;

    return alignment;
}