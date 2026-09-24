/*
 *  main.cpp
 *  Julian DuTemple, Thomas Giglia
 *  4/13/2025
 *
 *
 *  COMP 15 Project 4 Gerp
 * 
 *  PURPOSE: To start instances of the Gerp class to be used to find instances
 *  of words in a given directort and output them to a given file. Outputs an
 *  error if executable is not formatted correctly.
 */

#include "processing.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

    
int main(int argc, char *argv[]) {
    if (argc != 3) {
        cerr << "Usage: ./gerp inputDirectory outputFile\n";
        exit(EXIT_FAILURE);
    } else {
        // Gerp instance;
        string input1 = argv[1];
        string output1 = argv[2];
        traverseDirectory(input1);
    }

    return 0;
}