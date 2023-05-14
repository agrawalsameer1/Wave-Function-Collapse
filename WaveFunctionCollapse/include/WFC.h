#pragma once
#include <vector>
#include <random>
#include "PPM.h"
#include "HashTable.h"
#include "Structures.h"
#include "Queue.h"

using namespace std;

class WFC
{
public:
	/* *************FUNCTIONS************* */

	// Generate adjacency rules from an input image
	void ruleGeneration(PPMImage* img, int N);
	// Generate output image 
	void generateOutput(int N, int X, int Y);
	// Collapses a Wave to a single possible Pattern. Returns id of final collapsed element.
	int observe();
	// Returns if data has been propagated to every pattern in the output image
	bool checkPropagation();
	// Propagates the information from one cell to all other cells. Not recursive since we need to implement data strucures for credit. :(
	int propagate(int id);
	// Counts number of unique possible patterns in a cell and returns
	int calcEntropy(int id);
	// Returns the maximum entropy of all cells in the output
	int maxEntropy();
	// Returns whether algorithm has completed
	bool completed();
	// Returns whether there is a contradiction: whether there are 0 possible patterns for an element in the output
	bool contradiction();

	void reset();
	// Collapse function, puts all functions together
	PPMImage collapse(PPMImage* input, int N, int outputX, int outputY);
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