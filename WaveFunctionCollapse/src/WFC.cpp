#include <iostream>
#include <algorithm>
#include <random>
#include "../include/WFC.h"
#include "../include/PPM.h"

// Hey, pal. Looks like you just collapsed your last wave function *pulls out a coconut gun*

void WFC::wfc()
{
	// Define grid position
	int x = 0, y = 0;

	// Start with the first Element in the output
	observe(output[y][x].wave);

}

// Generate adjacency rules from input img
void WFC::ruleGeneration(PPMImage img, int N) {

    // Extract all NxN tiles from input image
    for (int i = 0; i < img.y-N; i++) {
        for (int j = 0; j < img.x-N; j++) {
            Pattern* pattern = new Pattern();
            pattern->id = (i*img.x+j);
            pattern->N = N;
            for (int k = 0; k < N; k++) {
                for (int l = 0; l < N; l++) {
                    pattern->pixels.writePixel(l,k,img.pixelAt(j+l,i+k));
                }
            }
            patterns.push_back(*pattern);
        }
    }

    // Find number of unique patterns
    int cnt = 0;
    bool found = false;
    for (int i = 0; i < patterns.size(); i++) {
        found = false;
        for (int j = 0; j < i; j++) {
            if (patterns[j].pixels == patterns[i].pixels) {
                found = true;
            }
        }
        if (!(found)) {
            cnt++;
        }
    }
    
    // Define hash table for top, left, right, and bottom patterns
    HashTable* topRules = new HashTable(cnt);
    HashTable* leftRules = new HashTable(cnt);
    HashTable* rightRules = new HashTable(cnt);
    HashTable* bottomRules = new HashTable(cnt);

    // Insert each unique pattern in input image as a key into each hash table
    for (int i = 0; i < patterns.size(); i++) {
        if (!(topRules->contains(patterns[i]))) {
            topRules->insert(patterns[i]);
        }
        if (!(leftRules->contains(patterns[i]))) {
            leftRules->insert(patterns[i]);
        }
        if (!(rightRules->contains(patterns[i]))) {
            rightRules->insert(patterns[i]);
        }
        if (!(bottomRules->contains(patterns[i]))) {
            bottomRules->insert(patterns[i]);
        }
    }

    // Add adjacent patterns
    for (int i = 0; i < topRules->getLength(); i++) {
        for (int j = 0; j < patterns.size(); j++) {
            if (patterns[j].pixels == topRules->get(i).head->pat.pixels) {
                if (j > img.x) { // If we're on the second row or below, we can have a pattern above
                    topRules->insert(patterns[j-img.x]);
                }
                if ((j%img.x) > 0) { // If we're at least one tile along a row, we can have a pattern to the left
                    leftRules->insert(patterns[j+1]); 
                }
                if ((j%(img.x-1)) > 0) { // If we're at least one tile before the end of a row, we can have a pattern to the right
                    rightRules->insert(patterns[j+1]); 
                }
                if (j < (patterns.size()-img.x)) { // If we're at least one row before the end, we can have a pattern below
                    bottomRules->insert(patterns[j+img.x]);
                }
            }
        }
    }

    adjacencyRules.push_back(*topRules);
    adjacencyRules.push_back(*leftRules);
    adjacencyRules.push_back(*rightRules);
    adjacencyRules.push_back(*bottomRules);
}

// Generate output image
void WFC::generateOutput(int N) {
    for (int j = 0; j < outputY-N+1; j++) {
        for (int k = 0; k < outputX-N+1; k++) {
            output.push_back(patterns);
        }
    }
}

