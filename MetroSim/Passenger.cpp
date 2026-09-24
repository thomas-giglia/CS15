/*
 *  Passenger.cpp
 *  Thomas Giglia
 *  2/9/2025
 *
 *  COMP 15 Project 1 Metro Sim
 *
 *
 *  PURPOSE: Implementation of the Passenger class, which represents
 *  a passenger traveling between stations. It includes getter functions
 *  for passenger details and a print function for output representation.
 */  

#include "Passenger.h"
#include <iostream>
#include <string>

/*
 * name:      Passenger( )
 * purpose:   This is the constructor for Passenger that initializes
 *            a Passenger object with an ID, starting station, and 
 *            ending station.
 * arguments: An integer passenger ID, an integer starting station,
 *            and an integer ending station. 
 * returns:   none
 * effects:   Constructs a Passenger with the provided information.
 * note:      Students do not have to modify this function.
 */
Passenger::Passenger(int id, int startingStation, int endingStation) {
    this->id = id;
    this->startingStation = startingStation;
    this->endingStation = endingStation;
}

/*
 * name:      getId( )
 * purpose:   This is the getter (aka accessor) function that provides
 *            access to the Passenger's ID. 
 * arguments: none
 * returns:   The Passenger's ID. 
 * effects:   none
 * note:      Students do not have to modify this function.
 */
int Passenger::getId() const { return id; }

/*
 * name:      getStartingStation( )
 * purpose:   This is the getter (aka accessor) function that provides
 *            access to the Passenger's starting station. 
 * arguments: none
 * returns:   The Passenger's starting station. 
 * effects:   none
 * note:      Students do not have to modify this function.
 */
int Passenger::getStartingStation() const { return startingStation; }

/*
 * name:      getEndingStation( )
 * purpose:   This is the getter (aka accessor) function that provides
 *            access to the Passenger's ending station. 
 * arguments: none
 * returns:   The Passenger's ending station. 
 * effects:   none
 * note:      Students do not have to modify this function.
 */
int Passenger::getEndingStation() const { return endingStation; }

/*
 * name:      print()
 * purpose:   Outputs the Passenger’s details to the given output stream.
 * arguments: output - the output stream to print to.
 * returns:   none
 * effects:   Prints the passenger's ID, starting station, and ending station.
 */
 void Passenger::print(std::ostream &output) {
    output << "[" << id << ", " << startingStation << "->" << endingStation;
    output << "]";
}
