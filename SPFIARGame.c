#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "SPFIARGame.h"

SPFiarGame* spFiarGameCreate(int historySize) {
	if (historySize <= 0) {
		return NULL;
	}

	SPArrayList* gameHistory = spArrayListCreate(historySize);
	if (gameHistory == NULL) {
		return NULL;
	}
	SPFiarGame* game = (SPFiarGame*) malloc(sizeof(SPFiarGame));
	if (game == NULL) {
		free(gameHistory);
		return NULL;
	}
	game->gameHistory = gameHistory;

	spFiarGameClear(game);
	return game;
}

SPFiarGame* spFiarGameCopy(SPFiarGame* src) {
	if (src == NULL) {
		return NULL;
	}

	SPFiarGame* game = (SPFiarGame*) malloc(sizeof(SPFiarGame)); // allocate space to the game

	if (game == NULL) {
		return NULL;
	}

	SPArrayList* gameHistory = spArrayListCopy(src->gameHistory);
	if (gameHistory == NULL) { // need a copy of the game history as well (deep copy)
		free(game);
		return NULL;
	}

	memcpy(game, src, sizeof(SPFiarGame)); // overwrite everything with the data from src
	game->gameHistory = gameHistory; // and take the new game history

	return game;

}

void spFiarGameDestroy(SPFiarGame* src) {
	if (src == NULL) {
		return;
	}
	spArrayListDestroy(src->gameHistory);
	free(src);
	return;
}

SP_FIAR_GAME_MESSAGE spFiarGameSetMove(SPFiarGame* src, int col) {
	if ((col <0) || (col >= SP_FIAR_GAME_N_COLUMNS) || (src == NULL)) {
		return SP_FIAR_GAME_INVALID_ARGUMENT;
	}

	if (!spFiarGameIsValidMove(src, col)) {
		return SP_FIAR_GAME_INVALID_MOVE;
	}

	src->gameBoard[src->tops[col]][col] = src->currentPlayer; // set move
	src->tops[col]++; // update tops

	if (src->currentPlayer == SP_FIAR_GAME_PLAYER_1_SYMBOL) { // update current player
		src->currentPlayer = SP_FIAR_GAME_PLAYER_2_SYMBOL;
	} else {
		src->currentPlayer = SP_FIAR_GAME_PLAYER_1_SYMBOL;
	}

	if (spArrayListIsFull(src->gameHistory)) {
		spArrayListRemoveFirst(src->gameHistory);
    }
    if (spArrayListAddLast(src->gameHistory, col) == SP_ARRAY_LIST_FULL) {
    	printf("UNABLE TO ADD %d TO FULL HISTORY\n", col); // This shouldn't happen
    }

	return SP_FIAR_GAME_SUCCESS;
}

bool spFiarGameIsValidMove(SPFiarGame* src, int col) {
	if (src==NULL || spFiarCheckWinner(src) != SP_FIAR_GAME_NO_WINNER) {
		return false; // return false if there is no game of the game is over
	}

	// return true if there is free space.
	return (src->tops[col] < SP_FIAR_GAME_N_ROWS); 
}

SP_FIAR_GAME_MESSAGE spFiarGameUndoPrevMove(SPFiarGame* src) {
	if (src == NULL) {
		return SP_FIAR_GAME_INVALID_ARGUMENT;
	} else if (spArrayListIsEmpty(src->gameHistory)) {
		return SP_FIAR_GAME_NO_HISTORY;
	}

	char lastPlayer;
	if (src->currentPlayer == SP_FIAR_GAME_PLAYER_1_SYMBOL) {
		lastPlayer = SP_FIAR_GAME_PLAYER_2_SYMBOL;
	} else {
		lastPlayer = SP_FIAR_GAME_PLAYER_1_SYMBOL;
	}

	int lastMoveCol = spArrayListGetLast(src->gameHistory);

	src->tops[lastMoveCol]--; // update tops
	src->gameBoard[src->tops[lastMoveCol]][lastMoveCol] = SP_FIAR_GAME_EMPTY_ENTRY; // update board
	src->currentPlayer = lastPlayer; // update current player
	spArrayListRemoveLast(src->gameHistory); // update game history

	return SP_FIAR_GAME_SUCCESS;
}

SP_FIAR_GAME_MESSAGE spFiarGamePrintBoard(SPFiarGame* src) {
	if (src == NULL) {
		return SP_FIAR_GAME_INVALID_ARGUMENT;
	}

	for (int i = SP_FIAR_GAME_N_ROWS - 1; i >= 0; i--) {
		printf("%c", SP_FIAR_GAME_BORDER_SYMBOL);
		for (int j = 0; j < SP_FIAR_GAME_N_COLUMNS; j++) {

			printf(" %c", src->gameBoard[i][j]);
		}
		printf(" %c\n", SP_FIAR_GAME_BORDER_SYMBOL);
	}
	for (int i=0; i < SP_FIAR_GAME_N_COLUMNS * 2 + 3; i++)  {// two borders and one space between each
		printf("%c", SP_FIAR_GAME_FLOOR_SYMBOL);
	}

	// print numbers
	printf("\n  ");
	for (int i=1; i <= SP_FIAR_GAME_N_COLUMNS; i++) {
		printf("%d ", i);
	}
	printf(" \n");

	return SP_FIAR_GAME_SUCCESS;
}

