//
// Created by rnetuka on 07.01.20.
//

#pragma once

#include <ostream>
#include <set>

#include "../geometry/geometry.h"

struct tractor_beam
{
private:
    const int max_x;
    const int max_y;

public:
    const std::set<coords> points;

    tractor_beam(int max_x, int max_y, std::set<coords> points) : max_x { max_x }, max_y { max_y }, points { move(points) } {

    }

    friend std::ostream& operator<<(std::ostream& stream, const tractor_beam& beam)
    {
        for (int y = 0; y <= beam.max_y; y++) {
            for (int x = 0; x <= beam.max_x; x++) {
                if (beam.points.find({ x, y }) == beam.points.end())
                    stream << ' ';
                else
                    stream << '#';
            }
            stream << '\n';
        }
        return stream;
    }
};