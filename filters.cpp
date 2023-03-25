#include "image.h"

void RGBToPixel(const long double &r, const long double &g, const long double &b, Pixel &pix) {
    pix.red = static_cast<uint8_t>(r);
    pix.green = static_cast<uint8_t>(g);
    pix.blue = static_cast<uint8_t>(b);
}

void PlusToRGB(long double &r, long double &g, long double &b, const Pixel &pix) {
    r += pix.red;
    g += pix.green;
    b += pix.blue;
}

void DivisionToRGB(long double &r, long double &g, long double &b, const uint32_t &divider) {
    r /= divider;
    g /= divider;
    b /= divider;
}

void PlusAndMultiplyToRGB(double &r, double &g, double &b, const Pixel &pix, const double &multiplier) {
    r += pix.red * multiplier;
    g += pix.green * multiplier;
    b += pix.blue * multiplier;
}

void MinusToRGB(int64_t &r, int64_t &g, int64_t &b, const Pixel& pix) {
    r -= pix.red;
    g -= pix.green;
    b -= pix.blue;
}

void MultiplyToRGB(double &r, double &g, double &b, const Pixel &pix, const double &multiplier) {
    r = pix.red * multiplier;
    g = pix.green * multiplier;
    b = pix.blue * multiplier;
}