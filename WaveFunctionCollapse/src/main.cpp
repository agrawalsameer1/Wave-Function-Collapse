#include "../include/WFC.h"
#include <iostream>
#include <stdlib.h>     //for using the function sleep
#include <fstream>
#include <chrono>
#include <thread>

int main() {
    WFC* wfc = new WFC();
    std::cout << "reached here!\n";
   /* std::cout << "Calling python script to convert image to pixels:\n";
    std::string filename = "extractPixels.py";
    std::string command = "python ";
    command += filename;
    system(command.c_str());
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));*/

    PPMImage* input = new PPMImage("../WaveFunctionCollapse/images/wsp.ppm");
    //std::ifstream myfile("pixels.txt");
    std::cout << (*input) << std::endl;
    //exit(1);
    PPMImage output = wfc->collapse(input,3,18,18);
    std::cout << output << "\n";
    output.saveImage("maze.ppm");
    /*std::string pixelData = output.toStringBGR();
    ofstream outFile;
    outFile.open("pixels.txt", ios::out);
    outFile << pixelData;
    outFile.close();*/

    /*std::cout << "Calling python script to convert pixel output to a PNG image:\n";
    std::string filename = "pixelsToPNG.py";
    std::string command = "python ";
    command += filename;
    system(command.c_str());*/
    //std::this_thread::sleep_for(std::chrono::milliseconds(3000));
}