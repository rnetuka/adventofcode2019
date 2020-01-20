//
// Created by rnetuka on 27.12.19.
//

#include "computer.h"


intcode::value_t get_value(computer& computer) {
    auto value = computer.card();
    computer.state = (value == -1 ? waiting : running);
    return value;
}

computer::computer() {
    cpu.in = [this]() { return get_value(*this); };
    cpu.set_output_consumer([this](intcode::value_t value) {
        card << value;
        cpu.out.clear();
    });
}

computer::computer(const computer& other) : card { other.card }, cpu { other.cpu } {
    state = other.state;
    cpu.in = [this]() { return get_value(*this); };
    cpu.set_output_consumer([this](intcode::value_t value) {
        card << value;
        cpu.out.clear();
    });
}

void computer::join(inetwork* network, int net_address) {
    card.network = network;
    card.set_net_address(net_address);
}

void computer::boot() {
    auto code = intcode::read("day23/res/input.txt");
    cpu.run_code(code);
}

void computer::shutdown() {
    cpu.shutdown();
}