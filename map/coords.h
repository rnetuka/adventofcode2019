//
// Created by rnetuka on 17.12.19.
//

#pragma once

struct coords {
    int x, y;
};

bool operator==(const coords& a, const coords& b) {
    return a.x == b.x && a.y == b.y;
}

bool operator<(const coords& a, const coords& b) {
    return (a.x == b.x) ? a.y < b.y : a.x < b.x;
}