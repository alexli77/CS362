/*******************************************************************************
* Author: Michael S. Lewis                                                     *
* Date: 1/31/2018                                                              *
* Description: unittest3.c implements a unit test of the function              *
*              updateCoins() for dominion.c.                                   *
********************************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>

#define FUNC_TEST "updateCoins"
#define SIZE_HAND   5
#define SIZE_BONUS  2

int main()
{
  int i;
  int numTest = 1;
  int seed = 1000;
  int flag = 0;
  int numPlayer = 2;
  int coppers[MAX_HAND];
  int silvers[MAX_HAND];
  int golds[MAX_HAND];
  int p, handCount;
  int bonus;
  struct gameState G;
  int k[10] = {adventurer, council_room, feast, gardens, mine,
    remodel, smithy, village, baron, great_hall};


  for (i = 0; i < MAX_HAND; i++)
  {
    coppers[i] = copper;  // Fills array with coppers.
    silvers[i] = silver;  // Fills array with silvers.
    golds[i] = gold;      // Fills array with golds.
  }

  printf ("Testing %s():\n", FUNC_TEST);

  for (p = 0; p < numPlayer; p++){   // Runs test for each player.
    for (handCount = 1; handCount <= SIZE_HAND; handCount++){   // Varies count of treasure cards.
      for (bonus = 0; bonus <= SIZE_BONUS; bonus++) {
        printf ("Test player %d with %d treasure card(s) and %d bonus.\n", p, handCount, bonus);
        
        /* Resets gameState and initializes game. */
        memset(&G, 23, sizeof(struct gameState));
        
        initializeGame(numPlayer, k, seed, &G);   // Initializes a new game.

        G.handCount[p] = handCount;

        /* Verifies copper count. */
        memcpy(G.hand[p], coppers, sizeof(int) * handCount);
        updateCoins(p, &G, bonus);

        if (G.coins == handCount * 1 + bonus)   // asserttrue
          printf("Test %d passed! Expected number of %d coppers matches actual result.\n", numTest++, G.coins);
        else
        {
          printf("Test %d failed. Expected number of %d coppers does not match actual result.\n", numTest++, G.coins);
          flag = -5;
        }

        /* Verifies silver count. */
        memcpy(G.hand[p], silvers, sizeof(int) * handCount);
        updateCoins(p, &G, bonus);

        if (G.coins == handCount * 2 + bonus)   // asserttrue
          printf("Test %d passed! Expected number of %d silvers matches actual result.\n", numTest++, G.coins);
        else
        {
          printf("Test %d failed. Expected number of %d silvers does not match actual result.\n", numTest++, G.coins);
          flag = -5;
        }

        /* Verifies gold count. */
        memcpy(G.hand[p], golds, sizeof(int) * handCount);
        updateCoins(p, &G, bonus);

        if (G.coins == handCount * 3 + bonus)   // asserttrue
          printf("Test %d passed! Expected number of %d golds matches actual result.\n", numTest++, G.coins);
        else
        {
          printf("Test %d failed. Expected number of %d golds does not match actual result.\n", numTest++, G.coins);
          flag = -5;
        }
      }
    }
  }

   /* Prints conclusion of testing result. */
   if(flag == 0)
      printf("All tests passed!\n\n");
   else
      printf("TESTING FAILED!\n\n");

  return 0;
}