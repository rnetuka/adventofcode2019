//
// Created by rnetuka on 20.12.19.
//

#pragma once

#include <istream>
#include <map>
#include <set>
#include <string>

#include "../2darray/2darray.h"
#include "../map/coords.h"

class portal_maze
{
private:
    array2d<std::string> tiles;
    int width_ = 0;
    int height_ = 0;
    coords entrance_;
    coords exit_;

public:

    int width() const;
    int height() const;

    bool is_empty(int x, int y) const;
    bool is_wall(int x, int y) const;
    bool is_portal(int x, int y) const;
    std::string id_of(int x, int y) const;
    std::set<std::string> portals() const;
    std::pair<coords, coords> portal_exits(const std::string& id) const;
    coords entrance() const;
    coords exit() const;

    friend std::istream& operator>>(std::istream& stream, portal_maze& ref);
};




