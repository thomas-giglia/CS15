/*
 * card.h
 * Written by: Dave Lillethun
 * Edited by: Richard Townsend
 * Date: 11/8/2022
 * Purpose: Define a Card class to represent cards in the Rack-O game.
 *
 */
#ifndef _CARD_H
#define _CARD_H

#include <string>
using namespace std;

class Card {
public:
    // Constructor
    Card(string cardName);
    ~Card();
    // Getter
    string getSushiType();
    int getMakiCount();

private:
    // The card's values on the card
    string sushiType;
    int makiCount;
};

#endif // _CARD_H
