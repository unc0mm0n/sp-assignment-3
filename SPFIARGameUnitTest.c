#include "unit_test_util.h"
#include "SPFIARGame.h"
#include <stdbool.h>

#define HISTORY_SIZE 20

static bool spFiarGameValidMoveTest() {
	SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);
	ASSERT_TRUE(res!=NULL);
	int repeat = SP_FIAR_GAME_N_ROWS;
	while (repeat-- > 0) {
		ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS);

	}
	ASSERT_FALSE(spFiarGameIsValidMove(res, 2));
	ASSERT_TRUE(spFiarGameSetMove(res,2)==SP_FIAR_GAME_INVALID_MOVE);
	spFiarGamePrintBoard(res);
	spFiarGameDestroy(res);
	return true;
}

static bool spFiarGameUndoMoveTest2() {
	SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);
	ASSERT_TRUE(res!=NULL);
	int repeat = 3;
	while (repeat-- > 0) {
		for (int i = 0; i < SP_FIAR_GAME_N_COLUMNS; i++) {
			ASSERT_TRUE(spFiarGameSetMove(res, i) == SP_FIAR_GAME_SUCCESS);
		}
	}
	spFiarGamePrintBoard(res);
	repeat = 20;
	while (repeat-- > 0) {
		ASSERT_TRUE(spFiarGameUndoPrevMove(res) == SP_FIAR_GAME_SUCCESS);
	}
	ASSERT_TRUE(spFiarGameUndoPrevMove(res) == SP_FIAR_GAME_NO_HISTORY);
	spFiarGamePrintBoard(res);
	spFiarGameDestroy(res);
	return true;
}
static bool spFiarGameUndoMoveTest() {
	SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);
	ASSERT_TRUE(res!=NULL);
	int repeat = 2;
	while (repeat-- > 0) {
		for (int i = 0; i < SP_FIAR_GAME_N_COLUMNS; i++) {
			ASSERT_TRUE(spFiarGameSetMove(res, i) == SP_FIAR_GAME_SUCCESS);
		}
	}

	spFiarGamePrintBoard(res);
	printf("Starting Undo\n");
	repeat = 2;
	while (repeat-- > 0) {
		for (int i = 0; i < SP_FIAR_GAME_N_COLUMNS; i++) {
			ASSERT_TRUE(spFiarGameUndoPrevMove(res) == SP_FIAR_GAME_SUCCESS);
		}
	}
	spFiarGamePrintBoard(res);
	spFiarGameDestroy(res);
	return true;
}

static bool spFiarGameSetMoveTest() {
	SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);
	ASSERT_TRUE(res!=NULL);
	int repeat = 2;
	while (repeat-- > 0) {
		for (int i = 0; i < SP_FIAR_GAME_N_COLUMNS; i++) {
			ASSERT_TRUE(spFiarGameSetMove(res, i) == SP_FIAR_GAME_SUCCESS);
		}
	}
	spFiarGamePrintBoard(res);
	spFiarGameDestroy(res);
	return true;
}

static bool spFIARGameBasicTest() {
	SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);
	ASSERT_TRUE(res!=NULL);
	spFiarGameDestroy(res);
	return true;
}

static bool spFIARGameTurnCountTest() {
	SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);
	ASSERT_TRUE(res!=NULL);
	ASSERT_TRUE(spFiarGameTurnCount(res) == 0);
	spFiarGameUndoPrevMove(res);
	ASSERT_TRUE(spFiarGameTurnCount(res) == 0);

	spFiarGameSetMove(res, 0);
	ASSERT_TRUE(spFiarGameTurnCount(res) == 1);
	spFiarGameSetMove(res, -1);
	ASSERT_TRUE(spFiarGameTurnCount(res) == 1);
	spFiarGameUndoPrevMove(res);
	ASSERT_TRUE(spFiarGameTurnCount(res) == 0);

	int repeat = SP_FIAR_GAME_N_ROWS;
	int count = 0;
	while (repeat-- > 0) {
		spFiarGameSetMove(res, 1);
		spFiarGameSetMove(res, 0);
		spFiarGameSetMove(res, 2);
		spFiarGameSetMove(res, 3);
		spFiarGameSetMove(res, 4);
		spFiarGameSetMove(res, 6);
		spFiarGameSetMove(res, 5);
		count+=7;
		ASSERT_TRUE(spFiarGameTurnCount(res) == count);
	}

	spFiarGamePrintBoard(res);
	spFiarGameSetMove(res, 0);
	ASSERT_TRUE(spFiarGameTurnCount(res) == SP_FIAR_GAME_N_ROWS * SP_FIAR_GAME_N_COLUMNS);

	spFiarGameDestroy(res);
	return true;
}

