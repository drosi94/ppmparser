// Eirini Katsadaki 3120228
// Niki Papagora 3120140


#include <iostream>
#include <cstdio>
#include <cstdlib>

#include "header/ppm_format.h"

using namespace imaging;
using namespace std;

int main(int argc, char *argv[]) {

    //The path of the image to be loaded
    string ppmPath;
    // argc the number of extra parameters
    if (argc == 2 || argc == 4) { 
        ppmPath = argv[1]; // argv[0] -> the name of .out file, argv[1] -> the extra parameter, the image file path
    //If no path was declared in arguments
    } else if (argc == 1) {
        printf("Enter the name of the ppm file to get the details: ");
        //Read the pah from command line
        std::cin >> ppmPath;
    }

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

    //Get the dimensions of image
    int width = (*image).getWidth();
    int height = (*image).getHeight();
    // Print the dimensions
    cout << "Image dimensions are : " << width << " X " << height << endl;

    //Variables to calculate the average colors
    float countR = 0, countG = 0, countB = 0;

    //Loop through all rows of image
    for (unsigned int i = 0; i < height; i++) {
        // Loop through all columns of image
        for (unsigned int j = 0; j < width; j++) {
            // Create a temporary variable, and
            //get the color for the specific pixel
            Color color = (*image).getPixel(j, i);
            //Add the values for each color
            countR += color.r;
            countG += color.g;
            countB += color.b;
        }
    }

    //AVERAGE NUMBER FOR EACH ONE
    float averageR = countR / (width * height);
    float averageG = countG / (width * height);
    float averageB = countB / (width * height);

    //Print the average of colors
    cout << "The average color of the image is : (" << averageR << "," << averageG << "," <<
         averageB << ")" << endl;
    //If there are 4 arguments
    if (argc == 4) {
        // and the third is '-o'
        if (strcmp(argv[2], "-o") == 0){
            // Write the image to file
            // argv[3] -> Path and name of output file
            if (!(*image >> argv[3])) {
                // If failed, print a error and exit
                cout << "Error on writing the file" << endl;
                system("PAUSE");
                exit(EXIT_FAILURE);
            }
        }    
    }
    
    system("PAUSE");
    return 0;

}