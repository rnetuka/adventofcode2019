//
// Created by rnetuka on 08.12.19.
//

#pragma once

#include <ostream>
#include <vector>

namespace day8 {

    using layer = std::vector<int>;

    struct image {
        layer data;
    };

    int fewest_zero_digit_layer();
    image decode_message();

    std::ostream& operator<<(std::ostream& stream, const image& img);

}