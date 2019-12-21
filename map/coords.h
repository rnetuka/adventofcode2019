//
// Created by rnetuka on 17.12.19.
//

#pragma once

struct coords {
    int x, y;
};

bool operator==(const coords& a, const coords& b);
bool operator<(const coords& a, const coords& b);