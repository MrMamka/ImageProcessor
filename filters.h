#pragma once

#include "image.h"

void RGBToPixel(const long double &r, const long double &g, const long double &b, Pixel &pix);

void PlusToRGB(long double &r, long double &g, long double &b, const Pixel &pix);

void DivisionToRGB(long double &r, long double &g, long double &b, const uint32_t &divider);

void PlusAndMultiplyToRGB(double &r, double &g, double &b, const Pixel &pix, const double &multiplier);

void MinusToRGB(int64_t &r, int64_t &g, int64_t &b, const Pixel& pix);

void MultiplyToRGB(double &r, double &g, double &b, const Pixel &pix, const double &multiplier);

struct Filter {
    virtual Image Apply(const Image &picture) = 0;
    virtual ~Filter() = default;
};

struct Crop : public Filter {
    uint32_t width = 0;
    uint32_t height = 0;

    Crop(const uint32_t &wid, const uint32_t &high) : width(wid), height(high) {};

    Image Apply(const Image &picture) override;
};

struct Grayscale : public Filter {
    Image Apply(const Image &picture) override;
};

struct Negative : public Filter {
    Image Apply(const Image &picture) override;
};

struct Sharpening : public Filter {
    Image Apply(const Image &picture) override;
};

struct EdgeDetection : public Filter {
    double threshold = 0;

    explicit EdgeDetection(const double &thresh) : threshold(thresh) {};

    Image Apply(const Image &picture) override;
};

struct GaussianBlur : public Filter {
    double sigma = 0;

    explicit GaussianBlur(const double &sig) : sigma(sig) {};

    Image Apply(const Image &picture) override;
};

struct Censorship : public Filter {
    uint32_t size_of_square = 1;

    explicit Censorship(const int32_t &size) : size_of_square(size) {};

    Image Apply(const Image &picture) override;
};