#include <cstdlib>
#include <algorithm>
#include <iostream>
#include "header/Image.h"
#include "header/ppm_format.h"

using namespace math;

namespace imaging {

    Color Image::getPixel(unsigned int x, unsigned int y) const {

        /*
         Since every pixel has 1 color, we need to
         find the row ( y * total width
         and move x columns right
        */
        int index = x + y * getWidth();

        //checking if index is out of bounds
        if (index < 0 || index > getWidth() * getHeight()) {
            //if out of bounds, return black
            return Color(0, 0, 0);
        }

        return buffer[index];

    }

    void Image::setPixel(unsigned int x, unsigned int y, Color &value) {

        //Checks if pixel is inside our bounds
        if (y >= getHeight() || x >= getWidth()) {
            std::cout << "The pixel is outside of the image area" << std::endl;
            system("PAUSE");
            exit(EXIT_FAILURE);
        }

        int index = x + y * getWidth();
        buffer[index] = value;

    }

    void Image::setData(const Color *&data_ptr) {

        //Checks if image buffer has been allocated
        //and width and height are not 0
        if (getRawDataPtr() == nullptr || getHeight() == 0 || getWidth() == 0) {
            std::cout << "Invalid image" << std::endl;
            system("PAUSE");
            exit(EXIT_FAILURE);
        }

        //Copy Duplicates data from one pointer to another
        //params of copy : 
        // starting index (data_ptr stores the first memory position),
        // ending index ( starting position + total number of colors
        // destination ( the buffer of the image)
        std::copy(data_ptr, data_ptr + getWidth() * getHeight(), Image::buffer);
    }


    //Default constructor.
    Image::Image() : Array<Color>(0, 0) {
        buffer = nullptr;
    }

    //Constructor with width and height specification.
    Image::Image(unsigned int width, unsigned int height) : Array<Color>(width, height) {
        buffer = nullptr;
    }

    //Constructor with data initialization.
    Image::Image(unsigned int width, unsigned int height, const Color *data_ptr) : Array<Color>(width, height) {
        setData(data_ptr);
    }

    //Copy constructor.
    Image::Image(const Image &src) : Array<Color>(src) {}

    //The Image destructor.
    Image::~Image() {}//Array Destructor will delete buffer pointer


    // Read the image
    bool Image::operator<<(std::string filename) {
        // Create a temp image and store the image there
        // using the ppm read
        Image *tempImage = ReadPPM(filename.c_str());
        // if the read failed, return false
        if (tempImage == NULL) {
            return false;
        }
        //Change the old dimensions with new 
        this->width = tempImage->getWidth();
        this->height = tempImage->getHeight();
        // If there is a buffer, delete it
        if (this->buffer != NULL) {
            delete buffer;
        }
        //Initialize the new buffer with the right size
        this->buffer = new Color[width * height];
        // Store the new data into the buffer
        this->setData((const Color *&) (tempImage->buffer));
        // delete the temporary image
        delete tempImage;
        // If all worked, return true
        return true;
    }

    //Write
    bool Image::operator>>(std::string filename) {
        // Just calling the write of ppm
        return WritePPM(*this, filename.c_str());

    }

}