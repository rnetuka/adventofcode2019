//
// Created by rnetuka on 17.12.19.
//

#pragma once

#include <string>

#include "phase.h"
#include "sequence.h"

using signal_t = sequence;

signal_t input_signal(const std::string& string);

int operator*(const signal_t& signal, const phase_t& phase);