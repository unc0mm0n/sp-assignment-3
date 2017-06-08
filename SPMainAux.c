

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SPMainAux.h"

int getDifficulty() {
	char *s = (char *) malloc((MAX_INPUT_SIZE + 1) * sizeof(char));
	
	int difficulty = 0;
	while (difficulty < 1 || difficulty > 7) {
		printf("Please enter the difficulty level between [1-7]:\n");

		fgets(s, MAX_INPUT_SIZE, stdin);

		if (spParserIsInt(s)) {
			difficulty = atoi(s);
			if (difficulty < 1 || difficulty > 7) {
				printf("Error: invalid level (should be between 1 to 7)\n");
			}
		} else {
			SPCommand command = spParserPraseLine(s);
			if (command.cmd == SP_QUIT) {
				free (s);
				return -1;
			}

			printf("Error: invalid level (should be between 1 to 7)\n");
		}
	}

	free (s);
	return difficulty;
}

void printMovePrompt(SPFiarGame* game) {
    spFiarGamePrintBoard(game);
    switch (spFiarCheckWinner(game)) {
        case SP_FIAR_GAME_PLAYER_1_SYMBOL:
            printf("Game over: you win\nPlease enter 'quit' to exit or 'restart' to start a new game!\n");
            break;
        case SP_FIAR_GAME_PLAYER_2_SYMBOL:
            printf("Game over: computer wins\nPlease enter 'quit' to exit or 'restart' to start a new game!\n");
            break;
        case SP_FIAR_GAME_TIE_SYMBOL:
            printf("Game over: it's a tie\nPlease enter 'quit' to exit or 'restart' to start a new game!\n");
            break;
        default:
            printf("Please make the next move:\n");
    }
}

SPCommand getCommand(SPFiarGame* game) {
	char *s = (char *) malloc((MAX_INPUT_SIZE + 1) * sizeof(char));

	while (1) {
		
		SPCommand command;

		fgets(s, MAX_INPUT_SIZE, stdin);
		command = spParserPraseLine(s);

		if (command.cmd == SP_INVALID_LINE) {
			printf("Error: invalid command\n");
		} else if (spFiarCheckWinner(game) != SP_FIAR_GAME_NO_WINNER && !(command.cmd == SP_QUIT || command.cmd == SP_RESTART || command.cmd == SP_UNDO_MOVE)){
			printf("Error: the game is over\n");
		} else {
			free (s);
			return command;
		}
	}
	
}

int mainLoop(SPFiarGame* game, int difficulty) {
	SPCommand command;
	int suggestion;
    bool moveSuccess=true;

	while (1) {
		if (game->currentPlayer == SP_FIAR_GAME_PLAYER_1_SYMBOL || spFiarCheckWinner(game) != SP_FIAR_GAME_NO_WINNER) {

            if (moveSuccess) { // print prompt only if user hasn't entered a bad command.
                printMovePrompt(game);
            }

            command = getCommand(game);
			switch(command.cmd) {
				case SP_UNDO_MOVE:
					moveSuccess = undoMovePair(game);
					break;
				
				case SP_ADD_DISC:
					moveSuccess = playMove(game, command);
					break;
				
				case SP_SUGGEST_MOVE:
					suggestion = (spMinimaxSuggestMove(game, difficulty) + 1);
					printf("Suggested move: drop a disc to column %d\n", suggestion);
					break;
				case SP_QUIT:
					return 0;
					break;
				case SP_RESTART:
					spFiarGameClear(game);
					printf("Game restarted!\n");
					difficulty = getDifficulty();
					if (difficulty == -1) {
						return 0;
					}
					break;
				default:
					printf("This shouldn't happen\n");
					break;
			}
		
		}
		else {
			int computerMove;
			computerMove = spMinimaxSuggestMove(game, difficulty);
			printf("Computer move: add disc to column %d\n", (computerMove + 1));
			spFiarGameSetMove(game, computerMove);
		}
	}	
}

bool playMove(SPFiarGame* game, SPCommand command) {
	SP_FIAR_GAME_MESSAGE message;
	if (command.validArg) {
		message = spFiarGameSetMove(game, command.arg - 1);
		if (message == SP_FIAR_GAME_INVALID_ARGUMENT) {
			printf("Error: column number must be in range 1-7\n");
            return false;
		} else if (message == SP_FIAR_GAME_INVALID_MOVE) {
			printf("Error: column %d is full\n", command.arg);
            return false;
		}
	} else {
		printf("Error: column number must be in range 1-7\n");
        return false;
	}
    return true;
}

bool undoMovePair(SPFiarGame* game) {
	SP_FIAR_GAME_MESSAGE message;
	int lastMove;

	lastMove = spArrayListGetLast(game->gameHistory) + 1;
	message = spFiarGameUndoPrevMove(game);
	if (message == SP_FIAR_GAME_NO_HISTORY) {
		printf("Error: cannot undo previous move!\n");
        return false;
	} else {
		printf("Remove disc: remove computer's disc at column %d\n", lastMove);
		lastMove = spArrayListGetLast(game->gameHistory) + 1;
		spFiarGameUndoPrevMove(game);
		printf("Remove disc: remove user's disc at column %d\n", lastMove);
        return true;
	}
}

