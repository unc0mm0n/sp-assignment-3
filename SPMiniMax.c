#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "SPMiniMax.h"
#include "SPMiniMaxNode.h"
#include "SPFIARGame.h"

int spMinimaxSuggestMove(SPFiarGame* currentGame,
		unsigned int maxDepth) {

	SPFiarGame* gameCopy = spFiarGameCopy(currentGame);
	minimax_node* res;

	res = spMinimaxSuggest_rec(gameCopy, maxDepth);
	int col = res ->col;
	free(res);
	spFiarGameDestroy(gameCopy);
	return col;
}