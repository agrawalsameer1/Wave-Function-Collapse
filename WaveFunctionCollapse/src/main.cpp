#include "../include/WFC.h"

int main() {
    WFC* wfc = new WFC();
    std::cout << "reached here!\n";
    PPMImage* input = new PPMImage("/Users/sameeragrawal/Desktop/Forest.ppm");
    std::cout << (*input) << "\n";
    PPMImage output = wfc->collapse(*input, 2, 100,100);
    output.saveImage("output.ppm");
}