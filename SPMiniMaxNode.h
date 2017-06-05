#ifndef SPMINIMAXNODE_H_
#define SPMINIMAXNODE_H_

#define HEURISTIC_VALUES (7)

typedef struct {
	int col;
	int score;
	//int id;

} minimax_node;

/**
 * Return the current position evaluation for the given player.
 */
int spMinimaxHeuristic(SPFiarGame* currentGame, char player);

minimax_node* spMinimaxSuggest_rec(SPFiarGame* currentGame, unsigned int maxDepth);

#endif
