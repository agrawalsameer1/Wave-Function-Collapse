#pragma once
#include <vector>
#include <random>
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
		int id;
		int N;
	};

	// The Wave structure defines the "domain" of each Element. It hosts a lists of all possible Patterns in a boolean array.
	// The Wave also contains information about its Shannon entropy: essentially, the number of possible patterns.
	struct Wave
	{
		vector<Pattern> possiblePatterns;
		int entropy;
		bool propagated;
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
	void ruleGeneration(PPMImage img, int N);
	// Generate output image 
	void generateOutput(int N, int X, int Y);
	// Collapses a Wave to a single possible Pattern. Returns id of final collapsed element.
	int observe();
	// Returns if data has been propagated to every pattern in the output image
	bool checkPropagation();
	// Propagates the information from one cell to all other cells. Not recursive since we need to implement data strucures for credit. :(
	void propagate(int id);
	// Returns whether algorithm has completed
	bool completed();
	// Returns whether there is a contradiction: whether there are 0 possible patterns for an element in the output
	bool contradiction();
	// Collapse function, puts all functions together
	void collapse(PPMImage input, int N, int outputX, int outputY);
	// Create output PPM Image
	PPMImage buildOutput();


	/* *************FIELDS************* */

	// Defines the final pattern arrangement after the algorithm is done.
	vector<Wave> output;
	// Defines dimensions of output
	int outputX;
	int outputY;
	// An array of all patterns extracted from the source image.
	vector<Pattern> patterns;
	// A hash table of all adjacency rules extracted from source image.
	vector<HashTable> adjacencyRules;
};