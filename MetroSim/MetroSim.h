/*
 *  Passenger.h
 *  Thomas Giglia
 *  2/9/2025
 *
 *  COMP 15 Project 1 Metro Sim
 *
 *
 * PURPOSE GOES HERE
 *
 */  

#ifndef _METROSIM_H_
#define _METROSIM_H_

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include "PassengerQueue.h"



class MetroSim {

public:
    MetroSim();
    MetroSim(std::string inputFile);
    void run(std::string outputFile, std::string cmdFile);
    void addPassenger(std::string input);
    void printState();
    void allAboard(std::ostream &output);
    void mindTheGap(std::ostream &output);
    void checkInput(std::string file_name);
    void checkOutput(std::string file_name);
    void commandLoop(std::string input, std::ostream &output);

private:
    struct QueueData {
        std::string name;
        int id;
        PassengerQueue queue; 
    };
    
    std::vector<QueueData> train;
    std::vector<QueueData> stations;
    int idCount = 1;
    int currStation = 0;
};

#endif
