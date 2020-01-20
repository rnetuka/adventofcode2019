//
// Created by rnetuka on 14.01.20.
//

#include <chrono>
#include <thread>

#include "nat.h"

using namespace std;


nat_device::nat_device(inetwork *network) : network { network } {

}

void nat_device::operator<<(packet packet) {
    packet_ = packet;
}

void nat_device::boot() {
    while (! shutdown_request)
    {
        if (packet_) {
            vector<computer_state> computer_states = network->computer_states();

            if (all_of(computer_states.begin(), computer_states.end(), [](computer_state state) { return state == waiting; }))
            {
                if (send_listener)
                    (*send_listener)(*packet_);

                network->send(0, *packet_);
                sent_packets.push_back(*packet_);
                packet_ = nullopt;
            }
        }
        this_thread::sleep_for(1s);
    }
}

void nat_device::shutdown() {
    shutdown_request = true;
}