static bool spFIARCheckWinnerTest() {
	SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);
	ASSERT_TRUE(res!=NULL);
	ASSERT_TRUE(spFiarCheckWinner(res) == SP_FIAR_GAME_NO_WINNER);
	spFiarGameUndoPrevMove(res);
	ASSERT_TRUE(spFiarCheckWinner(res) == SP_FIAR_GAME_NO_WINNER);

	spFiarGameSetMove(res, 0);
	ASSERT_TRUE(spFiarCheckWinner(res) == SP_FIAR_GAME_NO_WINNER);
	spFiarGameSetMove(res, 1);
	spFiarGameSetMove(res, 0);
	spFiarGameSetMove(res, 1);
	spFiarGameSetMove(res, 0);
	spFiarGameSetMove(res, 1);
	spFiarGameSetMove(res, 0);
	spFiarGamePrintBoard(res);
	ASSERT_TRUE(spFiarCheckWinner(res) == SP_FIAR_GAME_PLAYER_1_SYMBOL);

	spFiarGameUndoPrevMove(res);
	ASSERT_TRUE(spFiarCheckWinner(res) == SP_FIAR_GAME_NO_WINNER);
	spFiarGameSetMove(res, 2);
	spFiarGameSetMove(res, 1);
	spFiarGamePrintBoard(res);
	ASSERT_TRUE(spFiarCheckWinner(res) == SP_FIAR_GAME_PLAYER_2_SYMBOL);

	spFiarGameClear(res);
	ASSERT_TRUE(spFiarCheckWinner(res) == SP_FIAR_GAME_NO_WINNER);

	int repeat = SP_FIAR_GAME_N_ROWS;
	int count = 0;
	while (repeat-- > 0) {
		ASSERT_TRUE(spFiarCheckWinner(res) == SP_FIAR_GAME_NO_WINNER);
		spFiarGameSetMove(res, 1);
		spFiarGameSetMove(res, 0);
		spFiarGameSetMove(res, 2);
		spFiarGameSetMove(res, 3);
		spFiarGameSetMove(res, 4);
		spFiarGameSetMove(res, 6);
		spFiarGameSetMove(res, 5);
		count+=7;
	}

	spFiarGamePrintBoard(res);
	printf("%c\n", spFiarCheckWinner(res));
	ASSERT_TRUE(spFiarCheckWinner(res) == SP_FIAR_GAME_TIE_SYMBOL);
	spFiarGameSetMove(res, 0);
	ASSERT_TRUE(spFiarCheckWinner(res) == SP_FIAR_GAME_TIE_SYMBOL);

	spFiarGameDestroy(res);
	return true;	
}

