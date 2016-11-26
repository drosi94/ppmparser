#include <cstdlib>
#include <algorithm>
#include <iostream>
#include "header/Image.h"


namespace imaging {

    component_t *Image::getRawDataPtr() {
        //Returning the pointer
        return buffer;
    }

    Color Image::getPixel(unsigned int x, unsigned int y) const {
        /*
          Since every pixel has 3 values, we need to
          find the row (3 * y * total width
          and move 3 * x columns right
         */
        int index = 3 * x + 3 * y * getWidth();

        //checking if index is out of bounds
        if (index < 0 || y >= getHeight() || x >= getWidth()) {
            //if out of bounds, return black
            return Color(0, 0, 0);
        }

        //from the starting position, make a new color with the current
        // and the next 2 values.
        return Color(buffer[index], buffer[index + 1], buffer[index + 2]);

    }

    void Image::setPixel(unsigned int x, unsigned int y, Color &value) {

        //Checks if pixel is inside our bounds
        if (y >= getHeight() || x >= getWidth()) {
            std::cout << "The pixel is outside of the image area" << std::endl;
            system("PAUSE");
            exit(EXIT_FAILURE);
        }

        /*
         Since every pixel has 3 values, we need to
         find the row (3 * y * total width
         and move 3 * x columns right
        */

        int index = 3 * x + 3 * y * getWidth();
        buffer[index] = value.r;
        buffer[index + 1] = value.g;
        buffer[index + 2] = value.b;

    }

    void Image::setData(const component_t *&data_ptr) {

        //Checks if image buffer has been allocated
        //and width and height are not 0
        if (getRawDataPtr() == nullptr || getHeight() == 0 || getWidth() == 0) {
            std::cout << "Invalid image" << std::endl;
            system("PAUSE");
            exit(EXIT_FAILURE);
        }

        //Copy Duplicates data from one pointer to another
        //params of copy : (
        // starting index (data_ptr stores the first memory position),
        // ending index ( starting position + total number of colors
        // destination ( the buffer of the image)
        std::copy(data_ptr, data_ptr + 3 * getWidth() * getHeight(), Image::buffer);
    }

    // changes the size of the image and fills with black if there are any added areas
    void Image::resize(unsigned int new_width, unsigned int new_height) {

        // Create a new temp buffer for the resized image, with the new size
        component_t *new_buffer = new component_t[3 * new_width * new_height];

        //Loop through each row (as height)
        for (unsigned int h= 0; h < new_height; h++) {
            // and each column ( as width)
            for (unsigned int w = 0; w < new_width; w++) {
                // Gets the RBG values of the image, if the current pixel
                // is inside our original
                // if pixel is not in the image returns black ( 0,0,0 )
                Color color = getPixel(w, h);
                int p = 3 * w + 3 * h * new_width;
                new_buffer[p] = color.r;
                new_buffer[p + 1] = color.g;
                new_buffer[p + 2] = color.b;
            }
        }
        //delete the old buffer
        delete[] getRawDataPtr();
        //allocate new memory with the new dimensions
        Image::width = new_width;
        Image::height = new_height;
        Image::buffer = new component_t[3 * new_width * new_height];

        //copy the data to the existing bufferr
        setData((const component_t *&) new_buffer);

        //free the memory
        delete[] new_buffer;
    }


//Default constructor.
    Image::Image() {
        width = 0;
        height = 0;
        buffer = nullptr;
    }

//Constructor with width and height specification.
    Image::Image(unsigned int width, unsigned int height) {
        Image::width = width;
        Image::height = height;
        Image::buffer = new component_t[3 * getWidth() * getHeight()];
    }

//Constructor with data initialization.
    Image::Image(unsigned int width, unsigned int height, const component_t *data_ptr) {
        Image::width = width;
        Image::height = height;
        Image::buffer = new component_t[3 * getWidth() * getHeight()];
        setData(data_ptr);
    }

//Copy constructor.
    Image::Image(const Image &src) {
        Image::width = src.width;
        Image::height = src.height;
        Image::buffer = new component_t[3 * getWidth() * getHeight()];
        setData((const component_t *&) src.buffer);
    }

//The Image destructor.
    Image::~Image() {
        if (buffer) {
            delete[] buffer;
        }
    }

//Copy assignment operator.
    Image &Image::operator=(const Image &right) {
        return *new Image(right);
    }
}