//
// Created by rnetuka on 18.12.19.
//

#pragma once

#include <vector>

template <typename T>
using array2d = std::vector<std::vector<T>>;

template <typename T>
void resize(array2d<T>& array, int width, int height)
{
    array.resize(width);
    for (auto& column : array)
        column.resize(height);
}