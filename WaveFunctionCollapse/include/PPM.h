#pragma once

#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include <string>
#include <fstream>

#define RGB_COMPONENT_COLOR 255

class PPMPixel{
    public:
        unsigned char red,green,blue; // int between 0 and 255
        std::string toString();
        std::string toStringBGR();
        bool operator==(PPMPixel pix);
};

class PPMImage {
    public:
        int x, y;
        PPMPixel* data;
        
        PPMImage();
        PPMImage(int X, int Y);
        PPMImage(const char *filename);
        void writePixel(int x, int y, PPMPixel* pix);
        PPMPixel pixelAt(int xcoord, int ycoord);
        void operator=(PPMImage img);
        bool operator==(PPMImage img);
        void saveImage(const char *filename);
        friend std::ostream& operator<<(std::ostream& os, PPMImage img);
};
