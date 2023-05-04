#pragma once
#include <vector>
#include "PPM.h"
#include "HashTable.h"

using namespace std;

class WFC
{
public:
	/* *************STRUCTURES************* */

	// The Pattern structure defines an arrangement of pixels, as well as their "weight" in the original image.
	// Weight is defined by the number of times it appears in the image.
	// N is the dimension of the NxN pattern (ex. 3x3, 5x5, etc)
	struct Pattern
	{
		PPMImage pixels;
		int weight;
		int N;
	};

	// The Wave structure defines the "domain" of each Element. It hosts a lists of all possible Patterns in a boolean array.
	// The Wave also contains information about its Shannon entropy: essentially, the number of possible patterns.
	struct Wave
	{
		vector<Pattern> domain;
		HashTable* rules;
		//bool possible[];
		int entropy;
	};

	// The Element structure defines an NxN region in the new output image.
	// It also contains an array of all its adjacent neighbors.
	struct Element
	{
		Wave* wave;
		vector<Element> neighbors[4]; // each Element can have a maximum of 4 adjacent neighbors, obviously
	};

	/* *************FUNCTIONS************* */

	// The "driver function". It starts the whole process.
	void wfc();
	// Generate adjacency rules from an input image
	HashTable* ruleGeneration(PPMImage img);
	// Collapses a Wave to a single possible Pattern.
	void observe(Wave* wave);
	// Propagates the information from one cell to all other cells. Not recursive since we need to implement data strucures for credit :(
	void propagate();
	// Returns a vector of all possible next cells.
	void findNextCell();


	/* *************FIELDS************* */

	// Defines the final pattern arrangement after the algorithm is done.
	vector<vector<Element>> output;
	// An array of all patterns extracted from the source image.
	vector<Pattern> patterns;
};