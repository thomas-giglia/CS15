/*
 *  Gerp.cpp
 *  Thomas Giglia
 *  2/27/2025
 *
 *
 *  COMP 15 Project 2 CalcYouLater
 * 
 * 
 *  PURPOSE: Implementation of the RPNCalc class, which holds a stack of datum
 *  objects. This class provides functionality to perform various arithmetic, 
 *  boolean, and organizaitonal commands on the data within the stack.
 */

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>

#include "processing.h"
#include "DirNode.h"
#include "FSTree.h"
#include "Gerp.h"

using namespace std;

/*
 * name:      RPNCalc
 * purpose:   Default constructor for RPNCalc
 * arguments: none
 * returns:   none
 * effects:   Initializes an empty RPNCalc instance.
 */
Gerp::Gerp() {
    
}

/*
 * Name:        run
 * Purpose:     Takes user inputs and performs proper operations on them using 
 *              the other functions
 * Parameters:  None
 * Returns:     None
 * Effects:     Manages stack operations
 */
// void Gerp::run(string& inputDirectory, string& outputFile) {
//     checkFile(inputFile);  
//     ifstream input(inputFile); 

//     string entry = "";
//     cout << "Query? ";
//     while (input >> entry) {
//         if (entry == "@q" or entry == "@quit") return;
//         cout << "Query? ";
//     }
// }