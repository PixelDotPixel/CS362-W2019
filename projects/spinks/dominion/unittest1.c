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

int main() {
    int i;
    int j;
    int p;
	int result = 0;
    int seed = 1323;
    struct gameState state;
    int players = 2;
    int playerTrack;
    int maxHandCount = 10;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    
    int handRef[2][10];
    // CARD cardsList [27] = {"curse", "estate", "duchy", "province", "copper", "silver", "gold", "adventurer", "council_room", "feast", 
    //                         "gardens", "mine", "remodel", "smithy", "village", "baron", "great_hall", "minion", "steward", "tribute", ""}

    enum CARD cardsList [27] ={curse, estate, duchy, province, copper, silver, gold, adventurer, council_room, feast, gardens, mine, remodel, smithy, 
                          village, baron, great_hall, minion, steward, tribute, ambassador, cutpurse, embargo, outpost, salvager, sea_hag, treasure_map};
    initializeGame(players, k, seed, &state);

    printf("-----------------Testing Discard----------------\n");

    printf("####- Asserting Trash Discard flag on playedCards -####");

    for(j = 0; j < 5; j++){
		printf("[==-----------------Testing Hand %d----------------==]\n", j+1);
        state.handCount[0] = 5;
        state.handCount[1] = 5;

        for(i = 0; i < 5; i++){
            state.hand[0][i] = (i + j*5);
            state.hand[1][i] = (27 - i - (j*5));
        }

        for(i = 0; i < 5; i++){
#if (NOISY_TEST == 1)
        printf("state.hand[0][%d] == %d, expected == %d\n", i, state.hand[0][i], (i + j*5));
#endif
            result= result + assertC(state.hand[0][i], (i + j*5));

#if (NOISY_TEST == 1)
        printf("state.hand[1][%d] == %d, expected == %d\n", i, state.hand[1][i], (27 - i - (j*5)));
#endif
            result= result + assertC(state.hand[1][i], (27 - i - (j*5)));
        }

        for(i = 0; i < 5; i++){
			printf("----------Testing Card %d: Player------------\n", i+1);
			int tempCard1 = state.hand[0][0];
			int tempCard2 = state.hand[1][0];
            discardCard(0, 0, &state, 0);

#if (NOISY_TEST == 1)
        printf("state.handCount[0] == %d, expected == %d\n", state.handCount[0], 5-(i+1));
#endif            
            result= result + assertC(state.handCount[0], 5-(i+1));

#if (NOISY_TEST == 1)
        printf("state.hand[0][%d] == %d, expected == %d\n", i, state.hand[0][5-(i+1)], -1);
#endif          
            result= result + assertC(state.hand[0][5-(i+1)], -1);


#if (NOISY_TEST == 1)
        printf("playedCardCount == %d, state.playedCards[state.playedCardCount - 1] == %d, expected == %d\n", state.playedCardCount, state.playedCards[state.playedCardCount - 1], tempCard1);
#endif          
            result= result + assertC(state.playedCards[state.playedCardCount - 1], tempCard1);

			printf("----------Testing Card %d: Opponent------------\n", i+1);

            discardCard(0, 1, &state, 0);

#if (NOISY_TEST == 1)
        printf("state.handCount[1] == %d, expected == %d\n", state.handCount[1], 5-(i+1));
#endif            
            result= result + assertC(state.handCount[1], 5-(i+1));

#if (NOISY_TEST == 1)
        printf("state.hand[0][%d] == %d, expected == %d\n", i, state.hand[0][i], (i + j*5));
#endif          
            result= result + assertC(state.hand[1][5-(i+1)], -1);

#if (NOISY_TEST == 1)
        printf("platedCardCount - 1 == %d, state.playedCards[state.playedCardCount - 1] == %d, expected == %d\n\n", state.playedCardCount - 1, state.playedCards[state.playedCardCount - 1], tempCard2);
#endif          
            result= result + assertC(state.playedCards[state.playedCardCount - 1], tempCard2);
        }
	
	printResult(result);

    }

}
