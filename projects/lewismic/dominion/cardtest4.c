/*******************************************************************************
* Author: Michael S. Lewis                                                     *
* Date: 1/31/2018                                                              *
* Description: cardtest4.c implements a unit test of the Council Room card for *
*              dominion.c.                                                     *
********************************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define CARD_TEST "Council Room"

int main() 
{
    int i;
    int result;
    int seed = 1000;
    int flag = 0;
    int numPlayer = 4;
    int thisPlayer = 0;
    struct gameState G, testG;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                    remodel, smithy, village, baron, great_hall};

  printf("Testing %s card:\n", CARD_TEST);

    /* Tests initializeGame(). */
    result = initializeGame(numPlayer, k, seed, &G);
    if (result == -1)
    {
      printf("Test failed. Game initialization failed.\n");
      flag = -5;
    }
    else
      printf("Test passed! Game initialization successful.\n");

    memcpy(&testG, &G, sizeof(struct gameState));

    /* Draws a Council Room card for Player 1. */
    testG.hand[thisPlayer][testG.handCount[thisPlayer]] = council_room;
    testG.handCount[thisPlayer]++;
    if (G.handCount[thisPlayer] + 1 == testG.handCount[thisPlayer])
        printf("Test passed! Council Room card given to player.\n");
    else
    {
        printf("Test failed. Council Room card not given.\n");
        flag = -5;
    }

    /* Plays Council Room card and tests for gain of +4 cards. */
    cardEffect(council_room, 0, 0, 0, &testG, 
            testG.hand[thisPlayer][testG.handCount[thisPlayer]-1], 0);

    if (G.handCount[thisPlayer] + 4 == testG.handCount[thisPlayer])
        printf("Test passed! Player 1 drew 4 new cards, discarded 1.\n");
    else
    {
        printf("Test failed. Player 1 did not draw/discard correct # of cards.\n");
        flag = -5;
    }

    /* Tests gain of +1 buy for Player 1. */
    if (G.numBuys + 1 == testG.numBuys)
        printf("Test passed! Player 1 gained +1 buy.\n");
    else
    {
        printf("Test failed. Player 1 did not get +1 buy.\n");
        flag = -5;
    }

    /* Tests gain of +1 card for each other player. */
    for (i = 1; i < numPlayer; i++)
    {
        if (G.handCount[i] + 1 == testG.handCount[i])
            printf("Test passed! Player %d drew 1 card.\n", (i + 1));
        else
        {
            printf("Test failed. Player %d did not draw 1 card.\n", (i + 1));
            flag = -5;
        }
    }

  if(flag == 0)
    printf("All tests passed!\n\n");
  else
    printf("TESTING FAILED!\n\n");

    return 0;
}
