/*
 *  main.cpp
 *  Thomas Giglia
 *  2/9/2025
 *
 *  COMP 15 Project 1 Metro Sim
 *
 *
 * PURPOSE GOES HERE
 *
 */  


#include <iostream>
#include <fstream>
#include <string>

#include "MetroSim.h"


using namespace std;

int main(int argc, char *argv[]) {
    //Necessary functions not yet implemented
    if (argc < 3 or argc > 4) {
        cerr << "Usage: ./MetroSim stationsFile outputFile [commandsFile]\n";
        MetroSim instance(argv[1]);
        exit(EXIT_FAILURE);
    } else if (argc == 3) {
        MetroSim test;
        test.checkOutput(argv[2]); 
        MetroSim instance(argv[1]);    
        instance.run(argv[2], "cin");
    } else if (argc == 4) {
        MetroSim test;
        test.checkOutput(argv[2]); 
        MetroSim instance(argv[1]);    
        instance.run(argv[2], argv[3]);
    }

    return 0;
}
