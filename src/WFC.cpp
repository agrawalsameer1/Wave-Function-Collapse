#include <iostream>
#include <algorithm>
#include <random>
#include "../include/WFC.h"
#include "../include/PPM.h"
#include "../include/Queue.h"

// Hey, pal. Looks like you just collapsed your last wave function *pulls out a coconut gun*

// Generate adjacency rules from input img
void WFC::ruleGeneration(PPMImage* img, int N) {
    std::cout << "what's good" << std::endl;
    // Extract all NxN tiles from input image
    for (int i = 0; i < img->y; i+=N) {
        for (int j = 0; j < img->x; j+=N) {
            Pattern* pattern = (Pattern*)(malloc(sizeof(Pattern)));
            //Pattern* pattern = new Pattern;
            pattern->id = (((i*img->x)/(N*N))+(j/N)); // i have no clue what this means but we give every Pattern an id i guess??
            std::cout << pattern->id << std::endl;
            // write NxN section of image to the Pattern
            pattern->N = N;
            PPMImage pixs = *(new PPMImage(N,N));
            for (int k = 0; k < N; k++) {
                for (int l = 0; l < N; l++) {
                    PPMPixel pixie = img->pixelAt(j+l,i+k);
                    pixs.writePixel(l,k,&(pixie));
                }
            }
            std::cout << "we win these\n";
            pattern->pixels = pixs;
            std::cout << pattern->pixels << "\n";
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
            std::cout << patterns[i].pixels << "\n";
            cnt++;
        }
    }
    std::cout << cnt << "\n";
    
    // Define hash table for top, left, right, and bottom patterns
    HashTable* topRules = new HashTable(cnt);
    HashTable* leftRules = new HashTable(cnt);
    HashTable* rightRules = new HashTable(cnt);
    HashTable* bottomRules = new HashTable(cnt);

    std::cout << "reached here!\n";

    // Insert each unique pattern in input image as a key into each hash table
    cnt = 0;
    for (int i = 0; i < patterns.size(); i++) {
        if (!(topRules->contains(&patterns[i]))) {
            std::cout << "topinsert\n";
            topRules->insert(cnt, &patterns[i]);
            std::cout << "leftinsert\n";
            leftRules->insert(cnt, &patterns[i]);
            std::cout << "rightinsert\n";
            rightRules->insert(cnt, &patterns[i]);
            std::cout << "bottominsert\n";
            bottomRules->insert(cnt, &patterns[i]);
            cnt++;
        }
        std::cout << topRules->getNumberOfElements() << "\n";
        std::cout << leftRules->getNumberOfElements() << "\n";
        std::cout << rightRules->getNumberOfElements() << "\n";
        std::cout << bottomRules->getNumberOfElements() << "\n";
    }
    
    // Add adjacent patterns
    for (int i = 0; i < cnt; i++) {
        PPMImage patty = topRules->get(i)->head->pat.pixels;
        std::cout << "new head reached!\n" << patty << "\n";
        for (int j = 0; j < patterns.size(); j++) {
            
            if (patterns[j].pixels == patty) {
                std::cout << i << " " << j << "\n";
                if (j >= img->x/N) { // If we're on the second row or below, we can have a pattern above
                    //std::cout << "topinsert\n";
                    topRules->insert(i, &patterns[j-img->x/N]);
                    //std::cout << "inserting:\n" << patterns[j-img->x/N].pixels << "\n";
                }
                if ((j%(img->x/N)) > 0) { // If we're at least one tile along a row, we can have a pattern to the left
                    //std::cout << "leftinsert\n";
                    leftRules->insert(i, &patterns[j-1]); 
                    //std::cout << "inserting:\n" << patterns[j-1].pixels << "\n";
                }
                if ((j%(img->x/N)) < ((img->x/N)-1)) { // If we're at least one tile before the end of a row, we can have a pattern to the right
                    //std::cout << "rightinsert\n";
                    rightRules->insert(i, &patterns[j+1]); 
                    //std::cout << "inserting:\n" << patterns[j+1].pixels << "\n";
                }
                if ((j) < (patterns.size()-(img->x/N))) { // If we're at least one row before the end, we can have a pattern below
                    //std::cout << "bottominsert\n";
                    bottomRules->insert(i, &patterns[j+img->x/N]);
                    //std::cout << "inserting:\n" << patterns[j+img->x/N].pixels << "\n";
                }
                //std::cout << topRules->get(0).length << "\n";
            }
        }
        
    }

    adjacencyRules.push_back(*topRules);
    adjacencyRules.push_back(*leftRules);
    adjacencyRules.push_back(*rightRules);
    adjacencyRules.push_back(*bottomRules);

    for (auto i : adjacencyRules)
    {
        for (int j = 0; j < i.getNumberOfElements(); j++)
        {
            node* traverser = i.get(j)->head;
            for (int k = 0; k < i.get(j)->getLength(); k++)
            {
                std::cout << traverser << '\n';
                traverser = traverser->next;
            }
        }
    }
}

