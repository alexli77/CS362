/********************************************************************************
* Author: Michael S. Lewis                                                      *
* Date: 1/31/2018                                                               *
* Description: unittest2.c implements a unit test of the function whoseTurn ()  *
*              for dominion.c.                                                  *
*********************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "assert.h"
#include "dominion.h"
#include "rngs.h"
#include <time.h>

#define FUNC_TEST "whoseTurn"
#define NUM_TESTS 10

int main()
{
   int i;
   int turn = 0;
   int result = 0;
   int success = 0;
   struct gameState G;

   printf("Testing %s()\n", FUNC_TEST);

   /* Runs test NUM_TESTS times, incrementing turn and testing for match with result on each iteration */
   for (i = 0; i < NUM_TESTS; i++){
      G.whoseTurn = turn;
      result = whoseTurn(&G);

      if (result == turn)   // asserttrue
         printf("Test %d passed! Expected turn matches actual result of whoseTurn().\n", i);
      else {
         printf("Test %d failed. Expected turn: %d, Actual result: %d\n", i, turn, result);
         success = -5;
      }
      turn++;
   }

   /* Prints conclusion of testing result. */
   if (success == 0)
      printf("All tests passed!\n\n");
   else if (success == -5)
      printf("TESTING FAILED!\n\n");

   return 0;
}