#include <cstdlib>
#include <algorithm>
#include <iostream>
#include "header/Image.h"
#include "header/ppm_format.h"

using namespace math;

namespace imaging {

    Color Image::getPixel(unsigned int x, unsigned int y) const {

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
        //params of copy : (
        // starting index (data_ptr stores the first memory position),
        // ending index ( starting position + total number of colors
        // destination ( the buffer of the image)
        std::copy(data_ptr, data_ptr + getWidth() * getHeight(), Image::buffer);
    }

//    void Image::resize(unsigned int new_width, unsigned int new_height) {
//        //create a new temp buffer with the new dimensions
//        Color *temp = new Color[3 * new_width * new_height];
//        //for the min amount of lines of old and new dimensions
//        for (int i = 0; i < new_height && i < getHeight(); i++) {
//            //for the min amount of rows of old and new dimension
//            for (int j = 0; j < new_width && j < getWidth(); j++) {
//                //copy the active data to the temp buffer
//                temp[i * new_width + j] = buffer[i * getWidth() + j];
//            }
//        }
//
//        //delete the old buffer
//        delete[] getRawDataPtr();
//        //allocate new memory with the new dimensions
//        Image::width = new_width;
//        Image::height = new_height;
//        Image::buffer = new component_t[3 * new_width * new_height];
//
//        //copy the data to the existing bufferr
//        setData((const component_t *&) temp);
//    }

    //Default constructor.
    Image::Image() : Array<Color>(0,0) {
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
    Image::~Image() {//Array Destructor will delete buffer pointer
    }

    bool Image::operator << (std::string filename){
	    ReadPPM(filename.c_str());
        return true;
    }

    bool Image::operator >> (std::string filename){
//        return WritePPM(*this, filename.c_str());
        return true;
    }

}