/*
 *  processing.cpp
 *  Thomas Giglia
 *  4/9/2025
 *
 *
 *  COMP 15 Project 4 Gerp
 * 
 * 
 *  PURPOSE: Implementation of the phaseOne functions, which help to remove all 
 *  non-alphanumeric characters from strings to make them 'words' and traverse
 *  directories to recursively output all files within it.
 */

#include <iostream>
#include "processing.h"
#include "DirNode.h"
#include "FSTree.h"

using namespace std;

string stripNonAlphaNum(string input) {
    string output = "";
    
    for (size_t i = 0; i < input.length(); i++) {
        if (input[i] >= '0' and input[i] <= '9') {         // numbers [0-9]
            output += input[i];
        } else if (input[i] >=  'A' and input[i] <= 'Z') { // letters [A-Z]
            output += input[i];
        } else if (input[i] >=  'a' and input[i] <= 'z') { // letters [a-z]
            output += input[i];
        } else if (input[i] == '-') {       // hyphens are also alphanumeric?
            output+= input[i];
        }
    }

    return output; 
}

void traverseDirectory(string directory) {
    FSTree rootDir(directory);
    DirNode* root = rootDir.getRoot();   
    for (int i = 0; i < root->numFiles(); i++) {
        cout << directory << "/" << root->getFile(i) << endl;    
    }
    for (int i = 0; i < root->numSubDirs(); i++) {
        
        traverseDirectory(directory + "/" + root->getSubDir(i)->getName());
    }
    return;
}