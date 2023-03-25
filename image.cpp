#include <fstream>
#include <iostream>
#include "image.h"

uint8_t NumOfPads(uint32_t wid) {
    return (4 - 3 * wid % 4) % 4;
}

Image::Image(const Image &other) : width(other.width), height(other.height), size(other.size), data(other.data) {
    memcpy(&header, &other.header, 54);
}

bool Pixel::operator==(const Pixel &other) const {
    return (red == other.red) && (green == other.green) && (blue == other.blue);
}

void Image::ReadFile(const std::string &path) {
    std::ifstream input_stream(path, std::ios::binary);
    if (!input_stream.is_open()) {
        throw std::runtime_error("File to open didn't find");
    }
    uint16_t tmp2 = 0;
    input_stream.read(reinterpret_cast<char *>(&tmp2), sizeof(tmp2));
    if (static_cast<int>(tmp2) != 19778) {
        throw std::runtime_error("File is not BMP");
    }
    input_stream.read(reinterpret_cast<char *>(&size), sizeof(size));
    uint32_t tmp4 = 0;
    input_stream.seekg(0xA);
    input_stream.read(reinterpret_cast<char *>(&tmp4), sizeof(tmp4));
    if (static_cast<int>(tmp4) != 54) {
        throw std::runtime_error("Wrong format of BMP");
    }
    input_stream.read(reinterpret_cast<char *>(&tmp4), sizeof(tmp4));
    if (static_cast<int>(tmp4) != 40) {
        throw std::runtime_error("Wrong format of BMP");
    }
    input_stream.read(reinterpret_cast<char *>(&width), sizeof(width));
    input_stream.read(reinterpret_cast<char *>(&height), sizeof(height));
    input_stream.read(reinterpret_cast<char *>(&tmp2), sizeof(tmp2));
    if (static_cast<int>(tmp2) != 1) {
        throw std::runtime_error("Number of color planes in BMP must be 1");
    }
    input_stream.read(reinterpret_cast<char *>(&tmp2), sizeof(tmp2));
    if (static_cast<int>(tmp2) != 24) {
        throw std::runtime_error("Number of bits per pixel in BMP must be 24");
    }
    input_stream.read(reinterpret_cast<char *>(&tmp4), sizeof(tmp4));
    if (static_cast<int>(tmp4) != 0) {
        throw std::runtime_error("BMP must be without compression");
    }
    input_stream.seekg(0x2E);
    input_stream.read(reinterpret_cast<char *>(&tmp4), sizeof(tmp4));
    if (static_cast<int>(tmp4) != 0) {
        throw std::runtime_error("BMP must be without palette");
    }
    input_stream.seekg(0x0);
    input_stream.read(reinterpret_cast<char *>(&header), 0x36);

    data.resize(height);
    for (uint32_t i = 0; i < height; ++i) {
        data[i].resize(width);
    }
    uint8_t num_of_pads = NumOfPads(width);
    Pixel pixel;
    for (uint32_t i = 0; i < height; ++i) {
        for (uint32_t j = 0; j < width; ++j) {
            input_stream.read(reinterpret_cast<char *>(&pixel.blue), sizeof(pixel.blue));
            input_stream.read(reinterpret_cast<char *>(&pixel.green), sizeof(pixel.green));
            input_stream.read(reinterpret_cast<char *>(&pixel.red), sizeof(pixel.red));
            data[i][j] = pixel;
        }
        input_stream.ignore(num_of_pads);
    }
    input_stream.close();
}

void Image::WriteFile(const std::string &path) {
    std::ofstream output_stream(path, std::ios::binary);
    if (!output_stream.is_open()) {
        throw std::runtime_error("File to write didn't open");
    }
    output_stream.write(reinterpret_cast<char *>(&header), 2);
    output_stream.write(reinterpret_cast<char *>(&size), 4);
    output_stream.write(reinterpret_cast<char *>(header + 6), 12);
    output_stream.write(reinterpret_cast<char *>(&width), 4);
    output_stream.write(reinterpret_cast<char *>(&height), 4);
    output_stream.write(reinterpret_cast<char *>(header + 0x1A), 28);
    uint8_t num_of_pads = NumOfPads(width);
    char pad = 0;
    for (uint32_t i = 0; i < height; ++i) {
        for (uint32_t j = 0; j < width; ++j) {
            output_stream.write(reinterpret_cast<char *>(&data[i][j].blue), sizeof(data[i][j].blue));
            output_stream.write(reinterpret_cast<char *>(&data[i][j].green), sizeof(data[i][j].green));
            output_stream.write(reinterpret_cast<char *>(&data[i][j].red), sizeof(data[i][j].red));
        }
        for (uint8_t j = 0; j < num_of_pads; j++) {
            output_stream.put(pad);
        }
    }
    output_stream.close();
}
