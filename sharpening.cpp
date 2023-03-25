#include "filters.h"

void SearchAllCases(const Image &picture, int64_t &red, int64_t &green, int64_t &blue, const uint32_t &i,
                    const uint32_t &j) {
    red = 5 * picture.data[i][j].red;
    green = 5 * picture.data[i][j].green;
    blue = 5 * picture.data[i][j].blue;
    if (i == 0) {
        MinusToRGB(red, green, blue, picture.data[i][j]);
    } else {
        MinusToRGB(red, green, blue, picture.data[i - 1][j]);
    }
    if (i == picture.height - 1) {
        MinusToRGB(red, green, blue, picture.data[i][j]);
    } else {
        MinusToRGB(red, green, blue, picture.data[i + 1][j]);
    }
    if (j == 0) {
        MinusToRGB(red, green, blue, picture.data[i][j]);
    } else {
        MinusToRGB(red, green, blue, picture.data[i][j - 1]);
    }
    if (j == picture.width - 1) {
        MinusToRGB(red, green, blue, picture.data[i][j]);
    } else {
        MinusToRGB(red, green, blue, picture.data[i][j + 1]);
    }
    red = std::min(static_cast<int64_t>(255), std::max(static_cast<int64_t>(0), red));
    green = std::min(static_cast<int64_t>(255), std::max(static_cast<int64_t>(0), green));
    blue = std::min(static_cast<int64_t>(255), std::max(static_cast<int64_t>(0), blue));
}

Image Sharpening::Apply(const Image &picture) {
    Image result = picture;
    int64_t red = 0;
    int64_t green = 0;
    int64_t blue = 0;
    for (uint32_t i = 0; i < result.height; ++i) {
        for (uint32_t j = 0; j < result.width; ++j) {
            SearchAllCases(picture, red, green, blue, i, j);
            result.data[i][j].red = red;
            result.data[i][j].green = green;
            result.data[i][j].blue = blue;
        }
    }
    return result;
}