static bool spFIARGameCharDiffAtTest() {
	SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);
	ASSERT_TRUE(res!=NULL);

	int repeat = SP_FIAR_GAME_N_ROWS;
	while (repeat-- > 0) {
		spFiarGameSetMove(res, 1);
		spFiarGameSetMove(res, 0);
		spFiarGameSetMove(res, 2);
		spFiarGameSetMove(res, 3);
		spFiarGameSetMove(res, 4);
		spFiarGameSetMove(res, 6);
		spFiarGameSetMove(res, 5);
	}

	int results1[SP_FIAR_GAME_SPAN], results2[SP_FIAR_GAME_SPAN];
	spFiarGamePrintBoard(res);
	for (int i=0; i < SP_FIAR_GAME_N_ROWS; i++) {
		for (int j=0; j < SP_FIAR_GAME_N_COLUMNS; j++) {
			spFiarGameCharDiffAt(res, i, j, SP_FIAR_GAME_PLAYER_1_SYMBOL, SP_FIAR_GAME_PLAYER_2_SYMBOL, results1);
			spFiarGameCharDiffAt(res, i, j, SP_FIAR_GAME_PLAYER_2_SYMBOL, SP_FIAR_GAME_PLAYER_1_SYMBOL, results2);
			for (int k=0; k < SP_FIAR_GAME_SPAN; k++) {
				ASSERT_TRUE(results1[k] == SP_FIAR_GAME_NO_SPAN || results1[k] == -results2[k]);
			}
		}
	}

    spFiarGameCharDiffAt(res, 0, 1, SP_FIAR_GAME_PLAYER_2_SYMBOL, SP_FIAR_GAME_PLAYER_1_SYMBOL, results2);
    
    ASSERT_TRUE(results2[2] == -5);
    ASSERT_TRUE(results2[0] == 0);
    ASSERT_TRUE(results2[1] == -2);
    ASSERT_TRUE(results2[3] == 2);

    spFiarGameClear(res);

    spFiarGameCharDiffAt(res, 0, 1, SP_FIAR_GAME_PLAYER_2_SYMBOL, SP_FIAR_GAME_PLAYER_1_SYMBOL, results2);
    
    ASSERT_TRUE(results2[2] == -5);
    ASSERT_TRUE(results2[0] == 0);
    ASSERT_TRUE(results2[1] == 0);
    ASSERT_TRUE(results2[3] == 0);

    spFiarGameSetMove(res, 1);
    spFiarGameCharDiffAt(res, 0, 1, SP_FIAR_GAME_PLAYER_2_SYMBOL, SP_FIAR_GAME_PLAYER_1_SYMBOL, results2);
    ASSERT_TRUE(results2[2] == -5);
    ASSERT_TRUE(results2[0] == -1);
    ASSERT_TRUE(results2[1] == -1);
    ASSERT_TRUE(results2[3] == -1);

    spFiarGameSetMove(res, 1);
    spFiarGameCharDiffAt(res, 0, 1, SP_FIAR_GAME_PLAYER_2_SYMBOL, SP_FIAR_GAME_PLAYER_1_SYMBOL, results2);
    ASSERT_TRUE(results2[2] == -5);
    ASSERT_TRUE(results2[0] == 0);
    ASSERT_TRUE(results2[1] == -1);
    ASSERT_TRUE(results2[3] == -1);

    spFiarGameSetMove(res, 2);
    spFiarGameCharDiffAt(res, 0, 1, SP_FIAR_GAME_PLAYER_2_SYMBOL, SP_FIAR_GAME_PLAYER_1_SYMBOL, results2);
    ASSERT_TRUE(results2[2] == -5);
    ASSERT_TRUE(results2[0] == 0);
    ASSERT_TRUE(results2[1] == -2);
    ASSERT_TRUE(results2[3] == -1);

    spFiarGameSetMove(res, 2);
    spFiarGameCharDiffAt(res, 0, 1, SP_FIAR_GAME_PLAYER_2_SYMBOL, SP_FIAR_GAME_PLAYER_1_SYMBOL, results2);
    ASSERT_TRUE(results2[2] == -5);
    ASSERT_TRUE(results2[0] == 0);
    ASSERT_TRUE(results2[1] == -2);
    ASSERT_TRUE(results2[3] == 0);

    spFiarGameSetMove(res, 3);
    spFiarGameSetMove(res, 3);
    spFiarGameCharDiffAt(res, 0, 1, SP_FIAR_GAME_PLAYER_2_SYMBOL, SP_FIAR_GAME_PLAYER_1_SYMBOL, results2);
    ASSERT_TRUE(results2[2] == -5);
    ASSERT_TRUE(results2[0] == 0);
    ASSERT_TRUE(results2[1] == -3);
    ASSERT_TRUE(results2[3] == 0);

    spFiarGameSetMove(res, 4);
    spFiarGameCharDiffAt(res, 0, 1, SP_FIAR_GAME_PLAYER_2_SYMBOL, SP_FIAR_GAME_PLAYER_1_SYMBOL, results2);
    ASSERT_TRUE(results2[2] == -5);
    ASSERT_TRUE(results2[0] == 0);
    ASSERT_TRUE(results2[1] == -4);
    ASSERT_TRUE(results2[3] == 0);

    spFiarGamePrintBoard(res);
	spFiarGameDestroy(res);
	return true;	
}

int main() {
	RUN_TEST(spFIARGameBasicTest);
	RUN_TEST(spFiarGameSetMoveTest);
	RUN_TEST(spFiarGameUndoMoveTest);
	RUN_TEST(spFiarGameUndoMoveTest2);
	RUN_TEST(spFiarGameValidMoveTest);
	RUN_TEST(spFIARGameTurnCountTest);
	RUN_TEST(spFIARCheckWinnerTest);
	RUN_TEST(spFIARGameCharDiffAtTest);
	return 0;
}
