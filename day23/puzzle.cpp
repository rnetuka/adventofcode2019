//
// Created by rnetuka on 23.12.19.
//

#include <thread>
#include <vector>

#include "network.h"

using namespace std;


int value_sent_to_nat()
{
    packet result;

    network network;

    for (int i = 0; i < 50; i++)
        network.add_computer();

    network.failed_delivery_listener = [&network, &result](int address, packet packet) {
        if (address == 255) {
            result = packet;

            for (auto& computer : network.computers)
                computer.shutdown();
        }
    };

    vector<thread> threads;

    for (auto& computer : network.computers)
        threads.emplace_back([&computer]() { computer.boot(); });

    for (auto& thread : threads)
        thread.join();

    return result.y;
}

int value_delivered_by_nat()
{
    packet result;

    network network;
    network.nat.send_listener = [&network, &result](packet packet) {
        for (auto& already_sent : network.nat.sent_packets)
        {
            if (packet.y == already_sent.y) {
                result = packet;

                for (auto& computer : network.computers)
                    computer.shutdown();

                network.nat.shutdown();
            }
        }
    };

    vector<thread> threads;
    threads.emplace_back([&network]() { network.nat.boot(); });

    for (int i = 0; i < 50; i++)
        network.add_computer();

    for (auto& computer : network.computers)
        threads.emplace_back([&computer]() { computer.boot(); });

    for (auto& thread : threads)
        thread.join();

    return result.y;
}