/*******************************************************************************
* Author: Michael S. Lewis                                                     *
* Date: 1/31/2018                                                              *
* Description: cardtest3.c implements a unit test of the Village card for      *
*              dominion.c.                                                     *
********************************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define CARD_TEST "Village"

int main() 
{
    int result;
    int seed = 1000;
    int flag = 0;
    int numPlayer = 2;
    int thisPlayer = 0;
    struct gameState G, testG;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                    remodel, smithy, village, baron, great_hall};

  printf("TESTING %s card:\n", CARD_TEST);

    // Tests initializeGame().
    result = initializeGame(numPlayer, k, seed, &G);
    if (result == -1)
    {
        printf("Test failed. Game initialization failed.\n");
        flag = -5;
    }
    else
      printf("Test passed! Game initialization successful.\n");

    memcpy(&testG, &G, sizeof(struct gameState));

    //give Village card to first player
    testG.hand[thisPlayer][testG.handCount[thisPlayer]] = village;
    testG.handCount[thisPlayer]++;
    if (G.handCount[thisPlayer] + 1 == testG.handCount[thisPlayer])
        printf("Test passed! Village card given to player.\n");
    else
    {
        printf("Test failed. Village card not given.\n");
        flag = -5;
    }

    //play Village card
    cardEffect(village, 0, 0, 0, &testG, 
            testG.hand[thisPlayer][testG.handCount[thisPlayer]-1], 0);
    
    //test that player gained 1 card
    if (G.handCount[thisPlayer] + 1 == testG.handCount[thisPlayer])
        printf("Test passed! Player gained 1 new card, discarded 1.\n");
    else
    {
        printf("Test failed. Player did not gain/discard correct # of cards.\n");
        flag = -5;
    }

    //test that player gained 2 actions
    if (G.numActions + 2 == testG.numActions)
        printf("Test passed! Player gained 2 actions.\n");
    else
    {
        printf("Test failed. Player did not gain 2 actions.\n");
        flag = -5;
    }

  if(flag == 0)
    printf("All tests passed!\n\n");
  else
    printf("TESTING FAILED!\n\n");

    return 0;
}
