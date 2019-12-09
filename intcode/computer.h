//
// Created by rnetuka on 07.12.19.
//

#pragma once

#include <stdexcept>
#include <string>
#include <vector>

#include "input.h"
#include "instruction.h"
#include "memory.h"
#include "operation.h"
#include "output.h"
#include "parameter.h"

namespace intcd {

    intcode read(const std::string& path);


    template <typename In, typename Out>
    class intcode_machine_t
    {
    private:
        intcode code;
        int i = 0;
        addr_t relative_base = 0;
        In*  input_ = nullptr;
        Out* output_ = nullptr;
        bool finished_ = false;


        value_t read(addr_t addr) const {
            if (addr >= code.size())
                return 0;
            return code[addr];
        }

        void write(addr_t addr, value_t value) {
            if (addr >= code.size())
                code.resize(addr + 1);
            code[addr] = value;
        }

        value_t extract_value(parameter parameter) {
            switch (parameter.mode) {
                case immediate: return parameter.value;
                case position:  return read(parameter.value);
                case relative:  return read(parameter.value + relative_base);
            }
        }

        addr_t extract_addr(parameter parameter) {
            auto addr = parameter.value;
            if (parameter.mode == relative)
                addr += relative_base;
            return addr;
        }

    public:
        intcode_machine_t() : input_ { nullptr }, output_ { nullptr } {

        }

        intcode_machine_t(In& input, Out& output) : input_ { &input }, output_ { &output } {

        }

        void run_code(const intcode& code) {
            set_code(code);
            run();
        }

        bool finished() const {
            return finished_ || i >= code.size();
        }

        void set_code(const intcode& code) {
            this->code = code;
            i = 0;
        }

        void run() {
            while (i < code.size())
            {
                auto operation = parse_operation(code, i);
                int opcode = operation.code;
                auto& parameters = operation.parameters;

                if (opcode == fin) {
                    finished_ = true;
                    return;
                }

                else if (opcode == add || opcode == mul)
                {
                    auto a = extract_value(parameters[0]);
                    auto b = extract_value(parameters[1]);
                    auto addr = extract_addr(parameters[2]);
                    auto res = calculations[opcode](a, b);
                    write(addr, res);
                    i += 4;
                }

                else if (opcode == in)
                {
                    auto addr = extract_addr(parameters[0]);
                    int value = 0;
                    *input_ >> value;
                    write(addr, value);
                    i += 2;
                }

                else if (opcode == out)
                {
                    auto value = extract_value(parameters[0]);
                    *output_ << value;
                    i += 2;
                }

                else if (opcode == jmp_if || opcode == jmp_ifn)
                {
                    auto cond = extract_value(parameters[0]);
                    auto j    = extract_value(parameters[1]);
                    if (checks[opcode](cond))
                        i = j;
                    else
                        i += 3;
                }

                else if (opcode == less || opcode == eq)
                {
                    auto a = extract_value(parameters[0]);
                    auto b = extract_value(parameters[1]);
                    auto addr = extract_addr(parameters[2]);
                    bool res = comparisons[opcode](a, b);
                    write(addr, res);
                    i += 4;
                }

                else if (opcode == rel)
                {
                    auto value = extract_value(parameters[0]);
                    relative_base += value;
                    i += 2;
                }

                else throw std::logic_error("Unknown opcode: " + std::to_string(opcode));
            }
        }

        const intcode& get_code() const {
            return code;
        }
    };

    using intcode_machine = intcode_machine_t<input, output>;
}