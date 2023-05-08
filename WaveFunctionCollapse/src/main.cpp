#include "../include/WFC.h"

int main() {
    WFC* wfc = new WFC();
    std::cout << "reached here!\n";
    PPMImage* input = new PPMImage("../images/wsp.ppm");
    std::cout << (*input) << std::endl;
    PPMImage output = wfc->collapse(*input, 2, 100,100);
    output.saveImage("output.ppm");
}