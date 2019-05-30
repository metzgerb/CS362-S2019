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

#define TEST_CARD great_hall
#define TEST_CARD_NAME "great_hall"

void testSummary(int pass, int fail);

int main()
{
	int pass = 0, fail = 0; //keeps track of the number of tests that passed and failed
	int newCards = 1;
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
	for (int i = 0; i < 500; i++)
	{
		// copy the game state to a test case
		memcpy(&testG, &G, sizeof(struct gameState));

		//calculate maximum cards in supply for range of gaining cards
		int sum = 0;
		for (int a = 0; a < 27; a++)
		{
			sum += supplyCount(a, &testG);
		}

		//randomize deck size by adding cards
		int deckIncrease = rand() % sum;
		for (int j = 0; j < deckIncrease; j++)
		{
			//pick random card from supply
			int supplyCard = rand() % 27;

			//gain random card to deck
			gainCard(supplyCard, &testG, 1, thisPlayer);
		}

		//store deck count
		int d = testG.deckCount[thisPlayer];

		//run effect to test
		cardEffect(TEST_CARD, choice1, choice2, choice3, &testG, handpos, &bonus);

		// ----------- POSITIVE TEST: count of played cards = 1 --------------

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

		// ----------- POSITIVE TEST: hand count is unchanged --------------


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

		// ----------- POSITIVE TEST: numActions is unchanged --------------

		//test oracle to check if test passed or failed
		if (testG.numActions != G.numActions)
		{
			//print results only if failed
			printf("deckcount = %d -- Test actions -- actual = %d, expected = %d: FAIL\n", d, testG.numActions, G.numActions);
			//printf("FAIL\n");
			fail++;
		}
		else
		{
			//printf("PASS\n");
			pass++;
		}

		// ----------- POSITIVE TEST: numBuys is unchanged --------------

		//test oracle to check if test passed or failed
		if (testG.numBuys != G.numBuys)
		{
			//print results only if failed
			printf("deckcount = %d -- Test Buys -- actual = %d, expected = %d: FAIL\n", d, testG.numBuys, G.numBuys);
			//printf("FAIL\n");
			fail++;
		}
		else
		{
			//printf("PASS\n");
			pass++;
		}

		// ----------- POSITIVE TEST: coins is unchanged --------------

		//test oracle to check if test passed or failed
		if (testG.coins != G.coins)
		{
			//print results only if failed
			printf("deckcount = %d -- Test coins -- actual = %d, expected = %d: FAIL\n", d, testG.coins, G.coins);
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