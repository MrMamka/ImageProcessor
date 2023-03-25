#include <stdexcept>
#include <cmath>
#include "filters.h"

Image Censorship::Apply(const Image &picture) {
    if (size_of_square < 1) {
        throw std::runtime_error("size can't be less than 1");
    } else if (size_of_square > std::min(picture.width, picture.height)) {
        throw std::runtime_error("size can't be more than width or height of image");
    }
    Image result = picture;
    long double red = 0;
    long double green = 0;
    long double blue = 0;
    for (uint32_t h_of_blocks = 0; h_of_blocks < std::ceil(1.0 * picture.height / size_of_square); ++h_of_blocks) {
        uint32_t h_in_block_start = h_of_blocks * size_of_square;
        uint32_t h_in_block_end = std::min((h_of_blocks + 1) * size_of_square, picture.height);
        for (uint32_t w_of_blocks = 0; w_of_blocks < std::ceil(1.0 * picture.width / size_of_square); ++w_of_blocks) {
            uint32_t w_in_block_start = w_of_blocks * size_of_square;
            uint32_t w_in_block_end = std::min((w_of_blocks + 1) * size_of_square, picture.width);
            red = green = blue = 0;
            for (uint32_t h_in_block = h_in_block_start; h_in_block < h_in_block_end; ++h_in_block) {
                for (uint32_t w_in_block = w_in_block_start; w_in_block < w_in_block_end; ++w_in_block) {
                    PlusToRGB(red, green, blue, picture.data[h_in_block][w_in_block]);
                }
            }
            DivisionToRGB(red, green, blue, (h_in_block_end - h_in_block_start) * (w_in_block_end - w_in_block_start));
            for (uint32_t h_in_block = h_in_block_start; h_in_block < h_in_block_end; ++h_in_block) {
                for (uint32_t w_in_block = w_in_block_start; w_in_block < w_in_block_end; ++w_in_block) {
                    RGBToPixel(red, green, blue, result.data[h_in_block][w_in_block]);
                }
            }
        }
    }
    return result;
}