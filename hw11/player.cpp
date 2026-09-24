/*
 * player.cpp
 * CS11 Sushi Go
 */

#include "player.h"
#include "vector.h"
#include <iostream>
#include <string>

using namespace std;

//Player Constructor:
//Input: None
//Description: initializes all variables within Player class
//Output: None
Player::Player() {
    score = 0;
    puddingCount = 0; 
    chopsticks = 0;
    passingHand = new Vector();
    revealedCards = new Vector();
}

//getScore
//Input: None
//Description: retrieves the private variable "score"
//Output: The player's score
int Player::getScore() {
    return score;
}

//addToScore
//Input: The number of points to be added to score
//Description: Adds deltaScore to score
//Output: None
void Player::addToScore(int deltaScore) {
    score += deltaScore;
}

//getPuddingCount
//Input: None
//Description: Retrieves the private variable "puddingCount"
//Output: The player's pudding count
int Player::getPuddingCount() {
    return puddingCount;
}

//addToScore
//Input: None
//Description: Increments puddingCount
//Output: None
void Player::addToPuddingCount() {
    puddingCount++;
}

//getPuddingCount
//Input: None
//Description: Retrieves the private variable "chopsticks"
//Output: The player's number of chopsticks
int Player::getChopsticks() {
    return chopsticks;
}

//addToScore
//Input: None
//Description: Increments chopsticks
//Output: None
void Player::addToChopsticks(int deltaSticks) {
    chopsticks += deltaSticks;
}

//getPassingHand
//Input: None
//Description: Retrieves the private variable "passingHand"
//Output: The player's passing hand
Vector* Player::getPassingHand() {
    return passingHand;
}

//setPassingHand
//Input: The new passing hand
//Description: changes the value of the private vector variable "passingHand"
//Output: None
void Player::setPassingHand(Vector *passingHand) {
    this -> passingHand = passingHand;
}

//getRevealedCards
//Input: None
//Description: Retrieves the private variable "puddingCount"
//Output: The player's pudding count
Vector* Player::getRevealedCards() {
    return revealedCards;
}

//Player Desctructor
//Input: None
//Description: deallocates any Card pointers remaining in the hands
//Output: None
Player::~Player() {
    delete passingHand;
    delete revealedCards;
} 