char spFiarGameGetCurrentPlayer(SPFiarGame* src) {
	if (src == NULL) {
		return SP_FIAR_GAME_EMPTY_ENTRY;
	}
	return src->currentPlayer;
}

char spFiarCheckWinner(SPFiarGame* src) {
	int results[SP_FIAR_GAME_N_DIRECTIONS];

	for (int i=0; i < SP_FIAR_GAME_N_ROWS; i++) {
		for (int j=0; j < SP_FIAR_GAME_N_COLUMNS; j++) {
			spFiarGameCharDiffAt(src, i, j, SP_FIAR_GAME_PLAYER_1_SYMBOL, SP_FIAR_GAME_PLAYER_2_SYMBOL, results);
			for (int k=0; k < SP_FIAR_GAME_N_DIRECTIONS; k++) {
				if (results[k] == SP_FIAR_GAME_SPAN) {
					return SP_FIAR_GAME_PLAYER_1_SYMBOL;
				} else if (results[k] == -SP_FIAR_GAME_SPAN) {
					return SP_FIAR_GAME_PLAYER_2_SYMBOL;
				}
			}
		}
	}
	if (spFiarGameTurnCount(src) == SP_FIAR_GAME_N_COLUMNS * SP_FIAR_GAME_N_ROWS) {
		return SP_FIAR_GAME_TIE_SYMBOL;
	}

	return SP_FIAR_GAME_NO_WINNER;
}

SP_FIAR_GAME_MESSAGE spFiarGameClear(SPFiarGame* src) {
	if (src == NULL || src -> gameHistory == NULL) {
		return SP_FIAR_GAME_INVALID_ARGUMENT;
	}

	for (int i = 0; i < SP_FIAR_GAME_N_COLUMNS; i++) { // initialize board
		for (int j = 0; j < SP_FIAR_GAME_N_ROWS; j++) {
			src->gameBoard[j][i] = SP_FIAR_GAME_EMPTY_ENTRY;
		}

		src->tops[i] = 0; // initilize tops
	}

	src->currentPlayer = SP_FIAR_GAME_PLAYER_1_SYMBOL; // initialize player;

	spArrayListClear(src->gameHistory);

	return SP_FIAR_GAME_SUCCESS;
}

void spFiarGameCharDiffAt(SPFiarGame* game, int row, int col, char posplayer, char negplayer, int* results) {
	if (game == NULL) {
		return;
	}

	int resultIndex = 0;

	// check vertical
	if (row + SP_FIAR_GAME_SPAN - 1 < SP_FIAR_GAME_N_ROWS) {
		results[resultIndex] = 0;
		for (int i = row; i <= row + SP_FIAR_GAME_SPAN - 1; i++) {
			if (game->gameBoard[i][col] == posplayer) {
				results[resultIndex]++;
			} else if (game->gameBoard[i][col] == negplayer) {
				results[resultIndex]--;
			}
		}
	} else {
		results[resultIndex] = SP_FIAR_GAME_NO_SPAN;
	}

	resultIndex++;

	// check horizontal
	if (col + SP_FIAR_GAME_SPAN - 1 < SP_FIAR_GAME_N_COLUMNS) {
		results[resultIndex] = 0;
		for (int i = col; i <= col + SP_FIAR_GAME_SPAN - 1; i++) {
			if (game->gameBoard[row][i] == posplayer) {
				results[resultIndex]++;
			} else if (game->gameBoard[row][i] == negplayer) {
				results[resultIndex]--;
			}
		}
	} else {
		results[resultIndex] = SP_FIAR_GAME_NO_SPAN;
	}

	resultIndex++;

	// check diagonal right-down
	if (row - SP_FIAR_GAME_SPAN + 1 >= 0 && col + SP_FIAR_GAME_SPAN - 1 < SP_FIAR_GAME_N_COLUMNS) {
		results[resultIndex] = 0;
		for (int i = 0; i <= SP_FIAR_GAME_SPAN - 1; i++) {
			if (game->gameBoard[row - i][col + i] == posplayer) {
				results[resultIndex]++;
			} else if (game->gameBoard[row - i][col + i] == negplayer) {
				results[resultIndex]--;
			}
		}  
	} else {
		results[resultIndex] = SP_FIAR_GAME_NO_SPAN;
	}

	resultIndex++;

	// check diagonal right-up
	if (row + SP_FIAR_GAME_SPAN - 1 < SP_FIAR_GAME_N_ROWS && col + SP_FIAR_GAME_SPAN - 1 < SP_FIAR_GAME_N_COLUMNS) {
		results[resultIndex] = 0;
		for (int i = 0; i <=  SP_FIAR_GAME_SPAN - 1; i++) {
			if (game->gameBoard[row + i][col + i] == posplayer) {
				results[resultIndex]++;
			} else if (game->gameBoard[row + i][col + i] == negplayer) {
				results[resultIndex]--;
			}
		} 
	} else {
		results[resultIndex] = SP_FIAR_GAME_NO_SPAN;
	}
}

int spFiarGameTurnCount(SPFiarGame* game) {
	if (game == NULL) {
		return -1;
	}
	int sum = 0;
	for (int i=0; i < SP_FIAR_GAME_N_COLUMNS; i++) {
		sum += game->tops[i];
	}
	return sum;
}
