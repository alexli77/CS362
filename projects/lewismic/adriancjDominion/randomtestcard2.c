/*******************************************************************************
* Author: Michael S. Lewis                                                     *
* Date: 2/10/2018                                                              *
* Description: randomtestcard2.c implements a random test of the Smithy card   *
*              for dominion.c.                                                 *
*                                                                              *
* References the checkDrawCard() function from testDrawCard.c                  *
********************************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define CARD_TEST "Smithy"
#define ITERATIONS 10000

/* Global variables. */
int fail_count_cardEffect = 0;        // Counts failure instances for cardEffect().
int fail_count_discardCard = 0;       // Counts failure instances for discardCard().
int fail_count_drawCard = 0;          // Counts failure instances for drawCard().
int fail_count_deckHandCount = 0;     // Counts failure instances for deckHandCount().

/* Function declarations. */
void testSmithy(int p, struct gameState *post);

int main ()
{
    printf("Performing random tests of %s card\n", CARD_TEST);

    int i, n;           // Loop counters.
    int player;         // Tracks current player number.
    struct gameState G; // Initializes gameState.

    srand(time(NULL));  // Provides random seed from system time.

    /* Initializes gameState to a random value. Referenced from testDrawCard.c. */
    for (n = 0; n < ITERATIONS; n++)
    {
        for (i = 0; i < sizeof(struct gameState); i++)
        {
            ((char*)&G)[i] = floor(Random() * 256); // Provides random values for initial gameState.
        }
        /* Chooses random values for player number and deck, hand, and discard pile counts. */
        player = floor(Random() * MAX_PLAYERS);
        G.deckCount[player] = floor(Random() * MAX_DECK);
        G.handCount[player] = floor(Random() * MAX_HAND);
        G.discardCount[player] = floor(Random() * MAX_DECK);
        G.playedCardCount = floor(Random() * (MAX_DECK - 1));
        G.whoseTurn = player;

        /* Calls the test function for the FUT. */
        testSmithy(player, &G);
    }

    /* Counts total number of failures for all tests. */
    int totalFailCount = fail_count_cardEffect + fail_count_discardCard +
                        fail_count_drawCard + fail_count_deckHandCount;

    printf("\nTest Summary:\n");

    if (totalFailCount == 0) {
        printf ("\nAll random tests passed!\n\n");
        printf("Results:\n");
        printf("Testing of drawCard() passed on %d total iterations.\n", ITERATIONS);
        printf("Testing of cardEffect() passed on %d total iterations.\n", ITERATIONS);
        printf("Testing of discardCard() passed on %d total iterations.\n", ITERATIONS);
        printf("The correct hand, deck, and discard pile count was returned\nas expected in %d instances.\n", ITERATIONS);
        printf("\n");
    }
    else {
        printf ("\nTESTING FAILED!\n\n");
        printf("Results:\n");
        if (fail_count_drawCard > 0)
            printf("Testing of drawCard() failed on %d total iterations.\n", fail_count_drawCard);
        else
            printf("Testing of drawCard() passed on %d total iterations.\n", ITERATIONS);
        if (fail_count_cardEffect > 0)
            printf("Testing of cardEffect() failed on %d total iterations.\n", fail_count_cardEffect);
        else
            printf("Testing of cardEffect() passed on %d total iterations.\n", ITERATIONS);
        if (fail_count_discardCard > 0)
            printf("Testing of discardCard() failed on %d total iterations.\n", fail_count_discardCard);
        else
            printf("Testing of discardCard() passed on %d total iterations.\n", ITERATIONS);
        if (fail_count_deckHandCount > 0)
            printf("An incorrect hand, deck, or discard pile count was\nreturned in %d instances.\n", fail_count_deckHandCount);
        else
            printf("The correct hand, deck, and discard pile count was\nreturned as expected in %d instances.\n", ITERATIONS);
        printf("\n");
    }
    return 0;
}


/*******************************************************************************
 * Name: void testSmithy(int p, struct gameState *post)
 * Description: Tests the Smithy card.
 * Arguments: An int representing the player number, and a struct gameState
 *            containing the state of the current game.
 *
 * References the checkDrawCard() function from testDrawCard.c
 *******************************************************************************/
void testSmithy(int p, struct gameState *post)
{
    struct gameState pre;   // Allows for manipulation of the gameState during test.
    int bonus = 0;          // Counts value of bonus.
    int r;                  // Stores result of cardEffect().
    int s;                  // Stores result of first drawCard().
    int t;                  // Stores result of second drawCard().
    int u;                  // Stores result of third drawCard().
    int v;                  // Stores result of discardCard().

    /* Sets up initial gameState prior to manipulation during test. */
    memcpy(&pre, post, sizeof(struct gameState));

    /* Invokes and stores the smithy case from cardEffect. */
    r = cardEffect(smithy, 0, 0, 0, post, 0, &bonus);

    /* Draws 3 cards, per the Smithy specification. */
    s = drawCard(p, &pre);
    t = drawCard(p, &pre);
    u = drawCard(p, &pre);

    /* Places used Smithy card in the discard pile. */
    v = discardCard(0, p, &pre, 0);

    /* Counts expected hand and deck. */
    int postHandCount = post->handCount[p];
    int postDeckCount = post->deckCount[p];
    int postDiscardCount = post->discardCount[p];

    /* Counts actual hand and deck. */ 
    int preHandCount = pre.handCount[p];
    int preDeckCount = pre.deckCount[p];
    int preDiscardCount = pre.discardCount[p];

    /* Tests for failure of first drawcard. */
    if (s == -1 && pre.deckCount[p] != 0)
    {
        fail_count_drawCard++;
    }
    /* Tests for failure of second drawcard. */
    if (t == -1 && pre.deckCount[p] != 0)
    {
        fail_count_drawCard++;
    }
    /* Tests for failure of third drawcard. */
    if (u == -1 && pre.deckCount[p] != 0)
    {
        fail_count_drawCard++;
    }

    /* Tests cardEffect() and discardCard() for failure. */
    if (!(r == 0 && v == 0))
    {
        if (r)  // Tests result of cardEffect().
        {
            fail_count_cardEffect++;
        }
        if (v)  // Tests result of discardCard().
        {
            fail_count_discardCard++;
        }
    }

    /* Tests if expected values match actual values for hand, deck, and discard pile. */
    if (!(postHandCount == preHandCount && postDeckCount == preDeckCount && postDiscardCount == preDiscardCount))
    {
        fail_count_deckHandCount++;
    }
}