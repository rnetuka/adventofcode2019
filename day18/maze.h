//
// Created by rnetuka on 18.12.19.
//

#pragma once

#include <map>
#include <string>
#include <vector>

#include "../2darray/2darray.h"
#include "../map/coords.h"

class maze
{
private:
    array2d<char> tiles;
    std::map<char, coords> keys_;
    std::map<char, coords> doors_;
    coords start;

public:
    const int width;
    const int height;

    explicit maze(const std::string& string);

    bool is_wall(int x, int y) const;
    bool is_door(int x, int y) const;
    bool is_key(int x, int y) const;
    char object_id(int x, int y) const;
    const std::map<char, coords>& keys() const;
    const std::map<char, coords>& doors() const;
    coords starting_position() const;
};

maze read(const std::string& path);