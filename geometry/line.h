//
// Created by rnetuka on 09.01.20.
//

#pragma once

#include "point.h"
#include "vector.h"

namespace geom {

    struct line {
        const vector u;

        line(const vector& u);

        double angle_with(const line& other) const;
    };

    struct line_segment {
        const point A;
        const point B;

        line_segment(point A, point B);

        vector direction_vector() const;
        bool contains_point(const point& p) const;
        double length() const;
    };

}