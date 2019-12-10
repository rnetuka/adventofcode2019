//
// Created by rnetuka on 03.12.19.
//

#pragma once

#include <string>
#include <vector>

template <typename T>
std::vector<T> read_lines(const std::string& path);

template <typename T>
std::vector<T> read_csv_input(const std::string& path);

std::string read_file(const std::string& path);