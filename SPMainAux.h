#ifndef SPMAINAUX_H_
#define SPMAINAUX_H_

#define MAX_INPUT_SIZE (1024)

#include "SPFIARParser.h"
#include "SPFIARGame.h"
#include "SPMiniMax.h"
#include "SPFIARParser.h"

//put auxiliary functions and constants used by the main function here.

/**
 * Read difficutly from user and return it.
 * Return -1 if quit command is given.
 */
int getDifficulty();

SPCommand getCommand(SPFiarGame* game);

int mainLoop(SPFiarGame* game,  int difficulty);

void playMove(SPFiarGame* game, SPCommand command);

void undoMovePair(SPFiarGame* game);
#endif
