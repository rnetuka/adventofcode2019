//
// Created by rnetuka on 09.01.20.
//

#pragma once

#include "line.h"

namespace geom {

    struct triangle {
        const point A;
        const point B;
        const point C;

        const line_segment a;
        const line_segment b;
        const line_segment c;

        triangle(point A, point B, point C);

        double area() const;
        bool contains_point(point p) const;
    };

}