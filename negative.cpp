#include "filters.h"

Image Negative::Apply(const Image &picture) {
    Image result = picture;
    Pixel pixel;
    for (uint32_t i = 0; i < result.height; ++i) {
        for (uint32_t j = 0; j < result.width; ++j) {
            pixel.red = 255 - picture.data[i][j].red;
            pixel.green = 255 - picture.data[i][j].green;
            pixel.blue = 255 - picture.data[i][j].blue;
            result.data[i][j] = pixel;
        }
    }
    return result;
}