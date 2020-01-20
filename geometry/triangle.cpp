//
// Created by rnetuka on 09.01.20.
//

#include "triangle.h"

namespace geom {

    triangle::triangle(point A, point B, point C) : A { A }, B { B }, C { C }, a { B, C }, b { A, C }, c { A, B } {

    }

    double triangle::area() const {
        return 0.5 * (A.x * (C.y - B.y) + B.x * (A.y - C.y) + C.x * (B.y - A.y));
    }

    bool triangle::contains_point(point p) const {
        if (a.contains_point(p) || b.contains_point(p) || c.contains_point(p))
            return true;

        double s1 = area();
        double s2 = triangle { A, B, p }.area();
        double s3 = triangle { B, C, p }.area();
        double s4 = triangle { C, A, p }.area();

        if (s1 > 0 && s2 > 0 && s3 > 0 && s4 > 0)
            return true;

        if (s1 < 0 && s2 < 0 && s3 < 0 && s4 < 0)
            return true;

        return false;
    }

}