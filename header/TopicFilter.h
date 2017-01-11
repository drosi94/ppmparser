#ifndef PPMPARSER_TOPICFILTER_H
#define PPMPARSER_TOPICFILTER_H

#include "Filter.h"

namespace imaging {


    class TopicFilter: public Filter {

    public:

        TopicFilter() : Filter() {};

        TopicFilter(Image *image) : Filter(image) {};

        Image* gray();
        Image* color(Color* color);

    };

}

#endif //PPMPARSER_TOPICFILTER_H
