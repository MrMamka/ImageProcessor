#include "filters.h"
#include <cmath>

using std::numbers::pi;

double GaussianFunction(const uint32_t &x, const uint32_t &x0, const double &sig) {
    return exp(-1 * (((x0 - x) * (x0 - x)) / (2 * (sig * sig)))) / (std::sqrt(2 * pi) * sig);
}

Image GaussianBlur::Apply(const Image &picture) {
    const auto accuracy_of_blur = static_cast<uint32_t>(3 * sigma);
    Image pic_after_one_loop = picture;
    double red = 0;
    double green = 0;
    double blue = 0;
    //Чтобы лишний раз не считать, ведь функция зависит только от расстояния:
    std::vector<double> gauss_func;
    for (uint32_t i = 0; i <= accuracy_of_blur; ++i) {
        gauss_func.push_back(GaussianFunction(0, i, sigma));
    }
    //Проход по горизонтали:
    for (uint32_t i = 0; i < picture.height; ++i) {
        for (uint32_t j = 0; j < picture.width; ++j) {
            MultiplyToRGB(red, green, blue, picture.data[i][j], gauss_func[0]);
            for (uint8_t k = 1; k <= accuracy_of_blur; ++k) {
                if (k <= j) {
                    PlusAndMultiplyToRGB(red, green, blue, picture.data[i][j - k], gauss_func[k]);
                } else {
                    PlusAndMultiplyToRGB(red, green, blue, picture.data[i][0], gauss_func[k]);
                }
            }
            for (uint8_t k = 1; k <= accuracy_of_blur; ++k) {
                if (j + k < picture.width) {
                    PlusAndMultiplyToRGB(red, green, blue, picture.data[i][j + k], gauss_func[k]);
                } else {
                    PlusAndMultiplyToRGB(red, green, blue, picture.data[i][picture.width - 1], gauss_func[k]);
                }
            }
            RGBToPixel(red, green, blue, pic_after_one_loop.data[i][j]);
        }
    }
    Image result = pic_after_one_loop;
    //Проход по вертикали:
    for (uint32_t i = 0; i < picture.height; ++i) {
        for (uint32_t j = 0; j < picture.width; ++j) {
            MultiplyToRGB(red, green, blue, pic_after_one_loop.data[i][j], gauss_func[0]);
            for (uint8_t k = 1; k <= accuracy_of_blur; ++k) {
                if (k <= i) {
                    PlusAndMultiplyToRGB(red, green, blue, pic_after_one_loop.data[i - k][j], gauss_func[k]);
                } else {
                    PlusAndMultiplyToRGB(red, green, blue, pic_after_one_loop.data[0][j], gauss_func[k]);
                }
            }
            for (uint8_t k = 1; k <= accuracy_of_blur; ++k) {
                if (i + k < picture.height) {
                    PlusAndMultiplyToRGB(red, green, blue, pic_after_one_loop.data[i + k][j], gauss_func[k]);
                } else {
                    PlusAndMultiplyToRGB(red, green, blue, pic_after_one_loop.data[picture.height - 1][j],
                                         gauss_func[k]);
                }
            }
            RGBToPixel(red, green, blue, result.data[i][j]);
        }
    }
    return result;
}