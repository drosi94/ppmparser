// Eirini Katsadaki 3120228
// Niki Papagora 3120140


#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "header/ppm_format.h"

using namespace imaging;
using namespace std;

const char* getRawName(const char *path);

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
    Filter *filter = new Filter(image);

    //for each argument pair ( -f filterName)
    for (int i = 1; i < argc - 1; i++) {
        //check if the first part is -f
        if (strcmp(argv[i], "-f") == 0) {
            //Move to next argument
            i++;

            //Find the filter to be used
            if (strcmp(argv[i], "gray") == 0) {

                filter->gray();
                i++;
                cout << "Gray filter used" << endl;
            } else if (strcmp(argv[i], "color") == 0) {
                Color *color = new Color(argv[i + 1], argv[i + 2], argv[i + 3]);
                filter->color(color);
                delete color;
                i += 4;
                cout << "Color filter used" << endl;
            } else if (strcmp(argv[i], "blur") == 0) {
                filter->blur();
                i++;
                cout << "Blur filter used" << endl;
            } else if (strcmp(argv[i], "diff") == 0) {
                filter->diff();
                i++;
                cout << "Diff filter used" << endl;
            } else if (strcmp(argv[i], "median") == 0) {
                filter->median();
                i++;
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


    if (!(*image >> ppmPath)) {
        // If failed, print a error and exit
        cout << "Error on writing the file" << endl;
        system("PAUSE");
        exit(EXIT_FAILURE);
    }

//    const char * path = ppmPath.c_str();
//
//    const char* name = getRawName(path);

    system("PAUSE");
    return 0;

}

////Get the raw name of ppm, without the path and the extension
//const char* getRawName(const char* path) {
//    if (!path) return nullptr;
//
//    int size = 0;
//    int position = 0;
//    int length = int(strlen(path));
//    int index = length - 1;
//
//    while (index > 0) {
//        if (path[index] == '\\' || path[index] == '/') {
//            position = index+1;
//            break;
//        }
//        index--;
//    }
//
//   length = length-position;
////    cout << position << endl;
//
//     char* name;
//    memcpy(name, path[position],length);
//
//    return path;
//}