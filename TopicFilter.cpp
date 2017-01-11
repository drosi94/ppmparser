//
// Created by bdrosatos on 11/1/2017.
//

#include "header/TopicFilter.h"

namespace imaging {


    Image *TopicFilter::grayFilter() {
        //Loop through all rows of image
        for (unsigned int i = 0; i < (*image).getHeight(); i++) {
            // Loop through all columns of image
            for (unsigned int j = 0; j < (*image).getWidth(); j++) {
                // Create a temporary variable, and
                //get the color for the specific pixel
                Color color = (*image).getPixel(j, i);

                //Find for current pixel colors the average color
                float m = (color.r + color.g + color.b)/ 3;

                //Create new color with RGB the average color of pixel
                Color* newColor = new Color(m, m, m);

                //Set the new color to the current pixel
                (*image).setPixel(j, i, *newColor);
            }
        }

        return image;
    }
}