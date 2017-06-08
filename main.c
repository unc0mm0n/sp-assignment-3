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
        printf("Exiting...\n");
		return 0;
	}

	SPFiarGame* game; 
	game = spFiarGameCreate(HISTORY_SIZE);

    if (game == NULL) {
        printf("Error: malloc has failed\n");
        return 1;
    }
	int ec = mainLoop(game, difficulty);
    
    printf("Exiting...\n");
    spFiarGameDestroy(game);
    return ec;
}
