/*
 *  RPNCalc.cpp
 *  Thomas Giglia
 *  2/27/2025
 *
 *
 *  COMP 15 Project 2 CalcYouLater
 * 
 * 
 *  PURPOSE: Acts as the interface for the RPNCalc program and the users inputs 
 *  meant for use by an outside user with little to no programming knowledge. 
 */

#ifndef __RPNCALC_H 
#define __RPNCALC_H
 
 
#include <string>
#include <iostream>
#include "DatumStack.h"
 
class RPNCalc {
public:
    RPNCalc();
    void run();
private:
    bool got_int(std::string s, int *resultp);
    void push(std::string input);
    void stackNot();
    void print() const;
    void clear();
    void drop();
    void dup();
    void swap();
    void quit();
    void doMath(std::string op);
    void relate(std::string op);
    void equate();
    void stackChange(std::string cmd);
    void convertBool(std::string boolean);
    std::string parse(std::istream &input);
    void exec();
    void file();
    void stackIf();
    std::string read(std::string rstring);
    void findCommand(std::string input);
    void pushPrep(std::istream &fileStream);
    
    std::list<std::istream*> inputStack; 
    DatumStack stack;
    bool cont;
}; 

#endif 
 