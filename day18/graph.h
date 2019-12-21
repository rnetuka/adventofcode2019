//
// Created by rnetuka on 19.12.19.
//

#pragma once

#include <limits>
#include <map>
#include <set>

#include "../map/coords.h"

namespace day18 {

    const double infinity = std::numeric_limits<double>::infinity();

    struct node
    {
        int x, y;
        char id = 0;
        std::map<coords, double> neighbors;
    };

    bool operator<(const node& a, const node& b);
    bool operator==(const node& a, const node& b);
    bool operator!=(const node& a, const node& b);


    class graph
    {
    private:
        std::set<node> nodes_;

    public:
        graph() = default;

        void add(int x, int y, char id = 0);

        void connect(coords a, coords b, double length = 1);
        bool contains(int x, int y) const;

        const node& get(int x, int y) const;
        const node& get(coords coords) const;
        //const node& get(char key) const;

        const std::set<node>& nodes() const;

        std::set<node> neighbors_of(const node& n) const;
        double edge_length(const node& a, const node& b) const;

        std::map<node, double> shortest_paths(coords from) const;
    };

}