/*
 *  DatumStack.h
 *  Thomas Giglia
 *  2/18/2025
 *
 *  COMP 15 Project 2 CalcYouLater
 * 
 *  PURPOSE: Acts as the interface for DatumStack class of Datum variables
 *  meant for use by an outside user with little to know programming knowledge. 
 *  Specifically, creates an extensive interface for the user in the public 
 *  section and hides the background list.
 */


#ifndef __DATUMSTACK_H__
#define __DATUMSTACK_H__


#include "Datum.h"
#include <list>

class DatumStack {
public:
    DatumStack();
    DatumStack(Datum datumArray[], int length);
    ~DatumStack();

    bool    isEmpty() const;
    int     size()    const; 
    Datum   top()     const; 
    Datum   pop();
    void    push(Datum d);
    void    clear();
    
private:
  std::list<Datum> data;
};

#endif

