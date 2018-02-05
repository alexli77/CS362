/********************************************************************************
* Author: Michael S. Lewis                                                      *
* Date: 1/31/2018                                                               *
* Description: unittest1.c implements a unit test of the function               *
*              fullDeckCount() for dominion.c.                                  *
*********************************************************************************/
#include "interface.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

#define FUNC_TEST "fullDeckCount"

int main()
{
  printf("Testing %s():\n", FUNC_TEST);
  int flag = 0;

  struct gameState G;

  int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, 
    great_hall};

  initializeGame(2, k, 1, &G);

  int testHand1[0];
  int testDeck1[0];
  int testDiscard1[0];
  int result;

  memcpy(G.hand[0], testHand1, 0);
  memcpy(G.deck[0], testDeck1, 0);
  memcpy(G.discard[0], testDiscard1, 0);
  G.handCount[0] = 0;
  G.deckCount[0] = 0;
  G.discardCount[0] = 0;

  /* Tests for condition when deck is empty. */
  result = fullDeckCount(0, copper, &G);
  if (result == 0)   // asserttrue
  {
    printf("Test 1 passed! Expected deck count of 0 matches actual result.\n");
  }
  else
  {
    printf("Test 1 failed. Expected deck count does not match actual result.\n");
    flag = -5;
  }

  int testHand2[5];
  testHand2[0] = copper;
  testHand2[1] = copper;
  testHand2[2] = copper;
  testHand2[3] = copper;
  testHand2[4] = copper;
  memcpy(G.hand[0], testHand2, 5 * sizeof(int));
  G.handCount[0] = 5;

  int testDeck2[7];
  testDeck2[0] = copper;
  testDeck2[1] = copper;
  testDeck2[2] = copper;
  testDeck2[3] = copper;
  testDeck2[4] = copper;
  testDeck2[5] = copper;
  testDeck2[6] = copper;
  memcpy(G.deck[0], testDeck2, 7 * sizeof(int));
  G.deckCount[0] = 7;

  int testDiscard2[3];
  testDiscard2[0] = copper;
  testDiscard2[1] = copper;
  testDiscard2[2] = copper;
  memcpy(G.discard[0], testDiscard2, 3 * sizeof(int));
  G.discardCount[0] = 3;

  /* Tests for silvers if deck only has coppers. */
  result = fullDeckCount(0, silver, &G);
  if (result == 0)   // asserttrue
  {
    printf("Test 2 passed! Expected deck count of 0 matches actual result.\n");
  }
  else
  {
    printf("Test 2 failed. Expected deck count does not match actual result.\n");
    flag = -5;
  }

  /* Tests for coppers if deck only has coppers. */
  result = fullDeckCount(0, copper, &G);
  if (result == 15)   // asserttrue
  {
    printf("Test 3 passed! Expected deck count of 15 matches actual result.\n");
  }
  else
  {
    printf("Test 3 failed. Expected deck count does not match actual result.\n");
    flag = -5;
  }

  /* Prints conclusion of testing result. */
  if(flag == 0)
      printf("All tests passed!\n\n");
  else
      printf("TESTING FAILED!\n\n");

  return 0;
}
