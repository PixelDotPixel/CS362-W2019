
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

#define TESTCARD "council room"

int assertC(int actual, int expected)
{
    if (actual == expected)
    {
        printf("--PASSED--\n"); 
        return -1;
    }
    else
    {
        printf("--TEST FAILED--\n");
        return 0;
    }
}

void printResult(int res){
    if(res < 0){
        printf("Failed %d Tests\n", res * (-1));
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
    int addedCards[4] = {0, 0, 0, 0};
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

    int playerCard = 0;
    for(thisPlayer = 0; thisPlayer < numPlayers; thisPlayer++){
		printf("====>Player %d is playing the card\n", thisPlayer);
        base.whoseTurn = thisPlayer;
        testG.whoseTurn = thisPlayer;
        cardEffect(council_room, choice1, choice2, choice3, &testG, handpos, &bonus);
        addedCards[thisPlayer] += 4; 
		printf("handCount[%d] == %d, expected == %d\n", thisPlayer, testG.handCount[thisPlayer],  base.handCount[thisPlayer] + addedCards[thisPlayer]);
        result = result + assertC(testG.handCount[thisPlayer], base.handCount[thisPlayer] + addedCards[thisPlayer]);
		printf("numBuys == %d, expected == %d\n", testG.numBuys, base.numBuys + 1);
        result = result + assertC(testG.numBuys, base.numBuys + 1);
        for(j = 0; j < numPlayers; j++){
            if(j != thisPlayer){
                addedCards[j] += 1;
				printf("handCount[%d] == %d, expected == %d\n", j, testG.handCount[j], base.handCount[j] + addedCards[j]);
                result = result + assertC(testG.handCount[j], base.handCount[j] + addedCards[j]); 
            }
        }
		base.numBuys = 0;
		testG.numBuys = 0;
    }

    printResult(result);

}


        
