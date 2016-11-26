//------------------------------------------------------------
//
// C++ course assignment code 
//
// G. Papaioannou, 2016
//
//

#ifndef _ARRAY_IMPLEMENTATION_
#define _ARRAY_IMPLEMENTATION_

#include <algorithm>
#include <iostream>
#include "header/Array.h"

namespace math {

    //--------------------------------------------------------------------------------------------
    // This file is included from the templated Array class header.
    // TODO: Provide its member function implementations here:
    //--------------------------------------------------------------------------------------------


    //Obtains a constant pointer to the internal data.
    template<typename T>
    void *const Array<T>::getRawDataPtr() {
        return buffer;
    }

    //Returns a reference to the element at the zero-based position (column x, row y).
    template<typename T>
    T &Array<T>::operator()(int x, int y) {
        int index = x + y * getWidth();

        //checking if index is out of bounds
        if (index < 0 || index > getWidth() * getHeight()) {
            //if out of bounds, return black
            std::cout << "The pixel is outside of the area" << std::endl;
            system("PAUSE");
            exit(EXIT_FAILURE);
        }

        return Array::buffer[index];
    }

    //Returns a constant reference to the element at the zero-based position (column x, row y).
    template<typename T>
    const T &Array<T>::operator()(int x, int y) const {
        int index = x + y * getWidth();

        //checking if index is out of bounds
        if (index < 0 || index > getWidth() * getHeight()) {
            //if out of bounds, return black
            std::cout << "The pixel is outside of the area" << std::endl;
            system("PAUSE");
            exit(EXIT_FAILURE);
        }

        return Array::buffer[index];
    }

    //Constructor with width and height specification.
    template<typename T>
    Array<T>::Array(unsigned int w, unsigned int h){
        Array::width = w;
        Array::height = h;
        Array::buffer = new T[getWidth() * getHeight()];
    }


    //Copy constructor.
    template<typename T>
    Array<T>::Array(const Array<T> & source) {
        Array::width = source.width;
        Array::height = source.height;
        std::copy(source.buffer, source.buffer + getWidth() * getHeight() * sizeof(T), Array::buffer);
    }

    //Copy assignment operator.
    template<typename T>
    Array<T> &Array<T>::operator=(const Array<T> &right) {
        return *new Array<T>(right);
    }

    template<typename T>
    bool Array<T>::operator==(const Array<T> &source) const {

        //Check first, if dimensions are the same

        if (Array::getHeight() != source.getHeight()) {
            return false;
        }

        if (Array::getWidth() != source.getWidth()) {
            return false;
        }

        //Check if data, one by one, are the same
        for (unsigned int i = 0; i < getHeight() * getWidth(); i++) {
            if (Array::buffer[i] != source.buffer[i]) {
                return false;
            }
        }

        return true;
    }

    //Destructor
    template<typename T>
    Array<T>::~Array<T>() {
        if (buffer) delete[] buffer;
    }

} // namespace math

#endif