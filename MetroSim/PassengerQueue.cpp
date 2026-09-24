/*
 *  Passenger.cpp
 *  Thomas Giglia
 *  2/9/2025
 *
 *
 *  COMP 15 Project 1 Metro Sim
 * 
 *  PURPOSE: Implementation of the PassengerQueue class, which represents a 
 *  queue of passengers. This class provides functionality to enqueue and 
 *  dequeue passengers, as well as to return the queue's contents as a string.
 */

#include "Passenger.h"
 #include "PassengerQueue.h"
 
using namespace std;
 
 /*  Default constructor
  *  Purpose:    Construct an instance of a Queue.
  *  Parameters: None
  *  Return:     None
  */
PassengerQueue::PassengerQueue() {}
 
 /*  Destructor
  *  Purpose:    Deallocate all allocated memory for Queue class.
  *  Parameters: None
  *  Return:     None
  */
PassengerQueue::~PassengerQueue() {}
 
/*
 * name:      front
 * purpose:   to return the passenger element at front of Passenger Queue
 * arguments: none
 * effects:   none
 * returns:   passenger object at front of queue
 */
Passenger PassengerQueue::front() const {
    return queue.front();
}

/*
 * name:      size
 * purpose:   to return the number of passengers in the Passenger Queue
 * arguments: none
 * effects:   none
 * returns:   integer representing the size of the queue
 */
 int PassengerQueue::size() const {
    return queue.size();
}


 /*  dequeue()
  *  Purpose:    Remove the first element in the queue and return it.
  *  Parameters: None
  *  Return:     the removed passenger object.
  *  Notes:      Assumes queue is not empty.
  */
Passenger PassengerQueue::dequeue() {
     if (queue.empty()) {
         throw runtime_error("Queue is empty. Cannot dequeue.");
     }
     Passenger oldFront = queue.front();
     queue.pop_front();
     return oldFront;
}
 
 /*  enqueue()
  *  Purpose:    Add a new element to the back of the queue.
  *  Parameters: the passenger to add.
  *  Return:     None
  */
void PassengerQueue::enqueue(Passenger p) {
     queue.push_back(p);
}
 
 /*  print()
  *  Purpose:    Return the contents of the queue as a string.
  *  Parameters: None
  *  Return:     string representation of the queue.
  */
void PassengerQueue::print(std::ostream &output) {
     for (auto i = queue.begin(); i != queue.end(); ++i) {
        output << "[" << i->getId() << ", " << i->getStartingStation() << "->";
        output << i->getEndingStation() << "]";
     }
}
 