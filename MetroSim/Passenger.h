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

#ifndef __PASSENGER_H__
#define __PASSENGER_H__

#include <iostream>


class Passenger {
   public:
    Passenger(int id, int startingStation, int endingStation);
    int getId() const;
    int getStartingStation() const;
    int getEndingStation() const;
    void print(std::ostream &output);

   private:
    int id;
    int startingStation;
    int endingStation;
};

#endif

