//
// Created by rnetuka on 28.12.19.
//

#pragma once

#include<vector>

using layer = std::vector<int>;

constexpr int image_width = 25;
constexpr int image_height = 6;
constexpr int layer_size = image_width * image_height;

enum color
{
    black = 0,
    white = 1,
    transparent = 2
};

void operator&=(layer& top, const layer& bottom);