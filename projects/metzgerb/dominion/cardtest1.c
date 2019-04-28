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

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1
#define TEST_CARD great_hall
#define TEST_CARD_NAME "great_hall"

void testSummary(int pass, int fail);

int main()
{
	int pass = 0, fail = 0; //keeps track of the number of tests that passed and failed
	int newCards = 0;
	int discarded = 1;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = { adventurer, great_hall, ambassador, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room };

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("TESTING: %s  ----------------------------------------\n", TEST_CARD_NAME);

	// ----------- TEST 1: count of cards in hand is unchanged --------------
	printf("TEST 1: choice1 = 1 = +2 cards\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(TEST_CARD, choice1, choice2, choice3, &testG, handpos, &bonus);

	//set expected change values
	newCards = 1;
	discarded = 1;

	//print results
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	printf("TEST 1 RESULTS: ");
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

	testSummary(pass, fail);

	return 0;
}

void testSummary(int pass, int fail)
{
	printf("RESULTS FOR %s ----------------------------------------\n", TEST_CARD_NAME);
	printf("PASSED: %d\n", pass);
	printf("FAILED: %d\n", fail);
	printf("TOTAL: %d\n", pass + fail);
	printf("END OF UNIT TEST ----------------------------------------\n");
	return;
}