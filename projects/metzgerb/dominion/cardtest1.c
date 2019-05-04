/******************************************************************************
* Program Name: cardtest1.c
* Description: Runs tests on the smithy card to validate the
*	number of cards played during the function is correct and the remaining 
*	deck count is correct (Positive tests)
* Author: Brian Metzger (metzgerb@oregonstate.edu)
* Created: 2019-05-04
******************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TEST_CARD smithy
#define TEST_CARD_NAME "smithy"

void testSummary(int pass, int fail);

int main()
{
	int pass = 0, fail = 0; //keeps track of the number of tests that passed and failed
	int newCards = 3;
	int played = 1;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = { adventurer, great_hall, ambassador, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room };

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	//print results
	printf("TEST 1: Testing %s with various starting hand counts\n\n", TEST_CARD_NAME);

	//test with different sized hands
	for (int h = 1; h < 60; h += 6)
	{
		// copy the game state to a test case
		memcpy(&testG, &G, sizeof(struct gameState));

		//change handcount to different value
		testG.handCount[thisPlayer] = h;

		//run effect to test
		cardEffect(TEST_CARD, choice1, choice2, choice3, &testG, handpos, &bonus);

		// ----------- POSITIVE TEST: count of played cards --------------

		//print results
		printf("handcount = %d -- Test played count -- actual = %d, expected = %d: ", h, testG.playedCardCount, G.playedCardCount + played);

		//test oracle to check if test passed or failed
		if (testG.playedCardCount != G.playedCardCount + played)
		{
			printf("FAIL\n");
			fail++;
		}
		else
		{
			printf("PASS\n");
			pass++;
		}

		// ----------- POSITIVE TEST: deck count is decreased by 3 --------------
		//print results
		printf("handcount = %d -- Test deck count -- actual = %d, expected = %d: ", h, testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards);

		//test oracle to check if test passed or failed
		if (testG.deckCount[thisPlayer] != G.deckCount[thisPlayer] - newCards)
		{
			printf("FAIL\n");
			fail++;
		}
		else
		{
			printf("PASS\n");
			pass++;
		}

		printf("\n");
	}

	//print results
	printf("TEST 2: Testing %s with various starting action counts\n\n", TEST_CARD_NAME);

	//test with different number of starting actions
	for (int a = 1; a < 35; a += 4)
	{
		// copy the game state to a test case
		memcpy(&testG, &G, sizeof(struct gameState));

		//change handcount to different value
		testG.numActions = a;

		//run effect to test
		cardEffect(TEST_CARD, choice1, choice2, choice3, &testG, handpos, &bonus);

		// ----------- POSITIVE TEST: count of played cards --------------

		//print results
		printf("actioncount = %d -- Test played count -- actual = %d, expected = %d: ", a, testG.playedCardCount, G.playedCardCount + played);

		//test oracle to check if test passed or failed
		if (testG.playedCardCount != G.playedCardCount + played)
		{
			printf("FAIL\n");
			fail++;
		}
		else
		{
			printf("PASS\n");
			pass++;
		}

		// ----------- POSITIVE TEST: deck count is decreased by 3 --------------
		//print results
		printf("actioncount = %d -- Test deck count -- actual = %d, expected = %d: ", a, testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards);

		//test oracle to check if test passed or failed
		if (testG.deckCount[thisPlayer] != G.deckCount[thisPlayer] - newCards)
		{
			printf("FAIL\n");
			fail++;
		}
		else
		{
			printf("PASS\n");
			pass++;
		}

		printf("\n");
	}


	//output test results
	testSummary(pass, fail);

	return 0;
}

void testSummary(int pass, int fail)
{
	printf("\nTOTAL RESULTS FOR %s\n", TEST_CARD_NAME);
	printf("PASSED: %d\n", pass);
	printf("FAILED: %d\n", fail);
	printf("TOTAL: %d\n", pass + fail);
	printf("END OF UNIT TEST\n");
	return;
}