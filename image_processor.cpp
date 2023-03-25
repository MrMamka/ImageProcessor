#include <stdexcept>
#include <iostream>
#include "image.h"
#include "filters.h"

int main(int argc, char *argv[]) {
    if (argc == 1) {
        std::cout << "You must write path for file to read and path for file to write\n"
                     "Then you may use filters on image. List of available filter:\n"
                     "Crop (-crop) with 2 arguments - width and height of new cropped image.\n"
                     "Grayscale (-gs) without arguments - converts the image to shades of gray.\n"
                     "Negative (-neg) without arguments - converts the image to negative.\n"
                     "Sharpening (-sharp) without arguments - increases sharpness of the image.\n"
                     "EdgeDetection (-edge) with 1 argument (between 0 and 1) - highlights borders of the image.\n"
                     "GaussianBlur (-blur) with 1 argument (degree of blur) - blurring the image.\n"
                     "Censorship (-censor) with 1 argument (size of new pixels) - censoring the image.\n";
        return 0;
    }
    if (argc == 2) {
        throw std::runtime_error("You must write path for file to write");
    }
    std::vector<std::string> args(argv, argv + argc);
    Image image;
    image.ReadFile(args[1]);
    int i = 3;
    while (i < argc) {
        if (args[i] == "-crop") {
            if (i + 2 >= argc) {
                throw std::runtime_error("Not enough arguments for crop");
            }
            if (!std::all_of(args[i + 1].begin(), args[i + 1].end(), isdigit) ||
                !std::all_of(args[i + 2].begin(), args[i + 2].end(), isdigit)) {
                throw std::runtime_error("Arguments of crop must be integer numbers");
            }
            Crop crop(std::stoi(args[i + 1]), std::stoi(args[i + 2]));
            image = crop.Apply(image);
            i += 2;
        } else if (args[i] == "-gs") {
            Grayscale gs;
            image = gs.Apply(image);
        } else if (args[i] == "-neg") {
            Negative neg;
            image = neg.Apply(image);
        } else if (args[i] == "-sharp") {
            Sharpening sharp;
            image = sharp.Apply(image);
        } else if (args[i] == "-edge") {
            if (i + 1 == argc) {
                throw std::runtime_error("Not enough argument for edge detection");
            }
            try {
                std::stod(args[i + 1]);
            }
            catch (std::invalid_argument const&) {
                throw std::runtime_error("Argument of edge detection must be number");
            }
            if (std::stod(args[i + 1]) > 1 || std::stod(args[i + 1]) < 0) {
                throw std::runtime_error("Argument of edge detection must be number between 0 and 1");
            }
            EdgeDetection edge(std::stod(args[i + 1]));
            image = edge.Apply(image);
            ++i;
        } else if (args[i] == "-blur") {
            if (i + 1 == argc) {
                throw std::runtime_error("Not enough argument for gaussian blur");
            }
            try {
                GaussianBlur blur(std::stod(args[i + 1]));
                image = blur.Apply(image);
            }
            catch (std::invalid_argument const&) {
                throw std::runtime_error("Argument of gaussian blur must be number");
            }
            ++i;
        } else if (args[i] == "-censor") {
            if (i + 1 == argc) {
                throw std::runtime_error("Not enough argument for censorship");
            }
            if (!std::all_of(args[i + 1].begin(), args[i + 1].end(), isdigit)) {
                throw std::runtime_error("Argument of censorship must be integer number");
            }
            Censorship censor(std::stoi(args[i + 1]));
            image = censor.Apply(image);
            ++i;
        } else {
            throw std::runtime_error("Filter not found");
        }
        ++i;
    }
    image.WriteFile(args[2]);

    return 0;
}