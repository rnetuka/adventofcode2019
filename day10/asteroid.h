//
// Created by rnetuka on 10.12.19.
//

#pragma once

#include <algorithm>
#include <string>
#include <sstream>
#include <vector>

namespace day10 {

    constexpr char asteroid_sign = '#';

    struct asteroid {
        int x, y;
    };

    bool operator==(const asteroid& a, const asteroid& b) {
        return a.x == b.x && a.y == b.y;
    }

    bool operator!=(const asteroid& a, const asteroid& b) {
        return !(a == b);
    }

    struct space_map {
        int width;
        int height;
        std::vector<asteroid> asteroids;

        auto begin() -> decltype(asteroids.begin()) {
            return asteroids.begin();
        }

        auto end() -> decltype(asteroids.end()) {
            return asteroids.end();
        }
    };

    space_map read_asteroids(const std::string& text) {
        std::vector<asteroid> asteroids;

        std::stringstream stream { text };
        std::string line;
        int width = 0;
        int y = 0;

        while (stream) {
            stream >> line;
            width = std::max(width, (int) line.length());

            for (int x = 0; x < line.length(); x++)
                if (line[x] == asteroid_sign)
                    asteroids.push_back({ x, y });
            y++;
            line = "";
        }
        return { width, y + 1, asteroids };
    }

    space_map space_map = read_asteroids(read_file("day10/res/input.txt"));

    const int asteroid_map_max_x = space_map.width - 1;
    const int asteroid_map_max_y = space_map.height - 1;

}