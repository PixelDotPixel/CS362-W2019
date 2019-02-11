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

int handContainsCard(int card, struct gameState* state, int player){
    int j;
    for(j = 0; j < state->handCount[0]; j++){
        if(state->hand[player][j] == card)
            return 1;
    }
    return 0;
}

int main()
{
        int i;
        int j;
        int p;
        int seed = 1323;
        struct gameState state, G;
        struct gameState discardState;
        int players = 2;
        int playerTrack;
        int maxHandCount = 13;
        int refDeck[13];
        int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
		int refDeckSize;
		

        int handRef[2][10];

        enum CARD cardsList[27] = {curse, estate, duchy, province, copper, silver, gold, adventurer, council_room, feast, gardens, mine, remodel, smithy,
                                   village, baron, great_hall, minion, steward, tribute, ambassador, cutpurse, embargo, outpost, salvager, sea_hag, treasure_map};

        initializeGame(players, k, seed, &state);

        printf("-----------------Testing DrawCard on Empty Deck, 10 Discard Pile----------------\n");
        memcpy(&discardState, &state, sizeof(struct gameState));    //Set discardState to the same State as "state"
        memcpy(&G, &state, sizeof(struct gameState));

        discardState.discardCount[0] = 0;

        //fill discardState discardPile with every odd card
        for(i = 0; i < 27; i = i + 2){
            discardState.discard[0][discardState.discardCount[0]] = i;
            refDeck[discardState.discardCount[0]] = i;
            discardState.discardCount[0]++;
        }
        
        //Set Deck to Empty
        discardState.deckCount[0] = 0;

        //Set Hand to empty
        for(i = 0; i < 13; i++){
            discardState.hand[0][i] = -1;
        }

        discardState.handCount[0] = 0;

        for(i = 0; i <= 13; i++){
            drawCard(0, &discardState);
            if(i == 0){

#if (NOISY_TEST == 1)
                        printf("discardState.deckCount == %d, expected == 13\n", discardState.deckCount[0]);
#endif                

                //Asserts that the deck has taken in the discard pile
                assertC(discardState.deckCount[0], 13);
            }
        }

#if (NOISY_TEST == 1)
                        printf("discardState.deckCount == %d, expected == 0\n", discardState.deckCount[0]);
#endif             

        //Assert that the deck is empty again
        assertC(discardState.deckCount[0], 0);
        
        //Assert that each card in the discardPile is in the players deck now
        for(i = 0; i < 13; i++){

#if (NOISY_TEST == 1)
                        printf("%d: discardState.hand[0][%d] == %d, expected == TRUE\n", i, discardState.hand[0][i]);
#endif             
            assertC(handContainsCard(refDeck[i], &discardState, 0), 1);
        }


		printf("-----------------Testing DrawCard on Full Deck----------------\n");

        for(i = 0; i < G.deckCount[0]; i++){
            drawCard(0, &G);
            printf("handCount == %d, expected == %d", G.handCount[0], state.handCount[0] + (i+1));
            result = result + assertC(G.handCount[0], state.handCount[0] + (i+1));
            printf("deckCount == %d, expected == %d", G.deckCount[0], state.deckCount[0] - (i+1));
            result = result + assertC(G.deckCount[0], state.deckCount[0] - (i+1));
        }

        printf("handCount == %d, expected (deckCount) == %d", G.handCount[0], state.deckCount[0]);
        result = result + assertC(G.handCount[0], state.deckCount[0]);
}

