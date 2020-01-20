//
// Created by rnetuka on 09.01.20.
//

#pragma once

#include "point.h"

namespace geom {

    struct vector {
        double dx = 0;
        double dy = 0;

        vector() = default;
        vector(double dx, double dy);
        vector(point a, point b);

        double length();
    };

    vector normal(const vector& u);

}

geom::vector operator-(const geom::point& a, const geom::point& b);

geom::vector operator+(const geom::vector& u, const geom::vector& v);
geom::vector operator*(const geom::vector& u, double c);
geom::vector operator*(double c, const geom::vector& u);
double operator*(const geom::vector& u, const geom::vector& v);
geom::vector operator/(const geom::vector& u, double c);