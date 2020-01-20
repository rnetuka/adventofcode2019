//
// Created by rnetuka on 19.12.19.
//

#include "../intcode/computer.h"
#include "../geometry/geometry.h"
#include "beam.h"

using namespace intcode;
using namespace std;


constexpr int ship_size = 100;

const code code_ = read("day19/res/input.txt");

bool check_point(int x, int y) {
    intcode::machine machine;
    machine.in = input { x, y };
    machine.run_code(code_);
    return machine.out.front() == 1;
}

tractor_beam detect_tractor_beam(int max_x, int max_y)
{
    set<coords> points;

    // optimization: the x coordinates are beam are non-decreasing. go
    int min_x = 0;
    bool tractor_beam = false;

    for (int y = 0; y <= max_y; y++) {
        for (int x = min_x; x <= max_x; x++)
        {
            if (check_point(x, y))
            {
                // for next iteration, start x coordinates from minimal beam value in this row
                if (! tractor_beam) {
                    tractor_beam = true;
                    min_x = x;
                }

                points.insert({ x, y });
            }
            else {
                // skip all furthermore x coordinates in given row once the beam ends
                if (tractor_beam) {
                    tractor_beam = false;
                    x = max_x;
                }
            }
        }
    }
    return { max_x, max_y, points };
}

int tractor_beam_points() {
    return detect_tractor_beam(49, 49).points.size();
}

bool check_ship(int x, int y)
{
    int delta = ship_size - 1;
    return check_point(x, y)
        && check_point(x + delta, y)
        && check_point(x, y + delta)
        && check_point(x + delta, y + delta);
}

geom::point make_correction(const geom::point& guess) {
    // note: try up to 15 points in each axis for making a more precise approximation of the ship
    // location
    int delta = 15;

    for (int dy = delta; dy >= 0; dy--)
        for (int dx = delta; dx >= 0; dx--)
            if (int x = guess.x - dx, y = guess.y - dy; check_ship(x, y))
                return { x, y };

    return guess;
}

int santas_ship_coords()
{
    /* points taken from question 1 - 50x50 grid
     *
     * A
     *  ##
     *   ##
     *    ###
     *     ###
     *      ####
     *       ####
     *        B###C
     */
    geom::point A { 0, 0 };
    geom::point B { 29, 49 };
    geom::point C { 33, 49 };

    geom::vector u = B - A;
    geom::vector v = C - A;

    // unit vectors made from u and v
    geom::vector u1 = u / u.length();
    geom::vector v1 = v / v.length();

    // axis of angle alpha (vertex A)
    // note: multiply by 100 to overcome losing precision when later converted to ints
    geom::vector w = (u1 + v1) * 100;

    // guessed point for Santa's ship
    // note: this point lies on the alpha angle axis (vector w)
    // note: it's only a guess that will need later correction
    geom::point approximation { };

    // this interval has been selected based on previous calculations that are not part of this code
    for (int y = 1500; y < 3000; y++)
    {
        auto n = geom::normal(w);
        int a = (int) n.dx;
        int b = (int) n.dy;

        // alpha angle axis: a*x + b*y + c = 0
        // c is clearly 0 because the axis starts in [0,0]
        // thus: a*x = -b*y
        int x = -(b * y) / a;

        // [x,y] are coordinates on alpha angle axis, this means they're the center of Santa's ship
        // [ship_x, ship_y] marks top left corner of Santa's ship
        int ship_x = x - ship_size / 2;
        int ship_y = y - ship_size / 2;

        // if ship passes into the tractor beam, make a guess for it's coordinates and end this phase
        if (check_ship(ship_x, ship_y)) {
            approximation = { ship_x, ship_y };
            break;
        }
    }

    // if guess hasn't been made, exit now without success :(
    if (approximation == geom::point { 0, 0 })
        return -1;

    // the guessed coordinates are only approximation, we have to make a correction now
    // note: the 1000 limit here is only to prevent an infinite loop in a case we made the guess way too
    // distant
    for (int i = 0; i < 1000; i++) {
        geom::point correction = make_correction(approximation);

        // if no further correction is made, we have a result
        if (approximation == correction)
            return approximation.x * 10'000 + approximation.y;
        else
            approximation = correction;
    }

    // if corrections goes on and on and didn't yield any result so far, we better make a better guess
    // exit now without success :(
    return -1;
}