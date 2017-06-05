#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SPFIARGame.h"
#include "SPMiniMax.h"
#include "SPFIARParser.h"
#include "SPMainAux.h"
#include "SPArrayList.h"

#define HISTORY_SIZE (20)

int main() {

	int difficulty = getDifficulty();
	if (difficulty == -1) {
		return 0;
	}

	SPFiarGame* game; 
	game = spFiarGameCreate(HISTORY_SIZE);

	return mainLoop(game, difficulty);
}