// Propagate the data after collapsing the element with a specific id
void WFC::propagate(int id) {
    WFC::Pattern pat = output[id][0];

    if (id > outputX) { // If we're on the second row or below, we can have a pattern above
        int i = 0;
        LinkedList possibles = adjacencyRules[0].get(pat); // Get all possible above patterns for the pattern we just collapsed
        while (i < output[id-outputX].size()) {
            if (possibles.contains(output[id-outputX][i]) == false) {
                output[id-outputX].erase(output[id-outputX].begin() + i); // Delete all patterns that can't be above the one we just collapsed
            }
            else {
                i++;
            }
        }
        
        i = 0;
        while (i < output[id-outputX].size()) {
            possibles = adjacencyRules[3].get(output[id-outputX][i]);
            if (possibles.contains(pat) == false) {
                output[id-outputX].erase(output[id-outputX].begin() + i); // Delete all patterns which can't have the one we just collapsed below them
            }
            else {
                i++;
            }
        }
    }
    if ((id%outputX) > 0) { // If we're at least one tile along a row, we can have a pattern to the left
        int i = 0;
        LinkedList possibles = adjacencyRules[1].get(pat);
        while (i < output[id-1].size()) {
            if (possibles.contains(output[id-1][i]) == false) {
                output[id-1].erase(output[id-1].begin() + i); // Delete all patterns that can't be to the left of the one we just collapsed
            }
            else {
                i++;
            }
        }

        i = 0;
        while (i < output[id-1].size()) {
            possibles = adjacencyRules[2].get(output[id-1][i]);
            if (possibles.contains(pat) == false) {
                output[id-1].erase(output[id-1].begin() + i); // Delete all patterns which can't have the one we just collapsed to the right of them
            }
            else {
                i++;
            }
        }
    }
    if ((id%(outputX-1)) > 0) { // If we're at least one tile before the end of a row, we can have a pattern to the right
        int i = 0;
        LinkedList possibles = adjacencyRules[2].get(pat);
        while (i < output[id+1].size()) {
            if (possibles.contains(output[id+1][i]) == false) {
                output[id+1].erase(output[id+1].begin() + i);  // Delete all patterns that can't be to the right of the one we just collapsed
            }
            else {
                i++;
            }
        }

        i = 0;
        while (i < output[id+1].size()) {
            possibles = adjacencyRules[1].get(output[id+1][i]);
            if (possibles.contains(pat) == false) {
                output[id+1].erase(output[id+1].begin() + i); // Delete all patterns which can't have the one we just collapsed to the left of them
            }
            else {
                i++;
            }
        }
    }
    if (id < (output.size()-outputX)) { // If we're at least one row before the end, we can have a pattern below
        int i = 0;
        LinkedList possibles = adjacencyRules[3].get(pat);
        while (i < output[id+outputX].size()) {
            if (possibles.contains(output[id+outputX][i]) == false) {
                output[id+outputX].erase(output[id+outputX].begin() + i); // Delete all patterns that can't be below the one we just collapsed
            }
            else {
                i++;
            }
        }

        i = 0;
        while (i < output[id+outputX].size()) {
            possibles = adjacencyRules[0].get(output[id+outputX][i]);
            if (possibles.contains(pat) == false) {
                output[id+outputX].erase(output[id+outputX].begin() + i); // Delete all patterns which can't have the one we just collapsed above them
            }
            else {
                i++;
            }
        }
    }
}

void WFC::observe()
{
    std::random_device rd; 
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, output.size());
    int choice2 = distr(gen);
    int smallestLength = output[choice2].size();
    int smallestId = choice2;

    for (int i = 0; i < output.size(); i++) {
        if (output[i].size() < smallestLength && output[i].size() > 1) {
            smallestId = i;
            smallestLength = output[i].size();
        }
    }

    std::random_device rd; 
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, output[smallestId].size());
    int choice = distr(gen);

    vector<Pattern> newOutput;
    newOutput.push_back(output[smallestId][choice]);

    output[smallestId] = newOutput;
}

int main() {
    PPMImage *image = new PPMImage();
    image->readPPM("/Users/sameeragrawal/Desktop/hello.ppm");

    std::cout << image->y << " x " << image->x << "\n";

    std::cout << *image << "\n";
}