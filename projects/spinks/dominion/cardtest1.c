
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

#define TESTCARD "smithy"

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
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG, base;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &base);
    memcpy(&G, &base, sizeof(struct gameState));

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
    // copy the game state to a test case
	memcpy(&testG, &base, sizeof(struct gameState));
    cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

    newCards = 3;

    printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], base.handCount[thisPlayer] + newCards - discarded);
    result = result + assertC(testG.handCount[thisPlayer], base.handCount[thisPlayer] + newCards - discarded);
    printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], base.deckCount[thisPlayer] - newCards);
    result = result + assertC(testG.deckCount[thisPlayer], base.deckCount[thisPlayer] - newCards);
    printf("discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], base.discardCount[thisPlayer] + 1);
    result = result + assertC(testG.discardCount[thisPlayer], base.discardCount[thisPlayer] + 1);

    
	
    
}


