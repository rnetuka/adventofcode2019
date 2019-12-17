//
// Created by rnetuka on 17.12.19.
//

#include "sequence.h"

using namespace std;


sequence::sequence() : size { 0 } {

}

sequence::sequence(int size) : size { size } {
    values.resize(size);
}

sequence::sequence(const vector<int>& values) : values { values }, size { (int) values.size() } {

}

int& sequence::operator[](int i) {
    return values[i];
}

const int& sequence::operator[](int i) const {
    return values[i];
}

sequence& sequence::operator=(const sequence& other) {
    values = other.values;
    return *this;
}