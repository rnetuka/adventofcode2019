//
// Created by rnetuka on 17.12.19.
//

#include <fstream>
#include <queue>
#include <set>
#include <sstream>
#include <vector>

#include "../intcode/computer.h"
#include "../map/coords.h"

using namespace intcode;
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
    code code = read("day17/res/input.txt");
    intcode::computer computer;
    computer.run_code(code);

    stringstream stream;
    for (char c : computer.out.values)
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

struct orders
{
    static inline string yes = "y";
    static inline string no = "n";

    queue<char> chars;

    orders& operator<<(const string& str) {
        for (char c : str)
            chars.push(c);
        return *this;
    }

    char operator()() {
        if (chars.empty())
            throw no_input_exception();

        char value = chars.front();
        chars.pop();
        return value;
    }
};

int collected_space_dust()
{
    code code = read("day17/res/input.txt");
    code[0] = 2;

    /*
     * TODO:
     * 1. calculate all possible paths in the graph
     * 2. translate path to series of commands
     * 3. for every series, try to splice it to three patterns,
     * 4. from those, check if length of every pattern doesn't exceed 20
     */

    orders orders;
    orders << "A,A,B,C,B,C,B,C,B,A" << "\n";
    orders << "R,6,L,12,R,6" << "\n";
    orders << "L,12,R,6,L,8,L,12" << "\n";
    orders << "R,12,L,10,L,10" << "\n";
    orders << orders::no << "\n";

    intcode_machine_t<struct orders> cpu;
    cpu.in = orders;
    cpu.run_code(code);
    return cpu.out.back();
}