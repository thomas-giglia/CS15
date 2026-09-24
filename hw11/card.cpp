/*
 * card.cpp
 * Written by: Dave Lillethun
 * Edited by: Richard Townsend
 * Date last edited for starter code: 11/8/2022
 * Edited for HW10 by: {Thomas Giglia}
 * Date: {4/11/2024}
 * Purpose: Implement the methods for the Card class in the Rack-O game.
 *
 */

//NOTE: If we want to include a file we wrote, we need to use "" instead of <>
//when naming the file to include.
#include "card.h"
#include <iostream>

using namespace std;

// Constructor: initialize the private field of a Card object
Card::Card(string cardName) {
    sushiType = cardName;
    if (cardName == "Maki    1") {
        sushiType = "Maki";
        makiCount = 1;
    } else if (cardName == "Maki    2") {
        sushiType = "Maki";
        makiCount = 2;
    } else if (cardName == "Maki    3") {
        sushiType = "Maki";
        makiCount = 3;
    } else {
        makiCount = 0;
    }
}

Card::~Card() {
}

// getType
// Input: none
// Description: Getter for the cardType private field
// Output: This cards type
string Card::getSushiType() {
    if (sushiType.length() == 0) {
        cerr << "ERROR: tried to read an uninitialized card" << endl;
        exit(EXIT_FAILURE);
    }
    return sushiType;
}

// getVal
// Input: none
// Description: Getter for the cardVal private field
// Output: the value of this card alone
int Card::getMakiCount() {
    if (makiCount < 0) {
        cerr << "ERROR: tried to read an uninitialized card" << endl;
        exit(EXIT_FAILURE);
    }
    return makiCount;
}

