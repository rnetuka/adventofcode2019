//
// Created by rnetuka on 23.12.19.
//

#pragma once

#include <atomic>
#include <functional>
#include <mutex>
#include <optional>
#include <vector>

#include "inetwork.h"
#include "nat.h"
#include "computer.h"


class network : public inetwork
{
    std::recursive_mutex mutex;
    bool verbose = false;

public:
    std::vector<computer> computers;
    nat_device nat;
    std::optional<std::function<void(int, packet)>> failed_delivery_listener;

    network();

    int add_computer();
    std::vector<computer_state> computer_states() const override;
    void send(int net_address, const packet& packet) override;
    void deliver(const packet& packet, int net_address);
};