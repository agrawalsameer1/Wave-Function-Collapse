#include "../include/PPM.h"

int main(){
    PPMImage *image = new PPMImage();
    image->readPPM("/Users/sameeragrawal/Desktop/hello.ppm");

    std::cout << image->y << " x " << image->x << "\n";

    std::cout << *image << "\n";
}