#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define TESTCARD "adventurer"

int noise = 1;

int assertC(int actual, int expected, char this[50], char that[50])
{   
    if (actual == expected)
    {
        // printf("%s == %s\n", this, that);
    	// printf("Actual == %d  &&  Expected == %d\n", actual, expected);	
        //printf("--PASSED--\n"); 
        return 0;
    }
    else
    {
    	// printf("%s == %s\n", this, that);
    	// printf("Actual == %d  &&  Expected == %d\n", actual, expected);		
        // printf("--TEST FAILED--\n");
        return -1;
    }
}


int assertCDNE(int actual, int expected, char this[50], char that[50])
{
	
    if (actual != expected)
    {
        //printf("--PASSED--\n"); 
        return 0;
    }
    else
    {
		// printf("%s != %s\n", this, that);
        // printf("--TEST FAILED--\n");
        return -1;
    }
}

void finalprintResult(int res, int total)
{
    printf("Failed %d/%d test\n", (res*(-1)), total);
}

int searchForDeck(struct gameState* search, int Player, int Card){
    int d;
	int found = -1;
    for(d = 0; d < search->deckCount[Player]; d++){
        if(search->deck[Player][d] == Card)
            found = d;
    }
    return found;
}

int searchForHand(struct gameState* search, int Player, int Card){
    int d;
	int found = -1;
    for(d = 0; d < search->handCount[Player]; d++){
        if(search->hand[Player][d] == Card)
            found = d;
    }
    return found;
}

// Builds a random deck ranging from sizes 10 - 59 of random cards with a garunteed 2 treasure cards
void deckBuilder(struct gameState* testing, struct gameState* reference, int Player){
    int newDeckSize;                                    //Will become the new size of the deck
    int coinLocA, coinLocB;                             //Variables for the locations of 2 random treasure cards
    int index;                                          //Increments through the deck
    int newCard;                                        //holds the new card that will be added to the deck
    newDeckSize = (rand() % 50) + 10;                   //generate a random new deck size
    coinLocA = rand() % newDeckSize;                    //generate the first coin location
    coinLocB = rand() % newDeckSize;                    //generate the second coin location
    if(coinLocA == coinLocB){                           //if the two coin locations are the same offset by 1
        coinLocB = (coinLocA + 1) % newDeckSize;
    }    
    for(index = 0; index < newDeckSize; index++){       //Loop through each index of the deck and assign a random card there
        if(index == coinLocA || index == coinLocB){     //if we are at coin location generate a coin
            newCard = (rand() % 3) + 4;
        } else {                                        //anything else just generate a random card
            newCard = rand() % 27;
        }
        testing->deck[Player][index] = newCard;         //add the newCard to both testing and reference decks
        reference->deck[Player][index] = newCard;        
    }
    testing->deckCount[Player] = newDeckSize;           //Set the new deckCount for both testing (test) and reference (base)
    reference->deckCount[Player] = newDeckSize;
}


