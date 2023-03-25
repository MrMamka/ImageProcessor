#include "filters.h"

Image Grayscale::Apply(const Image &picture) {
    Image result = picture;
    Pixel pixel;
    for (uint32_t i = 0; i < result.height; ++i) {
        for (uint32_t j = 0; j < result.width; ++j) {
            auto color = static_cast<uint8_t>(picture.data[i][j].red * 0.299 + picture.data[i][j].green * 0.587 +
                                              picture.data[i][j].blue * 0.114);
            pixel.red = pixel.green = pixel.blue = color;
            result.data[i][j] = pixel;
        }
    }
    return result;
}