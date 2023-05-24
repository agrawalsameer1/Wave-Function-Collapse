#include "../include/WFC.h"
#include <iostream>
#include <stdlib.h>     //for using the function sleep
#include <fstream>
#include <chrono>
#include <thread>

int main() {
    WFC* wfc = new WFC();
    const int N = 8, X = 24, Y = 24;
    //std::cout << "reached here!\n";
   /* std::cout << "Calling python script to convert image to pixels:\n";
    std::string filename = "extractPixels.py";
    std::string command = "python ";
    command += filename;
    system(command.c_str());
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));*/

    PPMImage* input = new PPMImage("../WaveFunctionCollapse/images/Forest.ppm");
    //std::ifstream myfile("pixels.txt");
    //std::cout << (*input) << std::endl;
    //exit(1);
    PPMImage output = wfc->collapse(input,N,X,Y);
    //std::cout << output << "\n";
    output.saveImage("maze.ppm");
    std::string pixelData = output.toStringBGR();
    ofstream outFile;
    outFile.open("pixels.txt", ios::out);
    outFile << pixelData;
    outFile.close();

    std::cout << "Calling python script to convert pixel output to a PNG image:\n";
    std::string filename = "./src/pixelsToPNG.py";
    std::string command = "python3 ";
    command += filename;
    system(command.c_str());
    std::cout << "Input image dimensions: " << input->y << "x" << input->x << '\n';
    std::cout << "Using an N-value of " << N << " with output dimensions of " << Y << "x" << X << '\n';
    //std::this_thread::sleep_for(std::chrono::milliseconds(3000));
}