/********************************************************************************
* Author: Michael S. Lewis                                                  	  *
* Date: 1/31/2018                                                           	  *
* Description: unittest1.c implements a unit test of the function               *
*              fullDeckCount() for dominion.c.                                  *
*********************************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define FUNC_TEST "fullDeckCount"
#define NUM_TESTS 10

int main()
{
   int i;
   int handPile;
   int deckPile;
   int discardPile;
   int expectedSum;
   int actualSum;
   int seed = 1000;
   int flag = 0;
   int numPlayer = 2;
   struct gameState G;
   int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag,
      tribute, smithy, council_room};

   srand(time(NULL));   // Seeds random function.

   initializeGame(numPlayer, k, seed, &G);   // Initializes a new game.

   printf("Testing %s()\n", FUNC_TEST);

   /* Compares expected against actual deck count. Executes for NUM_TESTS instances, using
      randomized sizes for handCount, deckCount, and discardCount. */
   for(i = 0; i < NUM_TESTS; i++)
   {
      /* Generates random value to handPile to assign to gamestate's handCount, modulus (max hand) 10. */
      handPile = rand() % 10;
      G.handCount[0] = handPile;

      /* Generates random value to deckPile to assign to gamestate's deckCount, modulus (max deck) 20. */
      deckPile = rand() % 20;
      G.deckCount[0] = deckPile;

      /* Generates random value to discardPile to assign to gamestate's discardCount, modulus (max discard) 10. */
      discardPile = rand() % 10;
      G.discardCount[0] = discardPile;

      expectedSum = handPile + deckPile + discardPile;
      actualSum = fullDeckCount(0, smithy, &G);
      
      if (expectedSum == actualSum)
         printf("Test %d passed! Expected deck count matches actual deck count.\n", i);
      else
      {
         printf("Test %d failed. Expected Count: %d, Actual Count: %d\n", i, actualSum, expectedSum);
         flag = -5;
      }
   }

   /* Prints conclusion of testing result. */
   if(flag == 0)
      printf("All tests passed!\n\n");
   else
      printf("TESTING FAILED!\n\n");

   return 0;
}