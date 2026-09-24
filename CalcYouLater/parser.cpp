/*
 *  parser.cpp
 *  Thomas Giglia
 *  2/18/2025
 *
 *
 *  COMP 15 Project 2 CalcYouLater
 * 
 *  PURPOSE: Implementation of the parser class, which only holds a single 
 *  main function, but a very important one, as it allows commands from various
 *  different streams to be read an entered into the RPNCalc in a way it
 *  can interpret. 
 */

#include <string>
#include <iostream>
#include "parser.h"

using namespace std;

/*  parseRString()
  *  Purpose:    To parse values for the program into rstrings to be 
                 interpreted.
  *  Parameters: the input that needs to be parsed into an rstring.
  *  Return:     None
  *  Effects:    None:
  */
string parseRString(istream &input) {    
    int nestLvl = 1; 
    string inputString, temp; 
    string rstring = "{ "; 
    while (not input.eof()) { 
        getline(input, inputString); 
        if (inputString.length() > 0 and inputString[0] != ' ') {
            temp += " ";
        }
        temp += inputString; 
    }

    int stringLength = temp.length();
    for (int i = 0; i < stringLength; i++) { 
        
        // protocols for getting characters but ignoring unnecessary whitespace
        if (temp[i] != '\n' and temp[i] != ' ') {
            rstring += temp[i];
        } else if ((temp[i] == ' ' && rstring[rstring.length()-1] != ' ')) {
            rstring += temp[i];
        }
        
        // protocols for if braces appear
        if (temp[i] == '{') {
            nestLvl++;
        } else if (temp[i] == '}') { // Stop parsing if '}' is found
            nestLvl--;
            if (nestLvl == 0)
            return rstring; 
        }
    }
    // add an additional space as the second to last character if necessary
    if (rstring[rstring.length() - 1] != ' ') rstring += " ";
    return rstring + "}";
}
