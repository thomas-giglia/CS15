/*
 * deck.cpp
 * Written by: Dave Lillethun
 * Edited by: Richard Townsend
 * Date last edited for starter code: 11/8/2022
 * Edited for HW10 by: {YOUR NAME HERE}
 * Date: {DATE YOU STARTED WORKING ON THE HOMEWORK HERE}
 * Purpose: Implement the methods for the Deck class in the Rack-O game.
 *
 */

#include "deck.h"
#include <fstream>
#include <iostream>

using namespace std;

// Constructor:
//Input: Deck input file name
//Description: reads in the numbers listed in a "deck file", create a Card on
// the heap for each number, and store the resulting Card pointers in the deck
//Output: None
Deck::Deck(string deckFileName) {
    ifstream deckFile(deckFileName);
    if (deckFile.fail()) {
        cerr << "Failed to open deck file: " << deckFileName << endl;
        exit(EXIT_FAILURE);
    }

    // Read in all the numbers from the file, making a card for each one and
    // storing it in the deck array.
    string cardType;
    for (int i = 0; i < MAX_DECK_SIZE; i++) {
        // Read in the next number, making sure we didn't run into any errors
        getline(deckFile,cardType);
        if (deckFile.eof()) {
            cerr << "File does not contain " << MAX_DECK_SIZE << " cards!"
                 << endl;
            exit(EXIT_FAILURE);
        } else if (deckFile.fail()) {
            cerr << "Failed to read from file: " << deckFileName << endl;
            exit(EXIT_FAILURE);
        }
        deck[i] = new Card(cardType);
    }
}

//Deck Destructor:
//Input: none
//Description: deallocates any Card pointers remaining in the deck
//Output: None
Deck::~Deck() {
    for (int i = topCard; i < MAX_DECK_SIZE; i++) {
        delete deck[i];
    }
}

//isEmpty
//Input: none
//Description: Checks if more cards have been drawn than there are in the deck
//Output: True if the deck is empty, false otherwise
bool Deck::isEmpty() {
    if (topCard > MAX_DECK_SIZE - 1) {
        return true;
    }
    return false;
}

//draw
//Input: None
//Description: If there are still cards in the deck, it adds 1 to the value
//of topCard and returns what was the top card when the function was called
//Output: The card that was drawn
Card *Deck::draw() {
    if (isEmpty()) {
        cerr << "ERROR: Drawing from an empty deck" << endl;
        exit(EXIT_FAILURE);
    }

    topCard++;
    
    return deck[topCard-1];
}
