
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

#define TESTCARD "adventurer"

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

void printResult(int res)
{
    if (res < 0)
    {
        printf("Failed Some Tests");
    }
    else
    {
        printf("====PASSED ALL TESTS====");
    }
}

int main()
{
    int result = 0;
    int newCards = 0;
    int discarded = 1;
    int drawnCard;
    int tempHand[100];
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

    for (thisPlayer = 0; thisPlayer < numPlayers; thisPlayer++)
    {
        base.whoseTurn = thisPlayer;
        testG.whoseTurn = thisPlayer;
		base.discardCount[thisPlayer] = 0;
        cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
        int treasure;
        treasure = 0;
        i = 0;
        int deckIndex = base.deckCount[thisPlayer];
        while (treasure < 2)
        {
            drawnCard = base.deck[thisPlayer][deckIndex];
            deckIndex -= 1;
            if (drawnCard == copper || drawnCard == silver || drawnCard == gold)
            {
                treasure += 1;
            }
            else
            {
                tempHand[i] = drawnCard;
                i += 1;
            }
        }

        printf("discardCount == %d, expected == %d\n", testG.discardCount[thisPlayer], base.discardCount[thisPlayer] + i + 1);
        result = result + assertC(testG.discardCount[thisPlayer], base.discardCount[thisPlayer] + i + 1);
        printf("handCount == %d, expected == %d\n", testG.handCount[thisPlayer], base.handCount[thisPlayer] + 1);
        result = result + assertC(testG.handCount[thisPlayer], base.handCount[thisPlayer] + 1);
        printf("deckCount == %d, expected == %d\n", testG.deckCount[thisPlayer], base.deckCount[thisPlayer] - i - treasure);
        result = result + assertC(testG.deckCount[thisPlayer], base.deckCount[thisPlayer] - i - treasure);
    }
    printResult(result);
}
