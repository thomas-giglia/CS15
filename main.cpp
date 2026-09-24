/*
 *  phaseOne.cpp
 *  Thomas Giglia
 *  4/1/2025
 *
 *
 *  COMP 15 Project 3 Zap!
 * 
 *  PURPOSE: To start instances of the HuffmanCoder class to be used to zap and
 *  unzap files into encoded and decoded versions respectively. Outputs an
 *  error if executable is not formatted correctly.
 */

#include "HuffmanCoder.h"
#include "ZapUtil.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

    
int main(int argc, char *argv[]) {
    if (argc != 4) {
        cerr << "Usage: ./zap [zap | unzap] inputFile outputFile\n";
        exit(EXIT_FAILURE);
    } else {
        HuffmanCoder instance;
        
        string argv1 = argv[1];
        string input1 = argv[2];
        string output1 = argv[3];
        
        if (argv1 == "zap") {
            instance.encoder(input1, output1);
        } else if (argv1 == "unzap"){
             instance.decoder(input1, output1);
        } else {
            cerr << "Usage: ./zap [zap | unzap] inputFile outputFile\n";
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}