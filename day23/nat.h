//
// Created by rnetuka on 13.01.20.
//

#pragma once

#include <atomic>
#include <functional>
#include <optional>
#include <vector>

#include "inetwork.h"

class nat_device
{
    inetwork* network;
    std::optional<struct packet> packet_;
    std::atomic<bool> shutdown_request = false;

public:
    std::vector<struct packet> sent_packets;
    std::optional<std::function<void(struct packet)>> send_listener;

    explicit nat_device(inetwork* network);

    void operator<<(struct packet packet);
    void boot();
    void shutdown();
};