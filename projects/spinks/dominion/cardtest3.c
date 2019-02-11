
/*
 * cardtest4.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest4: cardtest4.c dominion.o rngs.o
 *      gcc -o cardtest1 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "village"

int assertC(int actual, int expected)
{
    if (actual == expected)
    {
        printf("--PASSED--\n"); 
        return 0;
    }
    else
    {
        printf("--TEST FAILED--\n");
        return -1;
    }
}

void printResult(int res){
    if(res < 0){
        printf("Failed Some Tests");
    } else {
        printf("====PASSED ALL TESTS====");
    }
}

int main() {
    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;
    int result = 0;

    int i, j, m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int remove1, remove2;
    int seed = 1000;
    int numPlayers = 4;
    int thisPlayer = 0;
	struct gameState testG, base;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &base);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
    // copy the game state to a test case
	memcpy(&testG, &base, sizeof(struct gameState));
    

    for(thisPlayer = 0; thisPlayer < numPlayers; thisPlayer++){
        testG.whoseTurn = thisPlayer;
        base.whoseTurn = thisPlayer;
		
        cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);
        printf("handCount == %d, expected == %d\n", testG.handCount[thisPlayer], base.handCount[thisPlayer] + 1 - 1);
        result = result + assertC(testG.handCount[thisPlayer], base.handCount[thisPlayer] + 1 - 1);
        printf("actionCount == %d, expected == %d\n", testG.numActions, base.numActions + 2);
        result = result + assertC(testG.numActions, base.numActions + 2);
        printf("deckCount == %d, expected == %d\n", testG.deckCount[thisPlayer], base.deckCount[thisPlayer] - 1);
        result = result + assertC(testG.deckCount[thisPlayer], base.deckCount[thisPlayer] - 1);
		testG.numActions = 0;
		base.numActions = 0;
    }

    printResult(result);

}


    
