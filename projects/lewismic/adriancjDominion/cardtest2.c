/*******************************************************************************
* Author: Michael S. Lewis                                                     *
* Date: 1/31/2018                                                              *
* Description: cardtest2.c implements a unit test of the Smithy card for       *
*              dominion.c.                                                     *
********************************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define CARD_TEST "Smithy"

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

   printf("Testing %s card:\n", CARD_TEST);

    /* Tests initializeGame(). */
    result = initializeGame(numPlayer, k, seed, &G);
    if (result == -1)
    {
      printf("Test failed. Game initialization unsuccessful.\n");
      flag = -5;
    }
    else
      printf("Test passed! Game initialization successful.\n");

    memcpy(&testG, &G, sizeof(struct gameState));

    /* Tests draw of Smithy card to player's hand. */
    testG.hand[thisPlayer][testG.handCount[thisPlayer]] = smithy;
    testG.handCount[thisPlayer]++;
    if (G.handCount[thisPlayer] + 1 == testG.handCount[thisPlayer])
        printf("Test passed! Smithy card drawn to hand.\n");
    else
    {
        printf("Test failed. Smithy card not drawn.\n");
        flag = -5;
    }

    /* Tests for correct gain of 3 cards from deck and discard of Smithy. */
    cardEffect(smithy, 0, 0, 0, &testG, 
            testG.hand[thisPlayer][testG.handCount[thisPlayer]-1], 0);

    if (G.handCount[thisPlayer] + 3 == testG.handCount[thisPlayer])
        printf("Test passed! Player gained 3 new cards and discarded 1.\n");
    else
    {
        printf("Test failed. Player did not gain and/or discard correct number of cards.\n");
        flag = -5;
    }

    /* Verifies that card count is unchanged. */
    if (G.supplyCount[estate] == testG.supplyCount[estate])     // Tests game state to verify correct number of Estate cards.
       printf("Test passed! Count of Estate cards unchanged.\n");
    else
    {
       printf("Test failed. Count of Estate cards has changed.\n");
        flag = -5;
    }

    if (G.supplyCount[duchy] == testG.supplyCount[duchy])       // Tests game state to verify correct number of Duchy cards.
       printf("Test passed! Count of Duchy cards unchanged.\n");
    else
    {
       printf("Test failed. Count of Duchy cards has changed.\n");
        flag = -5;
    }

    if (G.supplyCount[province] == testG.supplyCount[province]) // Tests game state to verify correct number of Province cards.
       printf("Test passed! Count of Province cards unchanged.\n");
    else
    {
       printf("Test failed. Count of Province cards has changed.\n");
        flag = -5;
    }

  if(flag == 0)
    printf("All tests passed!\n\n");
  else
    printf("TESTING FAILED!\n\n");

    return 0;
}
