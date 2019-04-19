#ifndef _DOMINION_HELPERS_H
#define _DOMINION_HELPERS_H

#include "dominion.h"

int drawCard(int player, struct gameState *state);
int updateCoins(int player, struct gameState *state, int bonus);
int discardCard(int handPos, int currentPlayer, struct gameState *state, 
		int trashFlag);
int gainCard(int supplyPos, struct gameState *state, int toFlag, int player);
int getCost(int cardNumber);
int cardEffect(int card, int choice1, int choice2, int choice3, 
	       struct gameState *state, int handPos, int *bonus);

//refactored card effects
int smithy_effect(int currentPlayer, struct gameState* state, int handPos);
int adventurer_effect(int currentPlayer, struct gameState* state);
int great_hall_effect(int currentPlayer, struct gameState* state, int handPos);
int ambassador_effect(int choice1, int choice2, int currentPlayer, struct gameState* state, int handPos);
int sea_hag_effect(int currentPlayer, struct gameState* state);

#endif
