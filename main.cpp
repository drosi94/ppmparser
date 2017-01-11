// Eirini Katsadaki 3120228
// Niki Papagora 3120140


#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "header/ppm_format.h"
#include "header/Filter.h"
#include "header/TopicFilter.h"

using namespace imaging;
using namespace std;



bool isNumber(const string &s);


int main(int argc, char *argv[]) {

    //The path of the image to be loaded
    // it's always the last argument
    string ppmPath = argv[argc - 1];

    //Create a empty image, where the image will
    //be stored after read
    Image *image = new Image();
    //Try to read the image
    if (!(*image << ppmPath)) {
        //If any error occured, print the error message and stop
        cout << "Error on reading the file" << endl;
        system("PAUSE");
        exit(EXIT_FAILURE);
    }

    //Create a new Filter object
    Filter *topicFilter = new TopicFilter(image);

    //for each argument pair ( -f filterName)
    for (int i = 1; i < argc - 1; i++) {
        //check if the first part is -f
        if (strcmp(argv[i], "-f") == 0) {
            //Move to next argument
            i++;

            //Find the filter to be used
            if (strcmp(argv[i], "gray") == 0) {
                image = topicFilter->gray();
                cout << "Gray filter used" << endl;
            } else if (strcmp(argv[i], "color") == 0) {
                if (!isNumber(argv[i + 1]) || !isNumber(argv[i + 2]) || !isNumber(argv[i + 3])) {
                    cout << "Error on parameters. Color filter used without color values " << endl;
                    system("PAUSE");
                    exit(EXIT_FAILURE);
                }

                Color *color = new Color(atof(argv[i + 1]), atof(argv[i + 2]), atof(argv[i + 3]));
                image = topicFilter->color(color);
                delete color;
                i += 3;
                cout << "Color filter used" << endl;
            } else if (strcmp(argv[i], "blur") == 0) {
//                filter->blur();
                cout << "Blur filter used" << endl;
            } else if (strcmp(argv[i], "diff") == 0) {
//                filter->diff();
                cout << "Diff filter used" << endl;
            } else if (strcmp(argv[i], "median") == 0) {
//                filter->median();
                cout << "Median filter used" << endl;
            } else {
                //If any error occured, print the error message and stop
                cout << "Wrong filter name" << endl;
                system("PAUSE");
                exit(EXIT_FAILURE);
            }

        } else {
            cout << "No more filters" << endl;
            break;
        }
    }

    string newExtention = ".filtered.ppm";

    string name = ppmPath.replace(ppmPath.end()-4,ppmPath.end(),newExtention);

    if (!(*image >> name)) {
        // If failed, print a error and exit
        cout << "Error on writing the file" << endl;
        system("PAUSE");
        exit(EXIT_FAILURE);
    }

    system("PAUSE");
    return 0;

}



//Stackoverflow
bool isNumber(const string &s) {
    bool hitDecimal = 0;
    for (char c : s) {
        if (c == '.' && !hitDecimal) // 2 '.' in string mean invalid
            hitDecimal = 1; // first hit here, we forgive and skip
        else if (!isdigit(c))
            return 0; // not ., not
    }
    return 1;
}