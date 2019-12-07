//
// Created by rnetuka on 07.12.19.
//

#pragma once

#include <string>
#include <vector>

#include "../utils.h"
#include "input.h"
#include "instruction.h"
#include "operation.h"
#include "output.h"
#include "parameter.h"

namespace day7 {

    using intcode = std::vector<int>;

    intcode read(const std::string& path) {
        return read_csv_input<int>(path);
    }

    int extract_value(intcode code, parameter parameter) {
        return parameter.mode == immediate ? parameter.value : code[parameter.value];
    }


    class intcode_machine
    {
    private:
        intcode code;
        int i = 0;
        input&  input_;
        output& output_;
        bool finished_ = false;

    public:
        intcode_machine() : input_( null_input ), output_ { null_output } {

        }

        intcode_machine(input& input, output& output) : input_ { input }, output_ { output } {

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

                if (opcode == add || opcode == mul)
                {
                    int a = extract_value(code, parameters[0]);
                    int b = extract_value(code, parameters[1]);
                    int addr = parameters[2];
                    code[addr] = calculations[opcode](a, b);
                    i += 4;
                }

                if (opcode == in)
                {
                    int addr = parameters[0];
                    input_ >> code[addr];
                    i += 2;
                }

                if (opcode == out)
                {
                    int value = extract_value(code, parameters[0]);
                    output_ << value;
                    i += 2;
                }

                if (opcode == jmp_if || opcode == jmp_ifn)
                {
                    int cond = extract_value(code, parameters[0]);
                    int j    = extract_value(code, parameters[1]);
                    if (checks[opcode](cond))
                        i = j;
                    else
                        i += 3;
                }

                if (opcode == less || opcode == eq)
                {
                    int a = extract_value(code, parameters[0]);
                    int b = extract_value(code, parameters[1]);
                    int addr = parameters[2];
                    code[addr] = comparisons[opcode](a, b);
                    i += 4;
                }
            }
        }
    };

}