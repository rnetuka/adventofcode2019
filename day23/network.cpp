//
// Created by rnetuka on 23.12.19.
//

#include <iostream>
#include <mutex>

#include "network.h"

using namespace std;


network::network() : nat { this } {

}

int network::add_computer() {
    int net_address = computers.size();
    computers.emplace_back();
    computers.back().join(this, net_address);
    return net_address;
}

vector<computer_state> network::computer_states() const
{
    lock_guard<recursive_mutex> guard { const_cast<recursive_mutex&>(mutex) };

    vector<computer_state> states;
    for (auto& computer : computers)
        states.push_back(computer.state);

    return states;
}

void network::send(int net_address, const packet& packet)
{
    lock_guard<recursive_mutex> guard { mutex };

    if (verbose)
        cout << "  Sending packet to: " << net_address << " [" << packet.x << ", " << packet.y << "]\n";

    deliver(packet, net_address);
}

void network::deliver(const packet& packet, int address)
{
    if (address >= computers.size()) {
        if (failed_delivery_listener)
            (*failed_delivery_listener)(address, packet);

        if (address == 255)
            nat << packet;
    }
    else
        computers[address].card << packet;
}