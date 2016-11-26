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

}
