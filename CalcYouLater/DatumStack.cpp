/*
 *  DatumStack.cpp
 *  Thomas Giglia
 *  2/9/2025
 *
 *
 *  COMP 15 Project 2 CalcYouLater
 * 
 *  PURPOSE: Implementation of the DatumStack class, which represents a 
 *  stack of datum objects. This class provides functionality to push onto and 
 *  pop off data as well as know some information about the stack itself.
 */

#include "DatumStack.h"
#include <iostream>
#include <stdexcept>
 
using namespace std;
 
/*  name:       DatumStack (default constructor)
 *  Purpose:    Construct an instance of a DatumStack.
 *  Parameters: None
 *  Return:     None
 */
DatumStack::DatumStack() {}
 
/*  name:       DatumStack (array constructor)
 *  Purpose:    Construct an instance of a DatumStack.
 *  Parameters: None
 *  Return:     None
 */
DatumStack::DatumStack(Datum datumArray[], int length) {
    for (int i = 0; i < length; i++) {
        data.push_back(datumArray[i]);
    }
}

/*  name:       Destructor
 *  Purpose:    Deallocate all allocated memory for DatumStack class.
 *  Parameters: None
 *  Return:     None
 */
DatumStack::~DatumStack() {}
 

/*
 * name:      isEmpty
 * purpose:   to state if a given DatumStack is empty or not
 * arguments: none
 * effects:   none
 * returns:   boolean representing if the stack is empty
 */
bool DatumStack::isEmpty() const {
    return data.size() == 0;
}


/*
 * name:      top
 * purpose:   to return the datum element at front of DatumStack
 * arguments: none
 * effects:   none
 * returns:   Datum object at top of stack
 */
Datum DatumStack::top() const {
    if (data.empty()) {
        throw runtime_error("Error: empty_stack");   
    }
    return data.back();
}

/*
 * name:      size
 * purpose:   to return the number of datum objects in the DatumStack
 * arguments: none
 * effects:   none
 * returns:   integer representing the size of the stack
 */
 int DatumStack::size() const {
    return data.size();
}


/*  pop()
 *  Purpose:    Remove the top element in the stack and return it.
 *  Parameters: None
 *  effects:    throws an error if the stack is empty
 *  returns:    the removed datum object.
 */
Datum DatumStack::pop() {
    if (data.empty()) {
        throw runtime_error("Error: empty_stack");   
    }
    Datum oldFront = data.back();
    data.pop_back();
    return oldFront;
}
 
/*  push()
 *  Purpose:    Add a new element to the top of the stack.
 *  Parameters: the datum to add.
 *  Effects:    Stack is now one element larger
 *  Return:     None
 */
void DatumStack::push(Datum d) {
    data.push_back(d);
}

/*  clear()
 *  Purpose:    Remove all elements from the stack.
 *  Parameters: none.
 *  Effects:    Stack is empty
 *  Returns:    None
 */
void DatumStack::clear() {
    data.clear();
}
