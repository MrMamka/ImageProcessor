//#include <catch.hpp>
//#include <iostream>
//
//#include "image.h"
//#include "filters.h"
//
//std::string AskAndGetAnswer(Image& input, const std::string& output, const std::string& name) {
//    std::string answer;
//    input.WriteFile(output);
//    std::cout << "Is in output " << name << '?' << std::endl;
//    std::cin >> answer;
//    return answer;
//}
//
//bool IsDataEqual(const std::vector<std::vector<Pixel>>& first, const std::vector<std::vector<Pixel>>& second) {
//    for (size_t i = 0; i < first.size(); ++i) {
//        for (size_t j = 0; j < first[0].size(); ++j) {
//            if (first[i][j] != second[i][j]) {
//                return false;
//            }
//        }
//    }
//    return true;
//}
//
//static Image image;
//static Image image2;
//const static std::string PATH_TO_IMAGE = "../projects/image_processor/examples/example.bmp";
//const static std::string PATH_TO_IMAGE2 = "../projects/image_processor/examples/example2.bmp";
//const static std::string PATH_TO_OUTPUT = "../projects/image_processor/examples/output.bmp";
//
//TEST_CASE("Check Header") {
//    image.ReadFile(PATH_TO_IMAGE);
//    image2.ReadFile(PATH_TO_IMAGE2);
//
//    REQUIRE(image.width == 2048);
//    REQUIRE(image.height == 2048);
//    REQUIRE(image.size == 12'582'966);
//
//    REQUIRE(image2.width == 1843);
//    REQUIRE(image2.height == 1037);
//    REQUIRE(image2.size == 5'736'738);
//
//    REQUIRE(AskAndGetAnswer(image, PATH_TO_OUTPUT, "image") == "yes");
//    REQUIRE(AskAndGetAnswer(image2, PATH_TO_OUTPUT, "image2") == "yes");
//}
//
//TEST_CASE("Check Crop") {
//    Image cropped_image;
//    cropped_image.ReadFile("../projects/image_processor/examples/Crop/example.bmp");
//    Image cropped_image2;
//    cropped_image2.ReadFile("../projects/image_processor/examples/Crop/example2.bmp");
//    Crop crop(800, 600);
//
//    REQUIRE(IsDataEqual(crop.Apply(image).data, cropped_image.data));
//    REQUIRE(IsDataEqual(crop.Apply(image2).data, cropped_image2.data));
//
//    crop.width = rand() % (image.width + 300) + 1;
//    crop.height = rand() % (image.height + 300) + 1;
//    cropped_image = crop.Apply(image);
//    REQUIRE(AskAndGetAnswer(cropped_image, PATH_TO_OUTPUT,
//                            "image with crop " + std::to_string(crop.width) + " " + std::to_string(crop.height)) ==
//            "yes");
//    crop.width = rand() % (image2.width + 300) + 1;
//    crop.height = rand() % (image2.height + 300) + 1;
//    cropped_image2 = crop.Apply(image2);
//    REQUIRE(AskAndGetAnswer(cropped_image2, PATH_TO_OUTPUT,
//                            "image2 with crop " + std::to_string(crop.width) + " " + std::to_string(crop.height)) ==
//            "yes");
//}
//
//TEST_CASE("Check Grayscale") {
//    Image grayscaled_image;
//    grayscaled_image.ReadFile("../projects/image_processor/examples/Grayscale/example.bmp");
//    Image grayscaled_image2;
//    grayscaled_image2.ReadFile("../projects/image_processor/examples/Grayscale/example2.bmp");
//    Grayscale gs;
//
//    REQUIRE(IsDataEqual(gs.Apply(image).data, grayscaled_image.data));
//    REQUIRE(IsDataEqual(gs.Apply(image2).data, grayscaled_image2.data));
//}
//
//TEST_CASE("Check Negative") {
//    Image negatived_image;
//    negatived_image.ReadFile("../projects/image_processor/examples/Negative/example.bmp");
//    Image negatived_image2;
//    negatived_image2.ReadFile("../projects/image_processor/examples/Negative/example2.bmp");
//    Negative neg;
//
//    REQUIRE(IsDataEqual(neg.Apply(image).data, negatived_image.data));
//    REQUIRE(IsDataEqual(neg.Apply(image2).data, negatived_image2.data));
//}
//
//TEST_CASE("Check Sharpening") {
//    Image sharped_image;
//    sharped_image.ReadFile("../projects/image_processor/examples/Sharpening/example.bmp");
//    Image sharped_image2;
//    sharped_image2.ReadFile("../projects/image_processor/examples/Sharpening/example2.bmp");
//    Sharpening sharp;
//
//    REQUIRE(IsDataEqual(sharp.Apply(image).data, sharped_image.data));
//    REQUIRE(IsDataEqual(sharp.Apply(image2).data, sharped_image2.data));
//}
//
//TEST_CASE("Check Edge Detection") {
//    Image edged_image;
//    edged_image.ReadFile("../projects/image_processor/examples/EdgeDetection/example.bmp");
//    Image edged_image2;
//    edged_image2.ReadFile("../projects/image_processor/examples/EdgeDetection/example2.bmp");
//    EdgeDetection edge(0.05);
//
//    REQUIRE(IsDataEqual(edge.Apply(image).data, edged_image.data));
//    REQUIRE(IsDataEqual(edge.Apply(image2).data, edged_image2.data));
//
//    edge.threshold = (rand() % 101) / 100.0;
//    edged_image = edge.Apply(image);
//    REQUIRE(AskAndGetAnswer(edged_image, PATH_TO_OUTPUT, "image with edge " + std::to_string(edge.threshold)) == "yes");
//    edge.threshold = (rand() % 101) / 100.0;
//    edged_image2 = edge.Apply(image2);
//    REQUIRE(AskAndGetAnswer(edged_image2, PATH_TO_OUTPUT, "image2 with edge " + std::to_string(edge.threshold)) ==
//            "yes");
//}
//
//TEST_CASE("Check Gaussian Blur") {
//    Image blured_image;
//    blured_image.ReadFile("../projects/image_processor/examples/GaussianBlur/example.bmp");
//    Image blured_image2;
//    blured_image2.ReadFile("../projects/image_processor/examples/GaussianBlur/example2.bmp");
//    GaussianBlur blur(3);
//
//    REQUIRE(IsDataEqual(blur.Apply(image).data, blured_image.data));
//    REQUIRE(IsDataEqual(blur.Apply(image2).data, blured_image2.data));
//
//    blur.sigma = ((rand() % 100) + 1) / 10.0;
//    blured_image = blur.Apply(image);
//    REQUIRE(AskAndGetAnswer(blured_image, PATH_TO_OUTPUT, "image with blur " + std::to_string(blur.sigma)) == "yes");
//    blur.sigma = ((rand() % 100) + 1) / 10.0;
//    blured_image2 = blur.Apply(image2);
//    REQUIRE(AskAndGetAnswer(blured_image2, PATH_TO_OUTPUT, "image2 with blur " + std::to_string(blur.sigma)) == "yes");
//}
//
//TEST_CASE("Check Censorship") {
//    Image censored_image;
//    censored_image.ReadFile("../projects/image_processor/examples/Censorship/example.bmp");
//    Image censored_image2;
//    censored_image2.ReadFile("../projects/image_processor/examples/Censorship/example2.bmp");
//    Censorship cens(30);
//
//    REQUIRE(IsDataEqual(cens.Apply(image).data, censored_image.data));
//    REQUIRE(IsDataEqual(cens.Apply(image2).data, censored_image2.data));
//
//    cens.size_of_square = (rand() % std::min(image.width, image.height)) + 1;
//    censored_image = cens.Apply(image);
//    REQUIRE(AskAndGetAnswer(censored_image, PATH_TO_OUTPUT,
//                            "image with censorship " + std::to_string(cens.size_of_square)) == "yes");
//    cens.size_of_square = (rand() % std::min(image2.width, image2.height)) + 1;
//    censored_image2 = cens.Apply(image2);
//    REQUIRE(AskAndGetAnswer(censored_image2, PATH_TO_OUTPUT,
//                            "image2 with censorship " + std::to_string(cens.size_of_square)) == "yes");
//}