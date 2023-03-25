#include <stdexcept>
#include <cmath>
#include "filters.h"


void SearchAllCases(const Image &picture, int64_t &red, const uint32_t &i, const uint32_t &j) {
    red = 4 * picture.data[i][j].red;
    if (i == 0) {
        red -= picture.data[i][j].red;
    } else {
        red -= picture.data[i - 1][j].red;
    }
    if (i == picture.height - 1) {
        red -= picture.data[i][j].red;
    } else {
        red -= picture.data[i + 1][j].red;
    }
    if (j == 0) {
        red -= picture.data[i][j].red;
    } else {
        red -= picture.data[i][j - 1].red;
    }
    if (j == picture.width - 1) {
        red -= picture.data[i][j].red;
    } else {
        red -= picture.data[i][j + 1].red;
    }
}

Image EdgeDetection::Apply(const Image &picture) {
    Grayscale gs;
    Image pic_after_gs = gs.Apply(picture);
    Image result = pic_after_gs;
    auto int_threshold = static_cast<uint8_t>(std::ceil(255 * threshold));
    int64_t red = 0;
    for (uint32_t i = 0; i < result.height; ++i) {
        for (uint32_t j = 0; j < result.width; ++j) {
            SearchAllCases(pic_after_gs, red, i, j);
            if (red > int_threshold) {
                result.data[i][j].red = result.data[i][j].green = result.data[i][j].blue = 255;
            } else {
                result.data[i][j].red = result.data[i][j].green = result.data[i][j].blue = 0;
            }
        }
    }
    return result;
}