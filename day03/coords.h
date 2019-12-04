//
// Created by rnetuka on 04.12.19.
//

#pragma once

namespace day3 {

    struct coords {
        int x, y;
    };

    bool operator==(const coords& a, const coords& b) {
        return a.x == b.x && a.y == b.y;
    }

    bool operator<(const coords& a, const coords& b) {
        return (a.x == b.x) ? a.y < b.y : a.x < b.x;
    }

    int distance(const coords& a, const coords& b) {
        return abs(a.x - b.x) + abs(a.y - b.y);
    }

}