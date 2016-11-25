// Eirini Katsadaki 3120228
// Niki Papagora 3120140


#include <iostream>
#include <cstdio>
#include <cstdlib>

#include "header/ppm_format.h"

using namespace imaging;
using namespace std;

int main(int argc, char *argv[]) {

    char *ppmPath = new char[50];

    if (argc == 2) { // argc the number of extra parameters
        ppmPath = argv[1]; // argv[0] -> the name of .out file, argv[1] -> the extra parameter, the image file path
    } else if (argc == 1) {
        printf("Enter the name of the ppm file to get the details: ");
        std::cin >> ppmPath;
    }

    Image *image = ReadPPM(ppmPath);

    int width = (*image).getWidth();
    int height = (*image).getHeight();
    component_t *data_ptr = (*image).getRawDataPtr();

    cout << "Image dimensions are : " << width << " X " << height << endl;

    component_t countR = 0, countG = 0, countB = 0;

    //TOTAL RED, GREEN, BLUE
    for (int i = 0; i < 3* width * height; i+=3) {
        countR += data_ptr[i + 0];
        countG += data_ptr[i + 1];
        countB += data_ptr[i + 2];
    }

    //AVERAGE NUMBER FOR EACH ONE
    component_t averageR = countR / (width * height);
    component_t averageG = countG / (width * height);
    component_t averageB = countB / (width * height);

    cout << "The average color of the image is : (" << averageR << "," << averageG << "," <<
         averageB << ")";

    delete[] data_ptr;
    system("PAUSE");
    return 0;

}