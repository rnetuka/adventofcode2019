//
// Created by rnetuka on 11.12.19.
//

#pragma once

namespace day10 {

    struct coords {
        int x, y;
    };

    struct axis {
        int a, b, c;
    };

    bool lies_on_line_segment(const coords& a, const coords& b, const coords& c) {
        int ux = b.x - a.x;
        int uy = b.y - a.y;

        // c.x = a.x + t * ux
        // c.y = a.y + t * uy
        double vx = (c.x - a.x);
        double vy = (c.y - a.y);

        double t1 = (double) vx / ux;
        double t2 = (double) vy / uy;

        if (ux == 0 && vx == 0)
            if (t2 > 0 && t2 < 1)
                return true;

        if (uy == 0 && vy == 0)
            if (t1 > 0 && t1 < 1)
                return true;

        if (t1 == t2 && t1 > 0 && t1 < 1)
            return true;

        return false;
    }

    double triangle_s(coords a, coords b, coords c) {
        return 0.5 * (a.x * (c.y - b.y) + b.x * (a.y - c.y) + c.x * (b.y - a.y));
    }

    axis axis_between(coords p1, coords p2) {
        int ux = p2.x - p1.x;
        int uy = p2.y - p1.y;

        int nx = uy;
        int ny = -ux;

        // a*x + b*y + c = 0
        int a = nx;
        int b = ny;
        int c = -(a * p2.x + b * p2.y);

        return { a, b, c };
    }

}