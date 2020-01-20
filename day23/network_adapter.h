//
// Created by rnetuka on 27.12.19.
//

#pragma once

#include <queue>
#include <deque>
#include <mutex>

#include "../intcode/memory.h"
#include "inetwork.h"


class network_adapter
{
    int net_address = -1;
    std::mutex mutex;

    std::deque<intcode::value_t> in_queue;
    std::deque<intcode::value_t> out_queue;

public:
    inetwork* network = nullptr;

    network_adapter() = default;
    network_adapter(const network_adapter& other);

    void set_net_address(int address);

    intcode::value_t operator()();
    void operator<<(intcode::value_t value);
    void operator<<(const packet& packet);
};