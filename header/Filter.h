#include "Image.h"

#ifndef PPMPARSER_FILTER_H
#define PPMPARSER_FILTER_H

namespace imaging {

    //Abstract class
    class Filter {

    protected :
        Image *image;

        //Constructors declared as protected to prevent user to create instances of Filter (Abstract class)
        Filter();

        Filter(Image *image);


    public:

        void setImage(Image *image);

        //Virtual Methods will overrided by sub classes
        virtual Image* grayFilter() = 0;

        virtual Image* colorFilter(Color* color) = 0;

        virtual ~Filter();

    };

}

#endif //PPMPARSER_FILTER_H
