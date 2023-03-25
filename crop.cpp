#include "filters.h"

Image Crop::Apply(const Image &picture) {
    Image result;
    result.width = std::min(width, picture.width);
    result.height = std::min(height, picture.height);
    uint8_t num_of_pads = NumOfPads(width);
    result.size = result.width * result.height *
                      (sizeof(picture.data[0][0].blue) + sizeof(picture.data[0][0].green) +
                       sizeof(picture.data[0][0].red)) + num_of_pads * result.height + 54;
    memcpy(&result.header, &picture.header, 54);
    result.data.resize(result.height);
    for (uint32_t i = 0; i < result.height; ++i) {
        result.data[i].resize(result.width);
    }
    for (uint32_t i = 0; i < result.height; ++i) {
        for (uint32_t j = 0; j < result.width; ++j) {
            result.data[i][j] = picture.data[i + picture.height - result.height][j];
        }
    }
    return result;
}