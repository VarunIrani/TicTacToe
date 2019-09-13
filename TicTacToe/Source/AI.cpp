#include "AI.hpp"
#include <iostream>

namespace TTT {
	AI::AI() {}
	
	pair<int, int> AI::findBestMove(int b[3][3]) {
		int bestVal = -1000;
		pair<int, int> bestMove;
		bestMove.first = -1;
		bestMove.second = -1;
		// Traverse all cells, evaluate minimax function for
		// all empty cells. And return the cell with optimal
		// value.
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (b[i][j] == EMPTY_PIECE)
				{
					b[i][j] = O_PIECE;
					int moveValue = minimax(b, 0, false);
					b[i][j] = EMPTY_PIECE;
					if (moveValue > bestVal)
					{
						bestMove.first = j;
						bestMove.second = i;
						bestVal = moveValue;
					}
				}
			}
		}
		return bestMove;
	}
	
	int AI::movesLeft(int b[3][3]) {
		int moveCount;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (b[i][j] == EMPTY_PIECE)
					++moveCount;
			}
		}
		return moveCount;
	}
	
	bool AI::isWin(int player, int b[3][3]) {
		int win = 3 * player;
		return ((b[0][0] + b[0][1] + b[0][2] == win) ||
						(b[1][0] + b[1][1] + b[1][2] == win) ||
						(b[2][0] + b[2][1] + b[2][2] == win) ||
						(b[0][0] + b[1][0] + b[2][0] == win) ||
						(b[0][1] + b[1][1] + b[2][1] == win) ||
						(b[0][2] + b[1][2] + b[2][2] == win) ||
						(b[0][0] + b[1][1] + b[2][2] == win) ||
						(b[2][0] + b[1][1] + b[0][2] == win));
	}
	
	int AI::minimax(int b[3][3], int depth, bool isMax) {
		if (isWin(AI_PIECE, b)) {
			return 10;
		}
		if(isWin(PLAYER_PIECE, b)) {
			return -10;
		}
		if (movesLeft(b) == 0) {
			return 0;
		}
		
		if (isMax)
		{
			int best = -1000;
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					if (b[i][j] == EMPTY_PIECE)
					{
						b[i][j] = O_PIECE;
						best = max(best, minimax(b, depth + 1, false));
						b[i][j] = EMPTY_PIECE;
					}
				}
			}
			return best;
		}
		else
		{
			int best = 1000;
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					if (b[i][j] == EMPTY_PIECE)
					{
						b[i][j] = X_PIECE;
						best = min(best, minimax(b, depth + 1, true));
						b[i][j] = EMPTY_PIECE;
					}
				}
			}
			return best;
		}
	}
}
