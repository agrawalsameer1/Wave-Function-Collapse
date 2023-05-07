#include <iostream>
#include <algorithm>
#include <random>
#include "../include/WFC.h"
#include "../include/PPM.h"

// Hey, pal. Looks like you just collapsed your last wave function *pulls out a coconut gun*

void WFC::wfc()
{
    ;
}

// Generate adjacency rules from input img
void WFC::ruleGeneration(PPMImage img, int N) {
    // Extract all NxN tiles from input image
    for (int i = 0; i < img.y; i+=N) {
        for (int j = 0; j < img.x; j+=N) {
            Pattern* pattern = (Pattern*)(malloc(sizeof(Pattern)));
            pattern->id = (((i*img.x)/(N*N))+(j/N));
            std::cout << pattern->id << "\n";
            pattern->N = N;
            pattern->pixels = *(new PPMImage(N,N));
            for (int k = 0; k < N; k++) {
                for (int l = 0; l < N; l++) {
                    pattern->pixels.writePixel(l,k,img.pixelAt(j+l,i+k));
                    //std::cout << (i+k) << " " << (j+l) << "\n";
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
                    leftRules->insert(patterns[j-1]); 
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
void WFC::generateOutput(int N, int X, int Y) {
    outputX = X;
    outputY = Y;
    for (int j = 0; j < outputY/N; j+=N) {
        for (int k = 0; k < outputX/N; k+=N) {
            Wave* w = (Wave*)(malloc(sizeof(Wave)));
            std::copy(patterns.begin(), patterns.end(), std::back_inserter(w->possiblePatterns));
            w->propagated = false;
            output[(j*outputX+k)/N] = *w;
        }
    }
}

bool WFC::checkPropagation() {
    for (int i = 0; i < output.size(); i++) {
        if (output[i].propagated == false) {
            return false;
        }
    }
    return true;
}

// Propagate the data for an element with a specific id
int WFC::propagate(int id) {
    if (checkPropagation()) {
        return 0;
    }

    if (id > outputX) { // If we're on the second row or below, we can have a pattern above
        int i = 0;
        while (i < output[id-outputX].possiblePatterns.size()) {
            bool possible = false;
            for (int it = 0; it < output[id].possiblePatterns.size(); it++) {
                Pattern pat = output[id].possiblePatterns[it];
                LinkedList possibles = adjacencyRules[0].get(pat); // Get all possible above patterns for the pattern we just collapsed
                if (possibles.contains(output[id-outputX].possiblePatterns[i])) {
                    possible = true;
                }
            }
            if (!(possible)) {
                output[id-outputX].possiblePatterns.erase(output[id-outputX].possiblePatterns.begin() + i); // Delete all patterns that can't be above the one we just collapsed
            }
            else {
                i++;
            }
        }
        output[id-outputX].propagated = true;
        int newID = id-outputX;
        return propagate(newID);
    }

    if ((id%outputX) > 0) { // If we're at least one tile along a row, we can have a pattern to the left
        int i = 0;
        while (i < output[id-1].possiblePatterns.size()) {
            bool possible = false;
            for (int it = 0; it < output[id].possiblePatterns.size(); it++) {
                Pattern pat = output[id].possiblePatterns[it];
                LinkedList possibles = adjacencyRules[1].get(pat); // Get all possible patterns to the left of the pattern we just collapsed
                if (possibles.contains(output[id-1].possiblePatterns[i])) {
                    possible = true;
                }
            }
            if (!(possible)) {
                output[id-1].possiblePatterns.erase(output[id-1].possiblePatterns.begin() + i); // Delete all patterns that can't be to the left of the one we just collapsed
            }
            else {
                i++;
            }
        }
        output[id-1].propagated = true;
        int newID = id-1;
        return propagate(newID);
    }

    if (id%(outputX-1) > 0) { // If we're at least one tile before the end of a row, we can have a pattern to the right
        int i = 0;
        while (i < output[id+1].possiblePatterns.size()) {
            bool possible = false;
            for (int it = 0; it < output[id].possiblePatterns.size(); it++) {
            Pattern pat = output[id].possiblePatterns[it];
                LinkedList possibles = adjacencyRules[2].get(pat); // Get all possible patterns to the right of the pattern we just collapsed
                if (possibles.contains(output[id+1].possiblePatterns[i])) {
                    possible = true;
                }
            }
            if (!(possible)) {
                output[id+1].possiblePatterns.erase(output[id+1].possiblePatterns.begin() + i); // Delete all patterns that can't be to the right of the one we just collapsed
            }
            else {
                i++;
            }
        }
        output[id+1].propagated = true;
        int newID = id+1;
        return propagate(newID);
    }

    if (id < output.size()-outputX) { // If we're at least one row before the end, we can have a pattern below
        int i = 0;
        while (i < output[id+outputX].possiblePatterns.size()) {
            bool possible = false;
            for (int it = 0; it < output[id].possiblePatterns.size(); it++) {
                Pattern pat = output[id].possiblePatterns[it];
                LinkedList possibles = adjacencyRules[3].get(pat); // Get all possible below patterns for the pattern we just collapsed
                if (possibles.contains(output[id+outputX].possiblePatterns[i])) {
                    possible = true;
                }
            }
            if (!(possible)) {
                output[id+outputX].possiblePatterns.erase(output[id+outputX].possiblePatterns.begin() + i); // Delete all patterns that can't be below the one we just collapsed
            }
            else {
                i++;
            }
        }
        output[id+outputX].propagated = true;
        int newID = id+outputX;
        return propagate(newID);
    }
}

int WFC::observe()
{
    std::random_device rd; 
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, output.size());
    int choice2 = distr(gen);
    int smallestLength = output[choice2].possiblePatterns.size();
    int smallestId = choice2;

    for (int i = 0; i < output.size(); i++) {
        if (output[i].possiblePatterns.size() < smallestLength && output[i].possiblePatterns.size() > 1) {
            smallestId = i;
            smallestLength = output[i].possiblePatterns.size();
        }
    }

    std::random_device rd2; 
    std::mt19937 gen2(rd2());
    std::uniform_int_distribution<> distr2(0, output[smallestId].possiblePatterns.size());
    int choice = distr2(gen2);

    vector<Pattern> newOutput;
    newOutput.push_back(output[smallestId].possiblePatterns[choice]);

    std::copy(newOutput.begin(), newOutput.end(), std::back_inserter(output[smallestId].possiblePatterns));
    output[smallestId].propagated = true;
    return smallestId;
}

bool WFC::completed() {
    for (int i = 0; i < output.size(); i++) {
        if (output[i].possiblePatterns.size() > 1) { // If an element has more than one possible pattern
            return false;
        }
    }
    return true;
}

bool WFC::contradiction() {
    for (int i = 0; i < output.size(); i++) {
        if (output[i].possiblePatterns.size() == 0) { // If an element has no possible patterns
            return true;
        }
    }
    return false;
}

PPMImage WFC::collapse(PPMImage input, int N, int outputX, int outputY) {
    bool contradicts = true;
    bool complete = false;
    ruleGeneration(input, N);
    std::cout << "Reached here!\n";

    while (contradicts) {            
        generateOutput(N, outputX, outputY); // If there is a contradiction, reset the output
        while (!(complete)) {
            int collapsedId = observe();
            propagate(collapsedId);
            contradicts = contradiction();
            if (contradicts) {
                break;
            }
            complete = completed();
        }
    }
    PPMImage returned = buildOutput();
    return returned;
}

PPMImage WFC::buildOutput() {
    PPMImage out = PPMImage(outputX, outputY);
    int NValue = output[0].possiblePatterns[0].N;

    for (int i = 0; i < outputY/NValue; i++) {
        for (int l = 0; l < outputX/NValue; l++) {
            for (int j = 0; j < NValue; j++) {
                for (int k = 0; k < NValue; k++) {
                    out.writePixel(NValue*l+k, NValue*i+j, output[i*outputX+l].possiblePatterns[0].pixels.pixelAt(k,j));
                }
            }
        }
    }

    return out;
}