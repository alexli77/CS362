/*******************************************************************************
* Author: Michael S. Lewis                                                     *
* Date: 1/31/2018                                                              *
* Description: cardtest1.c implements a unit test of the Adventurer card for   *
*              dominion.c.                                                     *
********************************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define CARD_TEST "Adventurer"

int main() 
{
    int i;
    int result;
    int seed = 1000;
    int flag = 0;
    int numPlayer = 2;
    int thisPlayer = 0;
    int cardDrawn1, cardDrawn2;
    int finalCount = 0
    int originalCount = 0;
    struct gameState G, testG;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                    remodel, smithy, village, baron, great_hall};

  printf("TESTING %s card\n", CARD_TEST);

    // Tests initializeGame().
    result = initializeGame(numPlayer, k, seed, &G);
    if (result == -1)
    {
      printf("Test failed. Game initialization unsuccessful.\n");
      flag = -5;
    }
    else
      printf("Test passed! Game initialization successful.\n");

    memcpy(&testG, &G, sizeof(struct gameState));

    // Tests draw of Adventurer card to player's hand.
    testG.hand[thisPlayer][testG.handCount[thisPlayer]] = adventurer;
    testG.handCount[thisPlayer]++;
    if (G.handCount[thisPlayer] + 1 == testG.handCount[thisPlayer])
        printf("Test passed! Adventurer card drawn to hand.\n");
    else
    {
        printf("Test failed. Adventurer card not drawn.\n");
        flag = -5;
    }

    // Tests Adventurer card for draw of 2 treasure cards.
    playAdventurer(thisPlayer, &testG);

    // Verifies that at least 2 new treasure cards were added to hand.
    for (i = 0; i < testG.handCount[thisPlayer]; i++) 
    {
       cardDrawn1 = testG.hand[thisPlayer][i];
       if (cardDrawn1 == copper || cardDrawn1 == silver || cardDrawn1 == gold)
          finalCount++;
    }
    for (i = 0; i < G.handCount[thisPlayer]; i++) 
    {
       cardDrawn2 = G.hand[thisPlayer][i];
       if (cardDrawn2 == copper || cardDrawn2 == silver || cardDrawn2 == gold)
          originalCount++;
    }
    if ((finalCount - originalCount) > 0 || (finalCount - originalCount) < 3 )
       printf("Test passed! %d additional treasure cards drawn.\n", 
                  (finalCount - originalCount));
    else
    {
      printf("Test failed. Less than 1 or more than 3 treasure cards drawn.\n");
      flag = -5;
    }

    // Verifies that more cards are present after playing Adventure card.
    if (G.handCount[thisPlayer] < testG.handCount[thisPlayer])
       printf("Test passed! Additional cards added to test hand.\n");
    else
    {
      printf("Test failed. No additional cards added to test hand.\n");
      flag = -5;
    }

  if(flag == 0)
    printf("All tests passed!\n\n");
  else
      printf("TESTING FAILED!\n\n");

  return 0;
}