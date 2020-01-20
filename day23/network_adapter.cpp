//
// Created by rnetuka on 27.12.19.
//

#include "network_adapter.h"

using namespace intcode;
using namespace std;


network_adapter::network_adapter(const network_adapter& other) : in_queue {other.in_queue }, out_queue {other.out_queue }
{
    network = other.network;
    net_address = other.net_address;
}

void network_adapter::set_net_address(int address)
{
    net_address = address;
    in_queue.push_back(address);
}

value_t network_adapter::operator()()
{
    lock_guard<std::mutex> guard { mutex };

    if (in_queue.empty())
        return -1;
    else {
        value_t value = in_queue.front();
        in_queue.pop_front();
        return value;
    }
}

void network_adapter::operator<<(value_t value)
{
    out_queue.push_back(value);
    if (out_queue.size() == 3)
    {
        int address = out_queue[0];
        packet packet { out_queue[1], out_queue[2] };
        out_queue.clear();
        network->send(address, packet);
    }
}

void network_adapter::operator<<(const packet& packet)
{
    lock_guard<std::mutex> guard { mutex };

    in_queue.push_back(packet.x);
    in_queue.push_back(packet.y);
}