#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

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

int getVal(struct gameState* game, enum CARD card, int pos){
	switch (card){
		case curse:
		return -1;
		case estate:
		return 1;
		case duchy:
		return 3;
		case province:
		return 6;
		case great_hall:
		return 1;
		case gardens:
		return (game->deckCount[0] / 10);
	}
	return 0;
}

int main()
{
    int i;
    int j;
    int p;
    int seed = 1323;
    struct gameState state;
    struct gameState test1;
    struct gameState test2;    
    int players = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};


    enum CARD cardsList[6] = {curse, estate, duchy, province, great_hall, gardens};

    initializeGame(players, k, seed, &state);

    //Set base case
    state.handCount[0] = 0;
    state.deckCount[0] = 0;
    state.discardCount[0] = 0;

    printf("-----------------Testing ScoreFor----------------\n");
    memcpy(&test1, &state, sizeof(struct gameState)); //Set discardState to the same State as "state"

    int tempScore = 0;
    //load up deck with cards
    for(i = 0; i < 6; i++){
        //adding all the cards together == -1 + 1 +3 +6 + 1, + 0/10 == 10
        test1.hand[0][i] = cardsList[i];
        test1.handCount[0]++;

        tempScore = tempScore + getVal(&test1, cardsList[i], i);

#if (NOISY_TEST == 1)
        printf("Hand: scoreFor(0, test1) == %d, expected == %d\n", scoreFor(0, &test1), tempScore);
#endif

        assertC(scoreFor(0, &test1), tempScore);
    }

    assertC(scoreFor(0, &test1), 10);

    for(i = 0; i < 10; i++){
        //adding all the cards together == -1 + 1 +3 +6 + 1, + 10/10 -1 + 1 + 3 == 14
        test1.deck[0][i] = cardsList[i % 7];
        test1.deckCount[0]++;

        tempScore = tempScore + getVal(&test1, cardsList[i % 7], i);

#if (NOISY_TEST == 1)
    printf("Deck: scoreFor(0, test1) == %d, expected == %d\n", scoreFor(0, &test1), tempScore);
#endif

        assertC(scoreFor(0, &test1), tempScore);
    }


    for(i = 0; i < 6; i++){
        //adding all the cards together == -1 + 1 +3 +6 + 1, + 10/10 == 11
        test1.discard[0][i] = cardsList[i];
        test1.discardCount[0]++;

        tempScore = tempScore + getVal(&test1, cardsList[i], i);

#if (NOISY_TEST == 1)
    printf("discard: scoreFor(0, test1) == %d, expected == %d\n", scoreFor(0, &test1), tempScore);
#endif
        
        assertC(scoreFor(0, &test1), tempScore);
    }

}

