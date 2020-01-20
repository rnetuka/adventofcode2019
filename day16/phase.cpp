//
// Created by rnetuka on 17.12.19.
//

#include <vector>

#include "phase.h"

using namespace std;


const vector<int> phase_pattern { 0, 1, 0, -1 };


phase_generator::phase_generator(int n) : n { n } {

}

int phase_generator::next()
{
    int result = phase_pattern[i % phase_pattern.size()];

    count++;
    if (count == n) {
        i++;
        count = 0;
    }
    return result;
}

vector<int> create_phase(int size, int n)
{
    vector<int> result(size);
    phase_generator generator { n };
    generator.next();   // discard first value

    for (int i = 0; i < size; i++)
        result[i] = generator.next();

    return result;
}

matrix<int> phase_matrix(int size)
{
    matrix<int> matrix { size, size };

    for (int j = 0; j < size; j++)
        matrix.column(j + 1) = create_phase(size, j + 1);

    return matrix;
}