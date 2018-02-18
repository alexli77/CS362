/*******************************************************************************
* Author: Michael S. Lewis                                                     *
* Date: 2/10/2018                                                              *
* Description: randomtestadventurer.c implements a random test of the          *
*              Adventurer card for dominion.c.                                 *
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

#define CARD_TEST "Adventurer"
#define MINIMUM 3 // Provides a minimum number of cards for the deck and active hand.
#define ITERATIONS 10000

/* Global variables. */
int fail_count_cardEffect = 0;    // Counts failure instances for cardEffect().
int fail_count_shuffle = 0;       // Counts failure instances for shuffle().
int fail_count_drawCard = 0;      // Counts failure instances for drawCard().
int fail_count_deckHandCount = 0; // Counts failure instances for deckHandCount().
int fail_count_treasureCount = 0; // Counts failure instances for treasureCount().

/* Function declarations. */
void testAdventurer(int p, struct gameState *post);

int main ()
{
    printf("Performing random tests of %s card\n", CARD_TEST);

    int i, n;               // Loop counters.
    int player;             // Tracks current player number.
    struct gameState G;     // Initializes gameState.
    int treasureCount;      // Counts number of treasures.
    int treasures[] = {copper, silver, gold};   // Stores random values of treasures.

    srand(time(NULL));      // Provides random seed from system time.

    /* Initializes gameState to a random value. Referenced from testDrawCard.c. */
    for (n = 0; n < ITERATIONS; n++)
    {
        for (i = 0; i < sizeof(struct gameState); i++)
        {
            ((char*)&G)[i] = floor(Random() * 256); // Provides random values for initial gameState.
        }
        /* Chooses random values for player number and treasures. */
        player = floor(Random() * MAX_PLAYERS);
        G.deckCount[player] = floor(Random() * ((MAX_DECK - MINIMUM) + 1) + MINIMUM);
        treasureCount = floor(Random() * ((G.deckCount[player] - MINIMUM) + 1) + MINIMUM);

        /* Places a minimum of 3 treasure cards in the deck. */
        for (i = 0; i < treasureCount; i++)
        {
            G.deck[player][i] = treasures[rand() % 3];
        }
        G.discardCount[player] = 0;
        G.handCount[player] = floor(Random() * ((MAX_HAND - MINIMUM) + 1) + MINIMUM);
        G.whoseTurn = player;

        /* Calls the test function for the FUT. */
        testAdventurer(player, &G);
    }

    /* Counts total number of failures for all tests. */
    int totalFailCount = fail_count_cardEffect + fail_count_drawCard + fail_count_shuffle +
                    fail_count_deckHandCount + fail_count_treasureCount;

    printf("\nTest Summary:\n");

    if (totalFailCount == 0)
    {
        printf ("\nAll random tests passed!\n\n");
        printf("Results:\n");
        printf("Testing of shuffle() passed on %d total iterations.\n", ITERATIONS);
        printf("Testing of drawCard() passed on %d total iterations.\n", ITERATIONS);
        printf("Testing of cardEffect() passed on %d total iterations.\n", ITERATIONS);
        printf("The correct treasure count was returned as expected\nin %d instances.\n", ITERATIONS);
        printf("The correct hand, deck, and discard pile count was returned\nas expected in %d instances.\n", ITERATIONS);
        printf("\n");
    }
    else
    {
        printf("\nTESTING FAILED!\n\n");
        printf("Results:\n");
        if (fail_count_shuffle > 0)
            printf("Testing of shuffle() failed on %d total iterations.\n", fail_count_shuffle);
        else
            printf("Testing of shuffle() passed on %d total iterations.\n", ITERATIONS);
        if (fail_count_drawCard > 0)
            printf("Testing of drawCard() failed on %d\n total iterations.\n", fail_count_drawCard);
        else
            printf("Testing of drawCard() passed on %d total iterations.\n", ITERATIONS);
        if (fail_count_cardEffect > 0)
            printf("Testing of cardEffect() failed on %d total iterations.\n", fail_count_cardEffect);
        else
            printf("Testing of cardEffect() passed on %d total iterations.\n", ITERATIONS);
        if (fail_count_treasureCount > 0)
            printf("An incorrect treasure count was returned in %d instances.\n", fail_count_treasureCount);
        else
            printf("The correct treasure count was returned as expected\nin %d instances.\n", ITERATIONS);
        if (fail_count_deckHandCount > 0)
            printf("An incorrect hand, deck, or discard pile count was\nreturned in %d instances.\n", fail_count_deckHandCount);
        else
            printf("The correct hand, deck, and discard pile count was\nreturned as expected in %d instances.\n", ITERATIONS);
        printf("\n");
    }
    return 0;
}


