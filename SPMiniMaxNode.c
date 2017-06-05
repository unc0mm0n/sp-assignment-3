#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "SPFIARGame.h"
#include "SPMiniMaxNode.h"

const int valueVector[] = {-5, -2, -1, 0,  1, 2, 5};

//int next_id = 0;

int spMinimaxHeuristic(SPFiarGame* currentGame, char player) {
	if (currentGame == NULL) {
		return 0;
	}
	
	char otherPlayer;
	int positionResults[SP_FIAR_GAME_N_DIRECTIONS];
	int results[HEURISTIC_VALUES];

	if (player == SP_FIAR_GAME_PLAYER_1_SYMBOL) { // decide other player
		otherPlayer = SP_FIAR_GAME_PLAYER_2_SYMBOL;
	} else {
		otherPlayer = SP_FIAR_GAME_PLAYER_1_SYMBOL;
	}

	for (int l=0; l < HEURISTIC_VALUES; l++) { // initialize results
		results[l] = 0;
	}

	for (int i=0; i < SP_FIAR_GAME_N_ROWS; i++) { // count tiles
		for (int j=0; j < SP_FIAR_GAME_N_COLUMNS; j++) {
			spFiarGameCharDiffAt(currentGame, i, j, player, otherPlayer, positionResults);
			for (int k=0; k < SP_FIAR_GAME_N_DIRECTIONS; k++) {
				if (positionResults[k] != SP_FIAR_GAME_NO_SPAN) {
					if (positionResults[k] == SP_FIAR_GAME_SPAN) {
						return INT_MAX;
					} else if (positionResults[k] == -SP_FIAR_GAME_SPAN) {
						return INT_MIN;
					}
					if (positionResults[k] != 0) {
						results[positionResults[k] + HEURISTIC_VALUES / 2]++;
					}
				}
			}
		}
	}

	int res = 0;

	for (int m=0; m < HEURISTIC_VALUES; m++) { // calculate product
		res += valueVector[m] * results[m];
	}

	return res;

}

minimax_node* spMinimaxSuggest_rec(SPFiarGame* currentGame, unsigned int maxDepth) {
	int newScore;

	minimax_node* res = (minimax_node *) malloc(sizeof(minimax_node));
	res -> col = 0;
	res -> score = INT_MIN;
	//res->id = next_id;
	//next_id++;

	//if (res->id == 115334) { // debug board
	//	spFiarGamePrintBoard(currentGame);
	//}

	char currentPlayer = currentGame -> currentPlayer;
	
	if (maxDepth == 1) { // base case - end of depth
		for (int i=0; i < SP_FIAR_GAME_N_COLUMNS; i++) {
			if (spFiarGameSetMove(currentGame, i) == SP_FIAR_GAME_INVALID_MOVE) {
				continue;
			}
			newScore = spMinimaxHeuristic(currentGame, currentPlayer);
			if (newScore > res->score) {
				res->col = i;
				res->score = newScore;
			}
			spFiarGameUndoPrevMove(currentGame);
		}
		return res;
	}

	for (int i=0; i < SP_FIAR_GAME_N_COLUMNS; i++) {
		if (spFiarGameSetMove(currentGame, i) == SP_FIAR_GAME_INVALID_MOVE) {
			continue;
		}

		char winner = spFiarCheckWinner(currentGame); // base case - game over
		if (winner == currentPlayer) {
			spFiarGameUndoPrevMove(currentGame);
			res->col = i;
			res->score = INT_MAX;
			return res;
		}

		minimax_node* child_res;
		child_res = spMinimaxSuggest_rec(currentGame, maxDepth-1);
		if (child_res->score == INT_MIN) {
			child_res->score = INT_MAX;
		} else if (child_res->score == INT_MAX) {
			child_res->score = INT_MIN;
		} else {
			child_res->score *= -1;
		}

		if (child_res->score > res->score) {
			res->col = i;
			res->score = child_res->score;
			//res->id = child_res->id;
		}

		free(child_res);
		spFiarGameUndoPrevMove(currentGame);
	}

	return res;

}

