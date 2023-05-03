#include <iostream>
#include <algorithm>
#include <random>
#include "WFC.h"
#include "../include/PPM.h"

// Hey, pal. Looks like you just collapsed your last wave function *pulls out a coconut gun*

void WFC::wfc()
{
	// Define grid position
	int x = 0, y = 0;

	// Start with the first Element in the output
	observe(output[y][x].wave);

}

void observe(Wave* wave)
{
	// since every Pattern is weighted, we'll use a vector to hold all possible Patterns in the distribution.
	// Weight is implemented via duplicates in the vector
	vector<Pattern> distribution;
	for (int i = 0; i < wave->domain.size(); i++)
	{
		for (int i = 0; i < pattern.weight; i++) distribution.push_back(pattern);
	}
	// Shuffle the distribution
	auto rng = std::default_random_engine{};
	std::shuffle(std::begin(cards_), std::end(cards_), rng);
	// ...and pick a Pattern.
	int randomIndex = rand() % SP.size();

int main(){
    PPMImage *image = new PPMImage();
    image->readPPM("/Users/sameeragrawal/Desktop/hello.ppm");

    std::cout << image->y << " x " << image->x << "\n";

    std::cout << *image << "\n";
}