/*******************************************************************************
 * Name: void testAdventurer(int p, struct gameState *post)
 * Description: Tests the Adventurer card.
 * Arguments: An int representing the player number, and a struct gameState
 *            containing the state of the current game.
 *
 * References the checkDrawCard() function from testDrawCard.c
 *******************************************************************************/
void testAdventurer(int p, struct gameState *post)
{
    int postTreasureCount = 0;  // Actual treasure count results returned from testing.
    int preTreasureCount = 0;   // Expected treasure count results returned from testing.
    int tempHand[MAX_HAND];     // Tracks current hand under test.
    int treasureDrawn = 0;      // Counts number of treasures drawn.
    struct gameState pre;   // Allows for manipulation of the gameState during test.
    int cardDrawn;          // Tracks card drawn from deck.
    int card;               // Identifies current card under inspection.
    int bonus = 0;          // Counts value of bonus.
    int r;                  // Stores result of cardEffect().
    int s;                  // Stores result of shuffle().
    int t;                  // Stores result of drawCard().
    int i;                  // Loop counter.
    int z = 0;              // Counts active player's played cards.

    /* Sets up initial gameState prior to manipulation during test. */
    memcpy(&pre, post, sizeof(struct gameState));

    /* Invokes and stores the adventurer case from cardEffect. */
    r = cardEffect(adventurer, 0, 0, 0, post, 0, &bonus);

    /* Tests cardEffect() for failure. */
    if (r)
    {
        fail_count_cardEffect++;
    }
    /* Exercises behaviors of the Adventure card. */
    while(treasureDrawn < 2)
    {
        if (pre.deckCount[p] < 1)
        {
        /* Shuffles discard pile in case of empty deck. */
            s = shuffle(p, &pre);
            /* Tests for failure of shuffle(). */
            if (s == -1 && pre.deckCount[p] >= 1)   
            {
                fail_count_shuffle++;
            }
        }

        /* Tests for failure of drawcard. */
        t = drawCard(p, &pre);
        if (t == -1 && pre.deckCount[p] != 0)
        {
            fail_count_drawCard++;
        }

        /* Tests if last card drawn is a treasure. */
        cardDrawn = pre.hand[p][pre.handCount[p] - 1];
        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
            treasureDrawn++;    // Increments treasureDrawn if treasure.
        else{                   // Removes last card drawn if not treasure.
            tempHand[z] = cardDrawn;
            pre.handCount[p]--; // Decrements remaining cards in handCount to test.
            z++;    // Increments tempHand count of tested cards.
        }
    }

    /* Places active player's played cards into discard pile. */
    while(z - 1 >= 0)
    {
        pre.discard[p][pre.discardCount[p]++] = tempHand[z - 1];
        z = z - 1;  // Decrements counter.
    }
    /* Counts actual (post) number of treasures. */
    for (i = 0; i < post->handCount[p]; i++)
    {
        card = post->hand[p][i];
        if (card == copper || card == silver || card == gold)
        {
            postTreasureCount++;
        }
    }
    /* Counts expected (pre) number of treasures. */
    for (i = 0; i < pre.handCount[p]; i++)
    {
        card = pre.hand[p][i];
        if (card == copper || card == silver || card == gold)
        {
            preTreasureCount++;
        }
    }
    /* Tests if resulting treasure count matches expected treasure count. */
    if (postTreasureCount != preTreasureCount)
    {
        fail_count_treasureCount++;
    }

    /* Counts expected hand, deck, and discard pile. */
    int postHandCount = post->handCount[p];
    int postDeckCount = post->deckCount[p];
    int postDiscardCount = post->discardCount[p];

    /* Counts actual hand, deck, and discard pile. */ 
    int preHandCount = pre.handCount[p];
    int preDeckCount = pre.deckCount[p];
    int preDiscardCount = pre.discardCount[p];

    /* Tests if expected values match actual values for hand, deck, and discard pile. */
    if (!(postHandCount == preHandCount && postDeckCount == preDeckCount && postDiscardCount == preDiscardCount))
    {
        fail_count_deckHandCount++;
    }
}