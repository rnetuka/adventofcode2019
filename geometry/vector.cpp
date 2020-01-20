//
// Created by rnetuka on 09.01.20.
//

#include <cmath>

#include "vector.h"

using namespace std;


namespace geom {

    vector::vector(double dx, double dy) {
        this->dx = dx;
        this->dy = dy;
    }

    vector::vector(point a, point b) {
        dx = b.x - a.x;
        dy = b.y - a.y;
    }

    double vector::length() {
        return sqrt(pow(dx, 2) + pow(dy, 2));
    }

    vector normal(const vector& u) {
        return { u.dy, -u.dx };
    }

}

geom::vector operator-(const geom::point& a, const geom::point& b) {
    return { b, a };
}

geom::vector operator+(const geom::vector& u, const geom::vector& v) {
    return { u.dx + v.dx, u.dy + v.dy };
}

geom::vector operator*(const geom::vector& u, double c) {
    return { c * u.dx, c * u.dy };
}

geom::vector operator*(double c, const geom::vector& u) {
    return u * c;
}

double operator*(const geom::vector& u, const geom::vector& v) {
    return u.dx * v.dx + u.dy * v.dy;
}

geom::vector operator/(const geom::vector& u, double c) {
    return { u.dx / c, u.dy / c };
}