//
// Created by rnetuka on 18.12.19.
//

#include "coords.h"

bool operator==(const coords& a, const coords& b) {
    return a.x == b.x && a.y == b.y;
}

bool operator<(const coords& a, const coords& b) {
    return (a.x == b.x) ? a.y < b.y : a.x < b.x;
}