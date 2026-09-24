/*
 * game.cpp
 * CS11 Sushi Go
 */

#include "game.h"

//Game constructor
//Input: The deck input file name and whether or not chopsticks are to be used
//Description: creates the game, and deck then fills it from the input file
//Output: None
Game::Game(string deckFileName, string play_chopsticks){
    //chosenCards = new Vector();
    if(play_chopsticks == "true"){
        this->play_chopsticks = true;
    } else {
        this->play_chopsticks = false;
    }  

    ifstream deckFile(deckFileName);
    if (deckFile.fail()) {
        cerr << "Failed to open deck file: " << deckFileName << endl;
        exit(EXIT_FAILURE);
    }

    string topCard;
    while(!deckFile.eof()) {
        getline(deckFile, topCard);
        if ((this->play_chopsticks || topCard != "Chopsticks") && i > 0) {
            deck.push_back(new Card(topCard));
        }
        
        if (deckFile.eof()) {
            cerr << "File does not contain " << 108 << " cards!"
                 << endl;
            exit(EXIT_FAILURE);
        } else if (deckFile.fail()) {
            cerr << "Failed to read from file: " << deckFileName << endl;
            exit(EXIT_FAILURE);
        }
    }
}

//playGame
//input: none
//description: deals the cards to players, takes their inputs for what cards
//they want to keep and then passes their hands (p1->p2, p2->p3, p3->p1)
void Game::playGame() {
    int entries[3];
    for(int round = 0; round < ROUNDS; round++){
        for (int i = 0; i < 27; i += 3) {
            for (int j = 0; j < 3; j++) {
                players[j].getPassingHand()->push_back(deck.back());
                deck.pop_back();
            }
        }    
        //select and pass all 27 cards
        Card* keptCard[4];
        int num;
        int chopOwner = -1;
        for(int card = 0; card < CARD_HAND; card++) {
            for(int p = 0; p < PLAYER_COUNT; p++) {
                board.drawBoard(players, p);
                cout << " Player " << p + 1 << ", select a card: ";
                cin >> entries[p];
                if(!cin){ //bail out of game if they enter a non-number
                    cerr << " INVALID INPUT: No game for you!\n";
                    exit(EXIT_FAILURE);
                }
                keptCard[p] = players[p].getPassingHand()->at(entries[p]-1);
                num = playChopsticks (p, entries[p], keptCard);
                if(keptCard[p]->getSushiType() == "Chopsticks") {
                    players[p].addToChopsticks(1);
                    chopOwner = p;
                }
                players[p].getPassingHand()->erase(entries[p]-1);
            }
            for (int p = 0; p < PLAYER_COUNT; p++) {
                players[p].getRevealedCards()->push_back(keptCard[p]);
            }

            Vector *temp = players[0].getPassingHand();
            players[0].setPassingHand(players[2].getPassingHand());
            players[2].setPassingHand(players[1].getPassingHand());
            players[1].setPassingHand(temp);
            int sizes[3];
            for (int i = 0; i < 3; i++) {
                sizes[i] = players[i].getRevealedCards()->size();
                cout << "P" << i+1 << ": " << sizes[i] << endl;
            }
            
        }
        if (!playOn(round)) break;
    }
    addPuddingPoints();
}

int Game::playChopsticks(int p, int choice, Card *keptCard[]) {
    string answer;
    int size = players[p].getPassingHand()->size();
    if (players[p].getChopsticks() == 0) return -1; 
    cout << "     ";
    cout << players[p].getPassingHand()->at(choice-1)->getSushiType();
    cout << " selected!\n     Would you like to use your Chopsticks card to"; 
    cout << " select a second card from your hand? (y/n): ";
    cin >> answer;
    if (answer == "y") {
        int entry = choice;
        players[p].getPassingHand()->erase(choice-1);
        cout << "     Select a second card: ";
        while(entry == choice) {
            cin >> entry;
            if (entry != choice) {
                break;
            } else if (entry == choice && choice == 1) {
                cout << "\tThat card has already been selected.\n\tPlease ";
                cout << "enter a valid number between 2 and " << size << ": ";
            } else if (entry == choice && choice == size) {
                cout << "\tThat card has already been selected.\n\tPlease ent";
                cout << "er a valid number between 1 and " << size - 1 << ": ";
            } else {
                cout << "\tThat card has already been selected.\n\tPlease ";
                cout << "enter a valid number between 1 and " << size;
                cout << " (other than " << choice << "): ";
            }
        }
        return passChopsticks(p, entry-1, keptCard);
    }
    return -1;
}

