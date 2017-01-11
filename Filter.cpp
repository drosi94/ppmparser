#include "header/Filter.h"


namespace imaging {
    Filter::Filter() {
        image = new Image();
    }

    Filter::Filter(Image *image) {
        Filter::image = image;
    }

    void Filter::setImage(Image *image) {
        Filter::image = image;
    }

    Filter::~Filter() {
        delete image;
    }
}

