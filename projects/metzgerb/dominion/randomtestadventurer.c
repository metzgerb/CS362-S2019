/******************************************************************************
* Program Name: randomtestadventurer.c
* Description: Runs tests on the adventurer card using random inputs to 
*	validate the number of cards drawn during the function is correct and the 
*	number of buy earned is correct (random testing)
* Author: Brian Metzger (metzgerb@oregonstate.edu)
* Created: 2019-05-13
******************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TEST_CARD adventurer
#define TEST_CARD_NAME "adventurer"

void testSummary(int pass, int fail);

int main()
{
	int pass = 0, fail = 0; //keeps track of the number of tests that passed and failed
	int newCards = 2;
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
	printf("TEST: Testing %s with random deck counts\n\n", TEST_CARD_NAME);

	//test with different sized hands
	for (int i = 0; i < 100; i++)
	{
		// copy the game state to a test case
		memcpy(&testG, &G, sizeof(struct gameState));
	
		//randomize deck size by adding cards
		int deckIncrease = rand() % (MAX_DECK - testG.deckCount[thisPlayer]);
		for (int j = 0; j < deckIncrease; j++)
		{
			//pick random card from supply
			int supplyCard = rand() % 10;

			//gain random card to deck
			gainCard(k[supplyCard], &testG, 1, thisPlayer);
		}

		//store deck count
		int d = testG.deckCount[thisPlayer];

		//run effect to test
		cardEffect(TEST_CARD, choice1, choice2, choice3, &testG, handpos, &bonus);

		// ----------- TEST: count of played cards --------------

		//test oracle to check if test passed or failed
		if (testG.playedCardCount != G.playedCardCount + played)
		{
			//print results only if failed
			printf("deckcount = %d -- Test played count -- actual = %d, expected = %d: FAIL\n", d, testG.playedCardCount, G.playedCardCount + played);
			//printf("FAIL\n");
			fail++;
		}
		else
		{
			//printf("PASS\n");
			pass++;
		}

		// ----------- POSITIVE TEST: hand count is increased by 2 --------------
		

		//test oracle to check if test passed or failed
		if (testG.handCount[thisPlayer] != G.handCount[thisPlayer] + newCards - played)
		{
			//print results only if failed
			printf("deckcount = %d -- Test hand count -- actual = %d, expected = %d: FAIL\n", d, testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - played);
			//printf("FAIL\n");
			fail++;
		}
		else
		{
			//printf("PASS\n");
			pass++;
		}

		printf("\n");
	}

	//print results
	/*printf("TEST 2: Testing %s with various starting action counts\n\n", TEST_CARD_NAME);

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

		// ----------- POSITIVE TEST: hand count is increased by 2 --------------
		//print results
		printf("actioncount = %d -- Test hand count -- actual = %d, expected = %d: ", a, testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - played);

		//test oracle to check if test passed or failed
		if (testG.handCount[thisPlayer] != G.handCount[thisPlayer] + newCards - played)
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
	}*/


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