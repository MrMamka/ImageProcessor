#pragma once

#include <cstdint>
#include <vector>
#include <string>

uint8_t NumOfPads(uint32_t wid);

struct Pixel {
    uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;

    bool operator==(const Pixel& other) const;
};

struct Image {
    uint32_t width = 0;
    uint32_t height = 0;
    uint32_t size = 0;
    char header[54] = {0};
    std::vector<std::vector<Pixel>> data;

    Image(const Image &other);

    Image() = default;

    void ReadFile(const std::string &path);

    void WriteFile(const std::string &path);
};