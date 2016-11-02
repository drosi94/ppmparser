#include <iostream>
#include <cstdio>
#include <cstdlib>

#include "header/ppm_format.h"

using namespace imaging;
using namespace std;

int main(int argc, char *argv[]) {

    char* ppmPath = new char[50];

    if (argc == 2) { // argc the number of extra parameters
        ppmPath = argv[1]; // argv[0] -> the name of .out file, argv[1] -> the extra parameter
    } else if (argc == 1){
        printf("Enter the name of the ppm file to get the details: ");
        std::cin >> ppmPath;
    }

    Image * image = ReadPPM(ppmPath);

    int width = (*image).getWidth();
    int height = (*image).getHeight();
    component_t * buffer = (*image).getRawDataPtr();

    cout << "Dimensions are : " << width << " X " << height << endl;

    system("PAUSE");
    return 0;

}