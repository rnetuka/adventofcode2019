//
// Created by rnetuka on 17.12.19.
//

#pragma once

#include <vector>

class sequence
{
private:
    std::vector<int> values;

public:
    const int size;

    sequence();
    explicit sequence(int size);
    sequence(const std::vector<int>& values);

    int& operator[](int i);
    const int& operator[](int i) const;
    sequence& operator=(const sequence& other);
};