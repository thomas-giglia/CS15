/*
 * player.h
 * Written by: Dave Lillethun
 * Edited by: Richard Townsend
 * Date: 11/8/2022
 * Purpose: Define a Hand class to represent a player's hand in the Rack-O game.
 *
 */
#ifndef _PLAYER_H
#define _PLAYER_H
#include "card.h"
#include "vector.h"

class Player {
    public:
        // Constructor
        Player();
        // Destructor
        ~Player();
        Vector* getPassingHand();
        void setPassingHand(Vector *passingHand);
        Vector* getRevealedCards();
        int getScore();
        void addToScore(int deltaScore);
        int getPuddingCount();
        void addToPuddingCount();
        int getChopsticks();
        void addToChopsticks(int deltaSticks);
    private:
        Vector* passingHand;
        Vector* revealedCards;
        //Vector* chosenCards;
        int score;
        int puddingCount;
        int chopsticks;
        
        //void print();
};

#endif // _HAND_H
