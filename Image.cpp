//
// Created by bdrosatos on 1/11/2016.
//

#include <cstdlib>
#include <algorithm>
#include <iostream>
#include "header/Image.h"

using namespace imaging;

Image::Image() {
    width = 0;
    height = 0;
    buffer = nullptr;
}

Image::Image(unsigned int width, unsigned int height) {
    Image::width = width;
    Image::height = height;
    Image::buffer = new component_t[3 * width * height];
}

Image::Image(unsigned int width, unsigned int height, const component_t *data_ptr) {
    Image::width = width;
    Image::height = height;
    Image::buffer = new component_t[3 * width * height];
    setData(data_ptr);
}

Image::Image(const Image &src) {
    Image::width = src.width;
    Image::height = src.height;
    Image::buffer = new component_t[3 * width * height];
    setData((const component_t *&) src.buffer);
}

component_t *Image::getRawDataPtr() {
    return buffer;
}

Color Image::getPixel(unsigned int x, unsigned int y) const {
    int index = 3 * y + 3 * x * width;

    if (index < 0 || index > 3 * width * height) {
        return Color(0, 0, 0);
    }

    return Color(buffer[index], buffer[index + 1], buffer[index + 2]);

}

void Image::setPixel(unsigned int x, unsigned int y, Color &value) {

    if (x >= height || y >= width) {
        std::cout << "The pixel is outside of the image area" << std::endl;
        exit(EXIT_FAILURE);
    }

    int index = 3 * y + 3 * x * width;
    buffer[index] = value.r;
    buffer[index + 1] = value.g;
    buffer[index + 2] = value.b;

}

void Image::setData(const component_t *&data_ptr) {

    if (!buffer || width == 0 || height == 0) {
        std::cout << "Width or height are zero values, or buffer is nullptr!" << std::endl;
        exit(EXIT_FAILURE);
    }
    //Copy Duplicates data from one pointer to another
    std::copy(data_ptr, data_ptr + 3 * width * height, Image::buffer);
}

void Image::resize(unsigned int new_width, unsigned int new_height) {
    Image::width = new_width;
    Image::height = new_height;
    Image::buffer = new component_t[3 * new_width * new_height];

    component_t *newBuffer = new component_t[3 * new_width * new_height];

    for (unsigned int x = 0; x < new_height; x++) {
        for (unsigned int y = 0; y < new_width; y++) {
            Color color = getPixel(x, y);
            int p = 3 * y + 3 * x * new_width;
            newBuffer[p] = color.r;
            newBuffer[p + 1] = color.g;
            newBuffer[p + 2] = color.b;
        }
    }

    setData((const component_t *&) newBuffer);
}

Image &operator=(const Image &right) {
    return *new Image(right);
}

Image::~Image() {
    if (buffer) {
        delete[] buffer;
    }
}


