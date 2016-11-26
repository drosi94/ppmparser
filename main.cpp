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

    cout << "Image dimensions are : " << width << " X " << height << endl;

    float countR = 0, countG = 0, countB = 0;


    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            Color color = (*image).getPixel(j, i);

            countR += color.r;
            countG += color.g;
            countB += color.b;
        }
    }

    //AVERAGE NUMBER FOR EACH ONE
    float averageR = countR / (width * height);
    float averageG = countG / (width * height);
    float averageB = countB / (width * height);

    cout << "The average color of the image is : (" << averageR << "," << averageG << "," <<
         averageB << ")";

    system("PAUSE");
    return 0;

}