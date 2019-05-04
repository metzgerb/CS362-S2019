/******************************************************************************
* Program Name: unittest1.c
* Description: Runs tests on the ambassador_effect function to validate the
*	number of cards drawn during the function is correct and the number of
*	card returned to Supply is correct (Positive tests)
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

#define TEST_CARD ambassador
#define TEST_CARD_NAME "ambassador"

void testSummary(int pass, int fail);

int main()
{
	int pass = 0, fail = 0; //keeps track of the number of tests that passed and failed
	int newCards = 0;
	int discarded = 1;
	//int actionChange = 0;
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
	for (int h = 1; h < 60; h += 5)
	{
		// copy the game state to a test case
		memcpy(&testG, &G, sizeof(struct gameState));

		//change handcount to different value
		testG.handCount[thisPlayer] = h;

		//fill test hand with curses
		for (int i = 0; i < testG.handCount[thisPlayer]; i++)
		{
			testG.hand[thisPlayer][i] = curse;
		}

		
		choice2 = 0; //choose to return 0 cards
		choice1 = 1; //choose a curse

		//run effect to test
		cardEffect(TEST_CARD, choice1, choice2, choice3, &testG, handpos, &bonus);

		// ----------- POSITIVE TEST: count of cards in hand is changed --------------

		//set expected change values
		newCards = 0;
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

		// ----------- POSITIVE TEST: supply pile is not changed --------------

		//print results (beginning supply count + choice2 (returned count) - number of players - 1
		printf("handcount = %d -- Test supply count -- actual = %d, expected = %d: ", h, testG.supplyCount[testG.hand[thisPlayer][choice1]], G.supplyCount[testG.hand[thisPlayer][choice1]] + choice2 - numPlayers - 1);

		//test oracle to check if test passed or failed
		if (testG.supplyCount[testG.hand[thisPlayer][choice1]] != G.supplyCount[testG.hand[thisPlayer][choice1]] + choice2 - numPlayers - 1)
		{
			printf("FAIL\n");
			fail++;
		}
		else
		{
			printf("PASS\n");
			pass++;
		}

		// ----------- POSITIVE TEST: other players gain a card --------------
		for (int p = 0; p < numPlayers; p++)
		{

			//set discard value (current player discards ambassador, other players gain a card to discard pile)
			discarded = 1;

			//print results
			printf("player = %d -- Test discard count -- actual = %d, expected = %d: ", p, testG.discardCount[p], G.discardCount[p] + discarded);

			//test oracle to check if test passed or failed
			if (testG.discardCount[p] != G.discardCount[p] + discarded)
			{
				printf("FAIL\n");
				fail++;
			}
			else
			{
				printf("PASS\n");
				pass++;
			}
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