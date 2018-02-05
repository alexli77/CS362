/*******************************************************************************
* Author: Michael S. Lewis                                                     *
* Date: 1/31/2018                                                              *
* Description: unittest4.c implements a unit test of the function isGameOver() *
*              for dominion.c.                                                 *
********************************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define FUNC_TEST "isGameOver"

int main() 
{
    int i;
    int result;
    int seed = 1000;
    int flag = 0;
    struct gameState G, testG;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                    remodel, smithy, village, baron, great_hall};

    printf("Testing %s():\n", FUNC_TEST);

    /* Tests initializeGame(). */
    result = initializeGame(MAX_PLAYERS, k, seed, &G);
    if (result == -1)
    {
      printf("Test failed. Game initialization unsuccessful.\n");
      flag = -5;
    }
    else
      printf("Test passed! Game initialization successful.\n");

    memcpy(&testG, &G, sizeof(struct gameState));

    /* Tests for proper end of game or continuation behavior when provinces in supply pile > 0 */ 
    printf("supplyCount[province] = %d\n", G.supplyCount[province]);
    if (isGameOver(&G))
        printf("Test failed. Incorrect result of gameover.\n");
    else
        printf("Test passed. Correct result, game continues.\n");

    /* Tests for proper behavior when provinces in supply pile == 0 */ 
    G.supplyCount[province] = 0;
    printf("supplyCount[province] = %d\n", G.supplyCount[province]);
    if (isGameOver(&G))
        printf("Test passed. Correct result of gameover.\n");
    else
        printf("Test failed. Game incorrectly continues.\n");

    /* Tests for proper end of game or continuation behavior when count for 3 different cards in supply pile == 0 */
    G.supplyCount[province] = 12; // Resets supply pile for Province card
    for (i = 0; i < 3; i++)
    {

        G.supplyCount[i] = 0;    // Sets supply pile to 0
        printf("%d different cards now contain empty supply piles.\n", i + 1);

        if (isGameOver(&G) && i == 2)
            printf("Test passed. Correct result of gameover.\n");
        else if (!isGameOver(&G) && i == 2)
            printf("Test failed. Game incorrectly continues.\n");
        else if (isGameOver(&G) && i < 2)
            printf("Test failed. Incorrect result of gameover.\n");
        else
            printf("Test passed. Correct result, game continues.\n");
    }

    /* Prints conclusion of testing result. */
    if(flag == 0)
        printf("All tests passed!\n\n");
    else
       printf("TESTING FAILED!\n\n");

    return 0;
}
