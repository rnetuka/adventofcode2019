//
// Created by rnetuka on 09.01.20.
//

#include<cmath>

#include "line.h"
#include "vector.h"

using namespace std;


namespace geom {

    line::line(const vector& u) : u { u } {

    }

    double line::angle_with(const line& other) const {
        vector u = this->u;
        vector v = other.u;
        return cos(abs(u * v) / u.length() * v.length());
    }

    line_segment::line_segment(point A, point B) : A { A }, B { B } {

    }

    vector line_segment::direction_vector() const {
        return { B - A };
    }

    bool line_segment::contains_point(const point& p) const
    {
        if (A == p || B == p)
            return true;

        //    P = A + t * u
        // -> t * u = P - A
        // -> t1, t2 = (P - A) / u
        vector u = direction_vector();
        vector v = p - A;

        double t1 = v.dx / u.dx;
        double t2 = v.dy / u.dy;

        if (u.dx == 0 && v.dx == 0)
            if (t2 > 0 && t2 < 1)
                return true;

        if (u.dy == 0 && v.dy == 0)
            if (t1 > 0 && t1 < 1)
                return true;

        if (t1 == t2 && t1 > 0 && t1 < 1)
            return true;

        return false;
    }

    double line_segment::length() const {
        vector u = B - A;
        return u.length();
    }

}