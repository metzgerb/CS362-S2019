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

#define TEST_CARD great_hall
#define TEST_CARD_NAME "great_hall"

void testSummary(int pass, int fail);

int main()
{
	int pass = 0, fail = 0; //keeps track of the number of tests that passed and failed
	int newCards = 0;
	int discarded = 1;
	int actionChange = 1;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = { adventurer, great_hall, ambassador, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room };
	
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	//test with different sized hands
	for (int h = 1; h < 60; h += 7)
	{
		// copy the game state to a test case
		memcpy(&testG, &G, sizeof(struct gameState));
		cardEffect(TEST_CARD, choice1, choice2, choice3, &testG, handpos, &bonus);

		//change handcount to different value
		G.handCount[thisPlayer] = h;

		// ----------- POSITIVE TEST: count of cards in hand is unchanged --------------
		
		//set expected change values
		newCards = 1;
		discarded = 1;

		//print results
		printf("Test hand count = %d, expected = %d: ", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);

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
		printf("Test hand count = %d, expected = %d: ", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);

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