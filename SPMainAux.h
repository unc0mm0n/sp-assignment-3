#ifndef SPMAINAUX_H_
#define SPMAINAUX_H_

#define MAX_INPUT_SIZE (1024)

#include <stdlib.h>

#include "SPFIARParser.h"
#include "SPFIARGame.h"
#include "SPMiniMax.h"
#include "SPFIARParser.h"

//put auxiliary functions and constants used by the main function here.

/**
 * Read difficutly from user and return it.
 * @return -1 if quit command is given.
 */
int getDifficulty();

/**
 * Get valid command from user for main game loop. Argument validity is checked but the arguments themselves
 * are not.
 *
 * @arg game - SPFiarGame instance to get command for.
 * @return SPCommand of valid command chosen by user.
 */
SPCommand getCommand(SPFiarGame* game);

/**
 * Run the main loop of the game.
 * Calls for commands and act accordingly until quit is called.
 *
 * @arg game - SPFiarGame instance for the loop to play on.
 * @arg difficulty - Difficulty of the game played.
 * @return exit code for the loop.
 */
int mainLoop(SPFiarGame* game,  int difficulty);

/**
 * Play move specified by command if legal, print error message otherwise.
 *
 * @arg game - SPFiarGame instance to play move in.
 * @arg command- SPCommand of type SP_ADD_DISC.
 * @return true if the move was played succesfully.
 */
bool playMove(SPFiarGame* game, SPCommand command);

/**
 * Undo two moves in the game.
 *
 *
 * @arg game - SPFiarGame instance to undo moves in.
 * @return true if undo was successfull.:w
 * 
 */
bool undoMovePair(SPFiarGame* game);

/**
 * Print player command prompt appropriate to the state of the game.
 *
 * @arg game - SPFiarGame instance according to which print the prompt.
 */
void printMovePrompt(SPFiarGame* game);
#endif
