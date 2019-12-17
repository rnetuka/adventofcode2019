//
// Created by rnetuka on 17.12.19.
//

#pragma once

#include "sequence.h"

using phase_t = sequence;

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


phase_t create_phase(int size, int n);