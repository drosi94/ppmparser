//
// Created by bdrosatos on 11/1/2017.
//

#ifndef PPMPARSER_TOPICFILTER_H
#define PPMPARSER_TOPICFILTER_H

#include "Filter.h"

namespace imaging {


    class TopicFilter: public Filter {

    public:

        TopicFilter() : Filter() {};

        TopicFilter(Image *image) : Filter(image) {};

        Image* grayFilter();

    };

}

#endif //PPMPARSER_TOPICFILTER_H
