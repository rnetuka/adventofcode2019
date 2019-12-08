//
// Created by rnetuka on 08.12.19.
//

/*
 * https://adventofcode.com/2019/day/8
 *
 * --- Day 8: Space Image Format ---
 * The Elves' spirits are lifted when they realize you have an opportunity to reboot one of their Mars rovers, and so
 * they are curious if you would spend a brief sojourn on Mars. You land your ship near the rover.
 *
 * When you reach the rover, you discover that it's already in the process of rebooting! It's just waiting for someone
 * to enter a BIOS password. The Elf responsible for the rover takes a picture of the password (your puzzle input) and
 * sends it to you via the Digital Sending Network.
 *
 * Unfortunately, images sent via the Digital Sending Network aren't encoded with any normal encoding; instead, they're
 * encoded in a special Space Image Format. None of the Elves seem to remember why this is the case. They send you
 * the instructions to decode it.
 *
 * Images are sent as a series of digits that each represent the color of a single pixel. The digits fill each row of
 * the image left-to-right, then move downward to the next row, filling rows top-to-bottom until every pixel of
 * the image is filled.
 *
 * Each image actually consists of a series of identically-sized layers that are filled in this way. So, the first digit
 * corresponds to the top-left pixel of the first layer, the second digit corresponds to the pixel to the right of that
 * on the same layer, and so on until the last digit, which corresponds to the bottom-right pixel of the last layer.
 *
 * For example, given an image 3 pixels wide and 2 pixels tall, the image data 123456789012 corresponds to the following
 * image layers:
 *
 * Layer 1: 123
 *          456
 *
 * Layer 2: 789
 *          012
 * The image you received is 25 pixels wide and 6 pixels tall.
 *
 * To make sure the image wasn't corrupted during transmission, the Elves would like you to find the layer that contains
 * the fewest 0 digits. On that layer, what is the number of 1 digits multiplied by the number of 2 digits?
 *
 * --- Part Two ---
 * Now you're ready to decode the image. The image is rendered by stacking the layers and aligning the pixels with
 * the same positions in each layer. The digits indicate the color of the corresponding pixel: 0 is black, 1 is white,
 * and 2 is transparent.
 *
 * The layers are rendered with the first layer in front and the last layer in back. So, if a given position has
 * a transparent pixel in the first and second layers, a black pixel in the third layer, and a white pixel in the fourth
 * layer, the final image would have a black pixel at that position.
 *
 * For example, given an image 2 pixels wide and 2 pixels tall, the image data 0222112222120000 corresponds to
 * the following image layers:
 *
 * Layer 1: 02
 *          22
 *
 * Layer 2: 11
 *          22
 *
 * Layer 3: 22
 *          12
 *
 * Layer 4: 00
 *          00
 *
 * Then, the full image can be found by determining the top visible pixel in each position:
 *
 * The top-left pixel is black because the top layer is 0.
 * The top-right pixel is white because the top layer is 2 (transparent), but the second layer is 1.
 * The bottom-left pixel is white because the top two layers are 2, but the third layer is 1.
 * The bottom-right pixel is black because the only visible pixel in that position is 0 (from layer 4).
 * So, the final image looks like this:
 *
 * 01
 * 10
 * What message is produced after decoding your image?
 */

#include <algorithm>
#include <vector>

#include "../utils.h"
#include "puzzle.h"

using namespace std;

namespace day8 {

    constexpr int image_width = 25;
    constexpr int image_height = 6;

    constexpr int layer_size = image_width * image_height;

    enum color {
        black = 0,
        white = 1,
        transparent = 2
    };

    vector<layer> load_layers() {
        string data = read_lines<string>("day08/res/input.txt")[0];
        int layer_count = data.size() / layer_size;

        vector<layer> layers;
        for (int i = 0; i < layer_count; i++) {
            layer layer;
            for (char c : data.substr(i * layer_size, layer_size))
                layer.push_back(c - '0');
            layers.push_back(layer);
        }
        return layers;
    }

    const vector<layer> layers = load_layers();

    int count_digits(const layer& layer, int digit) {
        int count = 0;
        for (int color : layer)
            if (color == digit)
                count++;
        return count;
    }

    void operator&=(layer& top, const layer& bottom) {
        for (int i = 0; i < layer_size; i++) {
            if (top[i] == transparent)
                top[i] = bottom[i];
        }
    }

    image flatten_layers(const vector<layer>& layers) {
        layer result = layers[0];
        for (int i = 1; i < layers.size(); i++)
            result &= layers[i];

        return { result };
    }

    image negative(const image& img) {
        image result = img;
        for (int i = 0; i < layer_size; i++)
            if (img.data[i] == black || img.data[i] == white)
                result.data[i] = 1 - img.data[i];
        return result;
    }

    ostream& operator<<(ostream& stream, const image& img) {
        for (int i = 0; i < layer_size; i++) {
            char ascii = img.data[i] == black ? 'x' : ' ';
            stream << ascii;
            if ((i + 1) % image_width == 0)
                stream << "\n";
        }
        return stream;
    }

    int fewest_zero_digit_layer()
    {
        layer min_layer = *min_element(layers.begin(), layers.end(), [](const layer& a, const layer& b) {
            return count_digits(a, 0) < count_digits(b, 0);
        });
        return count_digits(min_layer, 1) * count_digits(min_layer, 2);
    }

    image decode_message() {
        image img = flatten_layers(layers);
        return negative(img);
    }

}