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

// int indexOf(string source, string target);

int main() {
    RPNCalc calc;
    calc.run();
    cerr << "Thank you for using CalcYouLater.\n";
    // string source = "#t { quiz } { 200 } if";
    // string target = "quit";
    // cout << indexOf(source, target) << endl;
    return 0;
}

// int indexOf(string source, string target) {
//     int index = 0;
//     for (size_t i = 0; i < source.length(); i++) {
//         if (source[i] == target[0] and source.length() - i > target.length()) {
//             index = i;
//         }
//     }
//     for (size_t j = 0; j < target.length(); j++) {
//         if (target[j] != source[index + j]) index = -1;
//     }
//     return index;
// }
