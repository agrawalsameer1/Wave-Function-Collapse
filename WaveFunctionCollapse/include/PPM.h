#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include <string>

#define RGB_COMPONENT_COLOR 255

class PPMPixel{
    public:
        unsigned char red,green,blue; // int between 0 and 255
        std::string toString();
        bool operator==(PPMPixel pix);
};


class PPMImage {
    public:
        int x, y;
        PPMPixel* data;

        void writePixel(int x, int y, PPMPixel pix);
        void readPPM(const char *filename);
        PPMPixel pixelAt(int xcoord, int ycoord);
        bool operator==(PPMImage img);
        friend std::ostream& operator<<(std::ostream& os, PPMImage img);
};
