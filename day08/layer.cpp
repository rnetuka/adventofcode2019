//
// Created by rnetuka on 28.12.19.
//

#include "layer.h"

void operator&=(layer& top, const layer& bottom)
{
    for (int i = 0; i < layer_size; i++) {
        if (top[i] == transparent)
            top[i] = bottom[i];
    }
}