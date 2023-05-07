#include "../include/WFC.h"

int main() {
    WFC* wfc = new WFC();
    std::cout << "reached here!\n";
    PPMImage* input = new PPMImage("/Users/sameeragrawal/Desktop/wsp.ppm");
    std::cout << (*input) << "\n";
    PPMImage output = wfc->collapse(*input, 3, 60,60);
    output.saveImage("output.ppm");
}