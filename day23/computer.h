//
// Created by rnetuka on 27.12.19.
//

#pragma once

#include "../intcode/computer.h"
#include "inetwork.h"
#include "network_adapter.h"


struct computer
{
    intcode::computer cpu;
    network_adapter card;
    computer_state state = waiting;

    explicit computer();
    computer(const computer& other);

    void join(inetwork* network, int net_address);
    void boot();
    void shutdown();
};
