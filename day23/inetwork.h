//
// Created by rnetuka on 27.12.19.
//

#pragma once

#include <vector>

#include "../intcode/memory.h"

struct packet {
    intcode::value_t x = -1, y = -1;
};

enum computer_state {
    running,
    waiting
};

struct inetwork {
    virtual void send(int net_address, const packet& packet) = 0;
    virtual std::vector<computer_state> computer_states() const = 0;
};