//passChopsticks
//Input: One int to determine the player, another to determine the card they
//selected with chopsticks, and the array of cards picked without them
//Description: Puts first card into their revealed cards hand, the second card 
//they picked into the array of cards, and the chopsticks in their passing hand
//Output: None
int Game::passChopsticks (int p, int entry, Card *keptCard[]) {
    Card *chosenCard = players[p].getPassingHand()->at(entry-1); 
    //Card *temp = keptCard[p];
    //keptCard[p] = chosenCard;
    //chosenCard = temp;    
    
    for (int i = 0; i < players[p].getRevealedCards()->size(); i++) {
        Card *sticks = players[p].getRevealedCards()->at(i); 
        if (sticks->getSushiType() == "Chopsticks") {
            players[p].getPassingHand()->insert(1,sticks);
            players[p].getRevealedCards()->erase(i);
            players[p].addToChopsticks(-1);
            break;
        }
    }
    
    return entry-1;
}

//playOn:
//Input: The round of the game it is
//Description: Prompts the player to choose if they want
//to continue the game, if so resets their revealedCards vectors, if not ends
//the game
//Output: Whether or not the game should be continued
bool Game::playOn(int round) {
    string play_on;
    
    updateScores();
    board.drawScore(players);

    for (int i = 0; i < PLAYER_COUNT; i++) {
        while(players[i].getRevealedCards()->size()>0){
            delete players[i].getRevealedCards()->back();
            players[i].getRevealedCards()->pop_back();
        }
    }

    if (round < 2) {
        cout << " End of round! Ready for Round "
             << round + 2 << " ? (y/n): ";
        cin >> play_on;
        if(play_on != "y") return false;
    }
    
    return true; 
}   

//updateScores
//Input: None
//Description: Adds up all of the points for each player based on their cards
//Output: None
void Game::updateScores() {
    int makiCount[3] = {0,0,0};
    for (int i = 0; i < 3; i++) {
        int sushiCounter[4] = {0,0,0,0};
        int points = 0;
        for (int j = 0; j < 9; j++) {
            Card* card = players[i].getRevealedCards()->at(j); 
            if (card->getSushiType() == "Maki") {
                makiCount[i] += card->getMakiCount();
            } else if (card->getSushiType() == "Tempura") {
                sushiCounter[0]++; //tempuraCounter
            } else if (card->getSushiType() == "Sashimi") {
                sushiCounter[1]++; //sashimiCounter
            } else if (card->getSushiType() == "Dumpling") {
                if(sushiCounter[2] < 5) {
                    sushiCounter[2]++; //dumplingCount
                    points += sushiCounter[2];
                }
            } else if (card->getSushiType() == "Wasabi") {
                sushiCounter[3]++; //wasabiCount
            } else if (card->getSushiType() == "Pudding") {
                players[i].addToPuddingCount();
            } else if (sushiCounter[3] > 0) {
                sushiCounter[3]--;
                points += 2*calculateNigiri(card);
            }
            points += calculateNigiri(card); 
        }
        points += (sushiCounter[0]/2)*5;
        points += (sushiCounter[1]/3)*10;
        players[i].addToScore(points);
    }
    calculateMaki(makiCount);
}

