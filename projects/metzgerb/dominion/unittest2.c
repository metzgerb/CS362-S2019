/******************************************************************************
* Program Name: unittest1.c
* Description: Runs tests on the great_hall_effect function to validate the
*	number of cards drawn during the function is correct (checking gamestate)
* Author: Brian Metzger (metzgerb@oregonstate.edu)
* Created: 2019-04-28
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
	int newCards = 0;
	int discarded = 1;
	int actionChange = -1;
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

		// ----------- POSITIVE TEST: count of cards in hand is unchanged --------------

		//set expected change values
		newCards = 3;
		discarded = 1;

		//print results
		printf("handcount = %d -- Test hand count -- actual = %d, expected = %d: ", h, testG.handCount[thisPlayer], h + newCards - discarded);

		//test oracle to check if test passed or failed
		if (testG.handCount[thisPlayer] != h + newCards - discarded)
		{
			printf("FAIL\n");
			fail++;
		}
		else
		{
			printf("PASS\n");
			pass++;
		}

		// ----------- POSITIVE TEST: count of actions is increased by 1 --------------
		//print results
		printf("handcount = %d -- Test action count -- actual = %d, expected = %d: ", h, testG.numActions, G.numActions + actionChange);

		//test oracle to check if test passed or failed
		if (testG.numActions != G.numActions + actionChange)
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

		// ----------- POSITIVE TEST: count of cards in hand is unchanged --------------

		//set expected change values
		newCards = 1;
		discarded = 1;

		//print results
		printf("action count = %d -- Test hand count -- actual = %d, expected = %d: ", a, testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);

		//test oracle to check if test passed or failed
		if (testG.handCount[thisPlayer] != G.handCount[thisPlayer] + newCards - discarded)
		{
			printf("FAIL\n");
			fail++;
		}
		else
		{
			printf("PASS\n");
			pass++;
		}

		// ----------- POSITIVE TEST: count of actions is increased by 1 --------------
		//print results
		printf("action count = %d -- Test action count -- actual = %d, expected = %d: ", a, testG.numActions, a + actionChange);

		//test oracle to check if test passed or failed
		if (testG.numActions != a + actionChange)
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