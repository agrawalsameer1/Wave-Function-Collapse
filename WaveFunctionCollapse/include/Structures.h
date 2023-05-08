#pragma once

#include <iostream>
#include <string>
#include "PPM.h"
#include <vector>

/* *************STRUCTURES************* */

	// The Pattern structure defines an arrangement of pixels, as well as their "weight" in the original image.
	// Weight is defined by the number of times it appears in the image.
	// N is the dimension of the NxN pattern (ex. 3x3, 5x5, etc)
struct Pattern
{
    PPMImage pixels;
    int id = 0;
    int N = 0;
};

// The Wave structure defines the "domain" of each Element. It hosts a lists of all possible Patterns in a boolean array.
// The Wave also contains information about its Shannon entropy: essentially, the number of possible patterns.
struct Wave
{
    std::vector<Pattern> possiblePatterns;
    int entropy;
    bool propagated;
};

// The Element structure defines an NxN region in the new output image.
// It also contains an array of all its adjacent neighbors.
struct Element
{
    Wave* wave;
    std::vector<Element> neighbors[4]; // each Element can have a maximum of 4 adjacent neighbors, obviously
};