int main()
{
    int cardTested = adventurer;
    int result = 0;
    int tests = 0;
    int handOrDeck;
    int testSeed = 0;
    int Player = 0;
    int numPlayers = 2;
    int i, j;
    int randChce1, randChce2, randChce3, randLoc;
    int randK1, randK2, randK3, randK4, randK5, randK6, randK7, randK8, randK9, randK10;
    struct gameState base, test;

    printf("===============Testing %s===============\n", TESTCARD);
    for(numPlayers = 2; numPlayers <= 4; numPlayers++){
        for(testSeed = 1; testSeed < 32000; testSeed++){

            //Initialize random values and base (reference) game state
            srand(time(0));                                //Seed the rand generator
            randChce1 = rand();                                         //Random choices shouldn't matter because adventurer doesnt rely on choices
            randChce2 = rand();                                         //Random choices shouldn't matter because adventurer doesnt rely on choices
            randChce3 = rand();                                         //Random choices shouldn't matter because adventurer doesnt rely on choices
            handOrDeck = rand() % 2;                                    //Random planting of card either in the hand or in the deck
            randK1 = rand();                                            //Random kingdomcard values (not limited to enum CARDS)
            randK2 = randK1 + 1;                                        //
            randK3 = randK2 + 1;                                        //
            randK4 = randK3 + 1;                                        //
            randK5 = randK4 + 1;                                        //
            randK6 = randK5 + 1;                                        //
            randK7 = randK6 + 1;                                        //
            randK8 = randK7 + 1;                                        //
            randK9 = randK8 + 1;                                        //
            randK10 = randK9 + 1;                                       //
            int k[10] = {randK1, randK2, randK3, randK4, randK5, randK6,
            randK7, randK8, randK9, randK10};   
			int coinsAdded = 0;         

            //Set up test subjects           
            initializeGame(numPlayers, k, testSeed, &base);             //Initialize base with K, and a seed (0-max_rand)
            memcpy(&test, &base, sizeof(struct gameState));             //Deep copy base to the test case
            
            deckBuilder(&test, &base, Player);                          //Initializes a random deck on both test and base

            //Plants the card to be tested either in the deck or in the players hand based off rand() mod 2
            if(handOrDeck == 0){
                randLoc = rand() % base.handCount[Player];              //Generate a location within range of the set
                base.hand[Player][randLoc] = cardTested;                //Place cardTested in the hand of base
				test.hand[Player][randLoc] = cardTested;                //Place cardTested in the hand of test
            } else {
                randLoc = rand() % base.deckCount[Player];              //Generate a location within range of the set
                base.deck[Player][randLoc] = cardTested;                //Place cardTested in the deck of base
				test.deck[Player][randLoc] = cardTested;                //Place cardTested in the deck of test
            }

            //Actual test cases are performed here
            int deckDiscards = 0;
            int treasure, deckIndex, drawnCard;                         //Variables for the number of treasure cards found, the location the last treaseure card is, and a temp card holder
            int treasureCards[2];                                       //Holds an array of the 2 treasure cards found
            treasure = 0;                                               //Initialize treasure count to 0
            deckIndex = base.deckCount[Player];                         //Deck index will start at the top of the deck
            
            if(handOrDeck == 0){         //IF the card to be tested is located in the hand
                i = searchForHand(&test, Player, cardTested);           //Get the cards location in the hand

                //Find the 2nd treasure card location
                while (treasure < 2 && deckIndex != 0){                 //While 2 treasuire cards have not been found, and we haven't reached the end of the deck
                    drawnCard = base.deck[Player][deckIndex];           //check card at deck index location (starts at the top of the deck)
                    deckIndex -= 1;                                     //Decrement deck index to the next card from the top
                    deckDiscards++;
                    if (drawnCard == copper || drawnCard == silver || drawnCard == gold)
                    {
                        treasureCards[treasure] = drawnCard;            //If we have found a treasure card add it to a temp hand so we can reference later in assertC
                        treasure += 1;                                  //Increment the number of treasure cards found
                    }
                }

                if (treasure == 2){
					cardEffect(cardTested, randChce1, randChce2, randChce3, &test, i, NULL);
                    //Assert that the deckCount was reduced by the number of cards between the top and the second treasure card
                    //Assert that the handcount has been increased by 2 cards, and decreased by one card (played card)
                    //Assert that the discard pile has gained a card
                    //Assert that the two treasure cards are the top 2 in the deck
                    //ASsert that the number of actions was reduced by 1
                    // and that all other states are unchanged
                    result += assertC(test.deckCount[Player], deckIndex, "test.deckCount[Player]", "deckIndex");
                    result += assertC(test.handCount[Player], base.handCount[Player] + 1, "test.handCount[Player]", "base.handCount[Player]");
                    result += assertC(test.discardCount[Player], base.discardCount[Player] - deckDiscards - 1, "test.discardCount[Player]", "base.deckCount[Player]");
                    result += assertC(test.numBuys, base.numBuys, "test.numBuys", "base.numBuys");
                    result += assertC(test.numActions, base.numActions, "test.numActions", "base.numActions");
                    result += assertC(test.coins, base.coins + coinsAdded, "test.coins", "base.coins");
                    result += assertC(test.whoseTurn, base.whoseTurn, "test.whoseTurn", "base.whoseTurn");
                    result += assertC(test.phase, base.phase, "test.phase", "base.phase");
                    result += assertC(test.outpostPlayed, base.outpostPlayed, "test.outpostPlayed", "base.outpostPlayed");
                    result += assertC(test.outpostTurn, base.outpostTurn, "test.outpostTurn", "base.outpostTurn");
                    
                    tests += 10;
                    for (i = 0; i < treasure; i++){
                        result += assertCDNE(-1, searchForHand(&test, Player, treasureCards[i]), "-1", "Searchforhand");
                        tests++;
                    }
                }

            } else {

                i = searchForDeck(&test, Player, cardTested);           //Index location in the deck of where the card is located at
                int drawnIndex;                                         //drawnIndex is used to count up the number of cards drawn
                drawnIndex = 0;

                while (test.deckCount[Player] > i){
                    drawCard(Player, &test);                            //Draws the top card of the deck
                    drawnIndex += 1;                                    //Increments drawnIndex
                    deckDiscards += 1;
                }

                j = searchForHand(&test, Player, cardTested);

                cardEffect(cardTested, randChce1, randChce2, randChce3, &test, j, NULL); //Play the card (Implimenting card effect and discard)
                
                //Find the 2nd treasure card location
                deckIndex = base.deckCount[Player] - drawnIndex;
                while (treasure < 2 && deckIndex != 0){                 //While 2 treasuire cards have not been found, and we haven't reached the end of the deck
                    drawnCard = base.deck[Player][deckIndex];           //check card at deck index location (starts at the top of the deck)
                    deckIndex -= 1;                                     //Decrement deck index to the next card from the top
                    deckDiscards++;
                    if (drawnCard == copper || drawnCard == silver || drawnCard == gold)
                    {
                        treasureCards[treasure] = drawnCard;            //If we have found a treasure card add it to a temp hand so we can reference later in assertC
                        treasure += 1;                                  //Increment the number of treasure cards found
                    }
                }
                //Assert that the deckCount was reduced by the number of cards between the top and the second treasure card
                //Assert that the handcount has been increased by 2 cards, and decreased by one card (played card)
                //Assert that the discard pile has gained a card
                //Assert that the two treasure cards are the top 2 in the deck
                //Assert that the number of actions was reduced by 1
                // and that all other states are unchanged
                result += assertC(test.deckCount[Player], base.deckCount[Player] - deckDiscards, "test.deckCount[Player]", "base.deckCount[Player] - deckDiscards");
                result += assertC(test.handCount[Player], base.handCount[Player] + drawnIndex + 1, "test.handCount[Player]", "base.handCount[Player] + drawnIndex + 1");
                result += assertC(test.discardCount[Player], base.discardCount[Player] + deckDiscards + 1, "test.discardCount[Player]", "base.discardCount[Player] + deckDiscards + 1");  
                result += assertC(test.numBuys, base.numBuys, "test.numBuys", "base.numBuys");
                result += assertC(test.numActions, base.numActions, "test.numActions", "base.numActions");
                result += assertC(test.whoseTurn, base.whoseTurn, "test.whoseTurn", "base.whoseTurn");
                result += assertC(test.phase, base.phase, "test.phase", "base.phase");
                result += assertC(test.outpostPlayed, base.outpostPlayed, "test.outpostPlayed", "base.outpostPlayed");
                result += assertC(test.outpostTurn, base.outpostTurn, "test.outpostTurn", "base.outpostTurn");
                    
                tests += 10;            
                for(i = 0; i < treasure; i++){
                    result += assertCDNE(-1, searchForHand(&test, Player, treasureCards[i]), "", "");
                    tests++;
                }  
            } 
        }
    }

    finalprintResult(result, tests); 
}