//calculateMaki
//Input: The number of maki each player has
//Description: Checks if each player has the most maki, if it finds one checks 
//for a player with second most, deals with ties by splitting points
//Output: None
void Game::calculateMaki(int makiCount[]) {
    if(makiCount[0] == makiCount[1] && makiCount[1] == makiCount[2]) {
        return;
    }
    
    for (int i = 0; i < 3; i++){
        if (makiCount[i] > makiCount[(i+1)%3]) {
            if (makiCount[i] > makiCount[(i+2)%3]) {
                players[i].addToScore(6);
                if(makiCount[(i+1)%3]>makiCount[(i+2)%3]) {
                    players[(i+1)%3].addToScore(3);
                } else if (makiCount[(i+2)%3]>makiCount[(i+1)%3]) {
                    players[(i+2)%3].addToScore(3);
                }else {
                    players[(i+1)%3].addToScore(1);
                    players[(i+2)%3].addToScore(1);
                }
                return;
            }
        }

        if (makiCount[i] > makiCount[(i+1)%3]) {
            if (makiCount[i] == makiCount[(i+2)%3]) {
                players[i].addToScore(3);
                players[(i+2)%3].addToScore(3);
                return;
            }
        }
    }
     
}

//CalculateNigiri 
//Input: The players card at certain index of their revealedCards
//Description: Adds up the points gotten from nigiri in a way that makes it
//simple to multiply by 3 if wasabi is usable
//Output: Points from nigiri
int Game::calculateNigiri(Card *card){
    int points = 0;
    if (card->getSushiType() == "Egg-Nigiri") {
        points += 1;
    } else if (card->getSushiType() == "Salmon-Nigiri") {
        points += 2;
    } else if (card->getSushiType() == "Squid-Nigiri") {
        points += 3;
    }
    return points;
}


//addPuddingPoints:
//Input: None
//Description: Determine which player(s) has most puddings, and which player(s) 
//have the least, then adds points to their scores accordingly (splitting the
//points if there are ties)  
//Output: None
void Game::addPuddingPoints() {
    int puddings[3]; 
    for (int i = 0; i < PLAYER_COUNT; i++) {
        puddings[i] = players[i].getPuddingCount();
    }
    
    for (int n = 1; n >= -1; n -= 2) {
        for (int i = 0; i < 3; i++){
            if (n*puddings[i] > n*puddings[(i+1)%3]) {
                if (n*puddings[i] > n*puddings[(i+2)%3]) {
                    players[i].addToScore(n*6);
                }
            }
            if (n*puddings[i] > n*puddings[(i+1)%3]) {
                if (n*puddings[i] == n*puddings[(i+2)%3]) {
                    players[i].addToScore(n*3);
                    players[(i+2)%3].addToScore(n*3);
                }
            }
        }
    } 
    determineWinner(puddings);
}

//determineWinner
//Input: None
//Description: Sorts the players by their number of points and determines who
//won the game
//Output: None 
void Game::determineWinner(int puddings[]) {
    int points[PLAYER_COUNT];
    for (int i = 0; i < PLAYER_COUNT; i++) {
        points[i] = players[i].getScore();
    }
    int people[3] = {0, 1, 2};
    for (int i = 0; i < PLAYER_COUNT; i++) {
        for (int j = 0; j < PLAYER_COUNT - 1; j++) {
            if (points[j] < points[j+1]) {
                swap(&points[j], &points[j + 1]);
                swap(&people[j], &people[j + 1]);
                swap(&puddings[j], &puddings[j + 1]);  
            }
        }
    }
    if(points[0] > points[1]) {
        board.drawWinner(players, people[0]);
    } else if (puddings[0] > puddings[1]) {
        board.drawWinner(players, people[0]);
    } else if (puddings[1] > puddings[0]) {
        board.drawWinner(players, people[1]);
    } else {
        board.drawWinner(players, -1);
    }
}

//swap
//Input: Pointers to two positions within an array
//Description: Swaps the values at those two positions
//Output: None
void Game::swap (int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

//Game destructor
//input: none
//description: deletes every card in the deck
//output: none
Game::~Game(){
    for (int i = 0; i < deck.size(); i++) {
        delete deck.at(i);
    } 
    
}
