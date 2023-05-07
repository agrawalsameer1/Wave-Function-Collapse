#include "../include/WFC.h"

int main() {
    WFC* wfc = new WFC();
    PPMImage* input = new PPMImage();
    input->readPPM("/Users/sameeragrawal/Desktop/Spirals.ppm");
    wfc->collapse(*input, 3, 60,60);
    
}