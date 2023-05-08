#include "../include/WFC.h"
#include <iostream>
#include <stdlib.h>     //for using the function sleep
#include <fstream>

int main() {
    WFC* wfc = new WFC();
    std::cout << "reached here!\n";
    std::cout << "Calling python script to convert image to pixels:\n";
    std::string filename = "/home/abc/xyz/script.py";
    std::string command = "python ";
    command += filename;
    system(command.c_str());
    std::sleep(3000);

    //PPMImage* input = new PPMImage("../images/wsp.ppm");
    std::ifstream myfile("pixels.txt");
    //std::cout << (*input) << std::endl;
    PPMImage output = wfc->collapse(*input, 2, 100,100);
    output.saveImage("output.ppm");
}