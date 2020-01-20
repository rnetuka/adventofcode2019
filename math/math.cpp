//
// Created by rnetuka on 10.01.20.
//

#include <cstdlib>
#include <numeric>

int sig(int a) {
    return (a == 0) ? 0 : (a < 0 ? -1 : 1);
}

long lcm(long a, long b, long c) {
    return std::lcm(a, std::lcm(b, c));;
}

int last_digit(int n) {
    return abs(n) % 10;
}