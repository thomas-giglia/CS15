/*
 *  PassengerQueue.h
 *  Thomas Giglia
 *  2/9/2025
 *
 *  COMP 15 Project 1 Metro Sim
 *
 *
 * PURPOSE GOES HERE
 *
 */  


#ifndef __PASSENGERQUEUE_H__
#define __PASSENGERQUEUE_H__


#include "Passenger.h"
#include <sstream>
#include <string>
#include <list>

class PassengerQueue {
public:
  PassengerQueue();
  ~PassengerQueue();

  int         size()    const; 
  Passenger   front()   const; 
  Passenger   dequeue();
  void        enqueue(Passenger p);

  void        print(std::ostream &output);
    
private:
  std::list<Passenger> queue;
};

#endif