// Generate output image
void WFC::generateOutput(int N, int X, int Y) {
    outputX = X;
    outputY = Y;
    output.clear();
    for (int j = 0; j < outputY/N; j++) {
        for (int k = 0; k < outputX/N; k++) {
            std::cout << "i love men " << j*(outputX/N)+k << "\n";
            Wave* w = new Wave;
            std::cout << w << '\n';
            for (int i = 0; i < adjacencyRules[0].getNumberOfElements(); i++) {
                w->possiblePatterns.push_back(adjacencyRules[0].get(i)->head->pat);
            }
            output.push_back(*w);
        }
    }
    //exit(1);
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
    /*Queue<Wave> queue;
    queue.push(output[id]);
    while (queue.size() > 0)
    {
        Wave wave
    }*/

    int NValue = output[0].possiblePatterns[0].N;
    int outputx = outputX/NValue;
    if (id >= outputx) { // If we're on the second row or below, we can have a pattern above
        if (output[id-outputx].propagated == false) {
            std::cout << "Entropy of non-propagated top: " << calcEntropy(id-outputx) << "\n";
            int i = 0;
            while (i < output[id - outputx].possiblePatterns.size()) {
                bool possible = false;
                for (int it = 0; it < output[id].possiblePatterns.size(); it++) {
                    Pattern pat = output[id].possiblePatterns[it];
                    LinkedList* possibles = adjacencyRules[0].get(&pat); // Get all possible above patterns for the pattern we just collapsed
                    if (possibles->contains(output[id - outputx].possiblePatterns[i])) {
                        possible = true;
                    }
                }
                if (!(possible)) {
                    output[id - outputx].possiblePatterns.erase(output[id - outputx].possiblePatterns.begin() + i); // Delete all patterns that can't be above the one we just collapsed
                }
                else {
                    i++;
                }
            }
            std::cout << "Entropy of propagated top: " << calcEntropy(id-outputx) << "\n";
            output[id - outputx].propagated = true;
        }
        int newID = id - outputX;
        return propagate(newID);
    }

    if ((id % outputx) > 0) { // If we're at least one tile along a row, we can have a pattern to the left
        if (output[id-1].propagated == false) {
            int i = 0;
            std::cout << "Entropy of non-propagated left: " << calcEntropy(id-1) << "\n";
            while (i < output[id-1].possiblePatterns.size()) {
                bool possible = false;
                for (int it = 0; it < output[id].possiblePatterns.size(); it++) {
                    Pattern pat = output[id].possiblePatterns[it];
                    LinkedList* possibles = adjacencyRules[1].get(&pat); // Get all possible patterns to the left of the pattern we just collapsed
                    if (possibles->contains(output[id - 1].possiblePatterns[i])) {
                        possible = true;
                    }
                }
                if (!(possible)) {
                    output[id - 1].possiblePatterns.erase(output[id-1].possiblePatterns.begin() + i); // Delete all patterns that can't be to the left of the one we just collapsed
                }
                else {
                    i++;
                }
            }
            output[id - 1].propagated = true;
            std::cout << "Entropy of propagated left: " << calcEntropy(id-1) << "\n";
        }
        int newID = id - 1;
        return propagate(newID);
    }

    if (id % (outputx - 1) > 0) { // If we're at least one tile before the end of a row, we can have a pattern to the right
        if (output[id+1].propagated == false) {
            int i = 0;
            std::cout << "Entropy of non-propagated right: " << calcEntropy(id+1) << "\n";
            while (i < output[id + 1].possiblePatterns.size()) {
                bool possible = false;
                for (int it = 0; it < output[id].possiblePatterns.size(); it++) {
                Pattern pat = output[id].possiblePatterns[it];
                    LinkedList* possibles = adjacencyRules[2].get(&pat); // Get all possible patterns to the right of the pattern we just collapsed
                    if (possibles->contains(output[id + 1].possiblePatterns[i])) {
                        possible = true;
                    }
                }
                if (!(possible)) {
                    output[id+1].possiblePatterns.erase(output[id + 1].possiblePatterns.begin() + i); // Delete all patterns that can't be to the right of the one we just collapsed
                }
                else {
                    i++;
                }
            }
            std::cout << "Entropy of propagated right: " << calcEntropy(id+1) << "\n";
            output[id+1].propagated = true;
        }
        int newID = id+1;
        return propagate(newID);
    }

    if (id < (output.size()-outputx)) { // If we're at least one row before the end, we can have a pattern below
        if (output[id+outputx].propagated == false) {
            int i = 0;
            std::cout << "Entropy of non-propagated bottom: " << calcEntropy(id+outputx) << "\n";
            while (i < output[id + outputx].possiblePatterns.size()) {
                bool possible = false;
                for (int it = 0; it < output[id].possiblePatterns.size(); it++) {
                    Pattern pat = output[id].possiblePatterns[it];
                    LinkedList* possibles = adjacencyRules[3].get(&pat); // Get all possible below patterns for the pattern we just collapsed
                    if (possibles->contains(output[id + outputx].possiblePatterns[i])) {
                        possible = true;
                    }
                }
                if (!(possible)) {
                    output[id + outputx].possiblePatterns.erase(output[id + outputx].possiblePatterns.begin() + i); // Delete all patterns that can't be below the one we just collapsed
                }
                else {
                    i++;
                }
            }
            output[id+outputx].propagated = true;
            std::cout << "Entropy of propagated bottom: " << calcEntropy(id+outputx) << "\n";
        }
        int newID = id+outputx;
        return propagate(newID);
    }
}

