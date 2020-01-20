//
// Created by rnetuka on 17.12.19.
//

#pragma once

#include "../math/matrix.h"

class phase_generator
{
private:
    const int n;
    int i = 0;
    int count = 0;

public:
    explicit phase_generator(int n);

    int next();
};


matrix<int> phase_matrix(int size);