#include "../include/WFC.h"

int main() {
    WFC* wfc = new WFC();
    std::cout << "reached here!\n";
    PPMImage input = PPMImage("/Users/sameeragrawal/Desktop/Forest.ppm");

    for (int i = 0; i < input.x*input.y; i++) {
        ;//std::cout << input.data[i].toString() << "\n";
    }
    
    PPMImage output = wfc->collapse(input, 2, 100,100);
    output.saveImage("output.ppm");
}