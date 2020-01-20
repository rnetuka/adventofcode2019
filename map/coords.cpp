//
// Created by rnetuka on 18.12.19.
//

#include <stdexcept>

#include "coords.h"

using namespace std;


bool operator==(const coords& a, const coords& b) {
    return a.x == b.x && a.y == b.y;
}

bool operator!=(const coords& a, const coords& b) {
    return !(a == b);
}

bool operator<(const coords& a, const coords& b) {
    return (a.x == b.x) ? a.y < b.y : a.x < b.x;
}

coords operator+(const coords& a, const coords& b) {
    return { a.x + b.x,  a.y + b.y };
}