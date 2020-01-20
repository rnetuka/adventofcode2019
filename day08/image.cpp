//
// Created by rnetuka on 28.12.19.
//

#include <stdexcept>

#include "image.h"

using namespace std;


image flatten(const vector<layer>& layers)
{
    if (layers.empty())
        throw logic_error("Trying to flatten empty list of layers");

    layer result = layers[0];

    for (int i = 1; i < layers.size(); i++)
        result &= layers[i];

    return { result };
}

image negative(const image& img)
{
    image result = img;

    for (int i = 0; i < layer_size; i++)
        if (img.data[i] == black || img.data[i] == white)
            result.data[i] = 1 - img.data[i];

    return result;
}

ostream& operator<<(ostream& stream, const image& img)
{
    for (int i = 0; i < layer_size; i++) {
        char ascii = img.data[i] == black ? '#' : ' ';
        stream << ascii;
        if ((i + 1) % image_width == 0)
            stream << "\n";
    }
    return stream;
}