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
        return 0;
    }
    else
    {
        printf("--TEST FAILED--\n");
        return -1;
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

int getVal(enum CARD card){
	switch (card){
		case curse:
		return 0;
		case estate:
		return 2;
		case duchy:
		return 5;
		case province:
		return 8;
        case copper:
        return 0;
        case silver:
        return 3;
        case gold:
        return 6;
        case adventurer:
        return 6;
        case council_room:
        return 5;
        case feast:
        return 4;
        case gardens:
        return 4;
        case mine:
        return 5;
        case remodel:
        return 4;
        case smithy:
        return 4;
        case village:
        return 3;
        case baron:
        return 4;
		case great_hall:
		return 3;
		case minion:
		return 5;
        case steward:
        return 3;
        case tribute:
        return 5;
        case ambassador:
        return 3;
        case cutpurse:
        return 4;
        case embargo:
        return 2;
        case outpost:
        return 5;
        case salvager:
        return 4;
        case sea_hag:
        return 4;
        case treasure_map:
        return 4;
	}
	return 0;
}

int main()
{
    int i;
    int j;
    int p;
    int seed = 1323;
	int result = 0;
    struct gameState state;
    struct gameState test1;
    struct gameState test2;    
    int players = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

    initializeGame(players, k, seed, &state);

    //Set base case
    state.handCount[0] = 0;
    state.deckCount[0] = 0;
    state.discardCount[0] = 0;

    printf("-----------------Testing Card Costs----------------\n");
    memcpy(&test1, &state, sizeof(struct gameState)); //Set discardState to the same State as "state"
    enum CARD temp;
    for(temp = curse; temp <= treasure_map; temp++){
        printf("getCost(%d) == %d, expected == %d\n", temp, getCost(temp), getVal(temp));
        result = result + assertC(getCost(temp), getVal(temp));
    }
	printResult(result);
}

