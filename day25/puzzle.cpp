//
// Created by rnetuka on 27.12.19.
//

#include <iostream>
#include <string>

#include "../intcode/computer.h"

using namespace intcode;
using namespace std;


struct rescue_droid_cli
{
    string command;

    char operator()() {
        if (command.empty()) {
            getline(cin, command);
            command += '\n';
        }
        char value = command.front();
        command.erase(0, 1);
        return value;
    }

};

using rescue_droid_cpu = intcode_machine_t<rescue_droid_cli>;

struct rescue_droid
{
    rescue_droid_cpu cpu;

    rescue_droid() {
        cpu.in = rescue_droid_cli { };
        cpu.add_output_consumer([this](value_t value) {
            cout << (char) value;
        });
    }

    void start() {
        code code = read("day25/res/input.txt");
        cpu.run_code(code);
    }
};

void find_password_for_main_airlock()
{
    rescue_droid droid;
    droid.start();
}