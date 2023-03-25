cmake_minimum_required(VERSION 3.21)
project(ImageProcessor)

set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_executable(ImageProcessor
        image_processor.cpp
        filters.cpp
        filters.h
        image.cpp
        image.h
        #test.cpp
        censorship.cpp
        crop.cpp
        edge_detection.cpp
        gaussian_blur.cpp
        grayscale.cpp
        negative.cpp
        sharpening.cpp)

#add_catch(ImageProcessor
#        image_processor.cpp
#        image.cpp image.h
#        filters.cpp filters.h
#        censorship.cpp
#        crop.cpp
#        edge_detection.cpp
#        gaussian_blur.cpp
#        grayscale.cpp
#        negative.cpp
#        sharpening.cpp)
#
#add_catch(test_image_processor test.cpp
#        image.cpp
#        filters.cpp
#        censorship.cpp
#        crop.cpp
#        edge_detection.cpp
#        gaussian_blur.cpp
#        grayscale.cpp
#        negative.cpp
#        sharpening.cpp)