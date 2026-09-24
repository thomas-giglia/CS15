/*
 *  main.cpp
 *  Thomas Giglia
 *  2/9/2025
 *
 *  COMP 15 Project 2 CalcYouLater
 *
 *
 *  PURPOSE: To start instances of the RPNCalc class to be used as the 
 *  CalcYouLater. Thanks the user for using the program afterwards.
 */  

#include "RPNCalc.h"

using namespace std;

int main() {
    RPNCalc calc;
    calc.run();
    
    cerr << "Thank you for using CalcYouLater.\n";   
    return 0;
}
