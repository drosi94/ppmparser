#include <fstream>;
#include <iostream>
#include <cstdlib>
#include "header/ppm_format.h"


using namespace std;

namespace imaging {

    Image * ReadPPM(const char *filename) {

        ifstream reader;
        unsigned int height, width;
        float maxBytes;
        int dataSize;
        unsigned char *readerData;
        string nextCharacter = "";

        //OPEN FILE IN BINARY MODE
        reader.open(filename, ios::binary);

        //HEADER

        //CHECK IF FOUND FILE AND CAN OPEN
        if (!reader.good()) {
            cout << "File not found/can not open!" << endl;
            system("PAUSE");
            exit(EXIT_FAILURE);
        }

        //READ NEXT CHARACTER
        reader >> nextCharacter;

        //CHECK IF THE FIRST CHARACTER IS VALID FORMAT "P6"
        if (nextCharacter != "P6" && nextCharacter != "p6") {
            cout << "Only P6 format is supported.!" << endl;
            system("PAUSE");
            exit(EXIT_FAILURE);
        }

        //READ WIDTH & HEIGHT
        reader >> nextCharacter;
        width = atoi(nextCharacter.c_str());
        reader >> nextCharacter;
        height = atoi(nextCharacter.c_str());

        //CHECK IF HEIGHT AND WITH ARE POSITIVE NUMBERS
        if (height <= 0 || width <= 0) {
            cout << "Height and with must be positive numbers!" << endl;
            system("PAUSE");
            exit(EXIT_FAILURE);
        }

        //READ SIZE , MUST BE <=255
        reader >> nextCharacter;
        maxBytes = atoi(nextCharacter.c_str());
        if (maxBytes > 255) {
            cout << "Only 255 bytes (24bit images) are supported" << endl;
            system("PAUSE");
            exit(EXIT_FAILURE);
        }

        //IGNORE NEW LINE FOR THE BODY PART
        reader.ignore(256, '\n');

        //BODY


        dataSize = 3*width * height;
        readerData = new unsigned char[dataSize];

        //READ BODY DATA FROM FILE, size = 3 * width * height
        reader.read((char *) readerData, dataSize);

        Color *data_ptr = new Color[dataSize];

        unsigned  int y = 0;
        //READ FOR EACH COLOR RGB(3 BYTES)
        for (unsigned int i = 0; i < dataSize; i+=3) {

            Color* color =  new Color(readerData[i] / maxBytes, readerData[i + 1] / maxBytes , readerData[i + 2] / maxBytes);
            data_ptr[y] = *color;
            y++;
        }

        //CREATE NEW IMAGE
        Image *image = new Image(width, height, data_ptr);

        delete[] data_ptr;
        return image;

    }

    bool WritePPM(Image & image, const char * filename){

        //Declare the output stream to a file
        ofstream newfile;

        //try to open the file as binary stream
        newfile.open(filename, ofstream::binary );

        //check if file opened
        if(!newfile.good()){
            //print error message
            cout << "Cannot open file.";
            return false;
        }

        //write in the file the header of ppm image
        newfile << "P6"
                << " " << image.getWidth()
                << " " << image.getHeight()
                << " " << "255"
                << " " ;

        //for each pixel
        for (unsigned int h = 0; h < image.getHeight(); h++) {
            for (unsigned int w = 0; w < image.getWidth(); w++) {		//for each pixel (3 continuous numbers from the internal buffer, starting from index 0
                //get the pixel from image
                Color color =  image.getPixel(w, h);
                //for each color channel
                //change from range 0-1 to 0-255
                //and save it to a temp array
                char temp[3];
                temp[0] = char(color.r * 255);
                temp[1] = char(color.g * 255);
                temp[2] = char(color.b * 255);
                //write current pixel on the file
//                cout << "h" << h << " w " << w;
                newfile.write(temp,3);
            }
        }
        //close file
        newfile.close();
        return true;

    }


}