int WFC::observe()
{
    std::cout << "in obserev!\n";
    // Using GOOD RANDOM NUMBER GENERATION (std::rand() is BAD)
    std::random_device rd; 
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, output.size());
    int choice2 = distr(gen);
    int smallestLength = output[choice2].possiblePatterns.size();
    int smallestId = choice2;

    // Search for the Wave with the lowest entropy (if there are multiple, pick the first one in the vector of Waves) defined by the number of possible Patterns it can be
    for (int i = 0; i < output.size(); i++) {
        if (output[i].possiblePatterns.size() < smallestLength && output[i].possiblePatterns.size() > 1) {
            smallestId = i;
            smallestLength = output[i].possiblePatterns.size();
        }
    }
    std::cout << "done with obserev2!\n";

    // Pick a random Pattern index
    std::random_device rd2; 
    std::mt19937 gen2(rd2());
    std::cout << output[smallestId].possiblePatterns.size() << "\n";
    std::uniform_int_distribution<> distr2(0, output[smallestId].possiblePatterns.size());
    int choice = distr2(gen2);

    // Effectively remove all Patterns other than the selected Pattern
    vector<Pattern> newOutput;
    newOutput.push_back(output[smallestId].possiblePatterns[choice]);
    output[smallestId].possiblePatterns.resize(1);
    output[smallestId].possiblePatterns[0] = newOutput[0];
    std::cout << "done with obserev3!\n";
    //std::copy(newOutput.begin(), newOutput.end(), std::back_inserter(output[smallestId].possiblePatterns));
    output[smallestId].propagated = true;
    std::cout << "done with obserev!\n";
    return smallestId; // return Wave index that was collapsed
}

int WFC::calcEntropy(int id) {
    std::vector<PPMImage> found;
    int ent = 0;
    Pattern patty = output[id].possiblePatterns[0];
    for (int j = 0; j < output[id].possiblePatterns.size(); j++) {
        if (std::find(found.begin(), found.end(), output[id].possiblePatterns[j].pixels) == found.end()) {
            ent++;
            found.push_back(output[id].possiblePatterns[j].pixels);
        }
    }
    return ent;
}

int WFC::maxEntropy() {
    int maxEntropy = calcEntropy(0);
    for (int j = 1; j < output.size(); j++) {
        if (calcEntropy(j) > maxEntropy) {
            maxEntropy = calcEntropy(j);
        }
    }
    return maxEntropy;
}

bool WFC::completed() {
    for (int i = 0; i < output.size(); i++) {
        if (calcEntropy(i) > 1) {
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

PPMImage WFC::collapse(PPMImage* input, int N, int outputX, int outputY) {
    bool contradicts = true;
    bool complete = false;
    ruleGeneration(input, N); // create the adjacency rules
    std::cout << "Reached here!\n";

    while (contradicts) {            
        // Set up the image
        // Alternatively, if there is a contradiction, this works to reset the output and try again
        generateOutput(N, outputX, outputY);
        std::cout << "generating!\n";
        //exit(1);
        while (!(complete)) {
            // collapse Wave with the least entropy
            int collapsedId = observe();
            std::cout << "Entropy of collapsed: " << calcEntropy(collapsedId) << "\n";
            // propogate information from the collapsed Wave to the rest of the Waves
            propagate(collapsedId);
            std::cout << "Reached here2!\n";
            std::cout << maxEntropy() << "\n";
            contradicts = contradiction(); // Check for contradictions (if one or more Waves are impossible to collapse)
            if (contradicts) {
                std::cout << "bad\n";
                break; // start over...

            }
            complete = completed(); // check if everything is collapsed
            std::cout << complete << "\n";
        }
    }
    // Create .ppm image and return
    std::cout << "reached here3?\n";
    PPMImage returned = buildOutput();
    return returned;
}

PPMImage WFC::buildOutput() {
    PPMImage out = PPMImage(outputX, outputY); // create blank image
    int NValue = output[0].possiblePatterns[0].N;

    // Write to the image in NxN sections
    for (int i = 0; i < outputY/NValue; i++) {
        for (int l = 0; l < outputX/NValue; l++) {
            for (int j = 0; j < NValue; j++) {
                for (int k = 0; k < NValue; k++) {
                    PPMPixel pixies = output[i*outputX+l].possiblePatterns[0].pixels.pixelAt(k,j);
                    out.writePixel(NValue*l+k, NValue*i+j, &(pixies));
                }
            }
        }
    }

    return out;
}