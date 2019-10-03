#include "AI.hpp"
#include <iostream>

namespace TTT {
	AI::AI() {}
	
	int AI::Evaluate(Board b) {
		// Checking for Rows for X or O victory.
		for (int row = 0; row < 3; row++)
		{
			if (b.At(row, 0) == b.At(row, 1) &&
					b.At(row, 1) == b.At(row, 2))
			{
				if (b.At(row, 0) == AI_PIECE)
					return +10;
				else if (b.At(row, 0) == PLAYER_PIECE)
					return -10;
			}
		}
		
		// Checking for Columns for X or O victory.
		for (int col = 0; col < 3; col++)
		{
			if (b.At(0, col) == b.At(1, col) &&
					b.At(1, col) == b.At(2, col))
			{
				if (b.At(0, col) == AI_PIECE)
					return +10;
				
				else if (b.At(0, col) == PLAYER_PIECE)
					return -10;
			}
		}
		
		// Checking for Diagonals for X or O victory.
		if (b.At(0, 0) == b.At(1, 1) && b.At(1, 1) == b.At(2, 2))
		{
			if (b.At(0, 0) == AI_PIECE)
				return +10;
			else if (b.At(0, 0) == PLAYER_PIECE)
				return -10;
		}
		
		if (b.At(0, 2) == b.At(1, 1) && b.At(1, 1) == b.At(2, 0))
		{
			if (b.At(0, 2) == AI_PIECE)
				return +10;
			else if (b.At(0, 2) == PLAYER_PIECE)
				return -10;
		}
		
		// Else if none of them have won then return 0
		return 0;
	}
	
	bool AI::MovesLeft(Board b) {
		for (int i = 0 ; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (b.At(i, j) == EMPTY_PIECE)
					return true;
			}
		}
		return false;
	}
	
	Move AI::FindBestMove(Board board, int player) {
		int score = Evaluate(board);
		if (score == 10)
		{
			return Move(score);
		}
		if (score == -10)
		{
			return Move(score);
		}
		if (MovesLeft(board) == false)
		{
			return Move(0);
		}
		// Traverse all cells, evaluate minimax function for
		// all empty cells. And return the cell with optimal
		// value.
		vector<Move> moves = vector<Move>();
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (board.At(i, j) == EMPTY_PIECE)
				{
					Move move = Move();
					move.x = i;
					move.y = j;
					board.PlacePiece(i, j, player);
					if (player == AI_PIECE)
					{
						move.score = FindBestMove(board, PLAYER_PIECE).score;
					}
					else
					{
						move.score = FindBestMove(board, AI_PIECE).score;
					}
					moves.push_back(move);
					board.PlacePiece(i, j, EMPTY_PIECE);
				}
			}
		}
		
		int bestMove = 0;
		if (player == AI_PIECE)
		{
			int bestScore = -9999;
			for (int i = 0; i < moves.size(); i++)
			{
				if (moves[i].score > bestScore)
				{
					bestMove = i;
					bestScore = moves[i].score;
				}
			}
		}
		else
		{
			int bestScore = 9999;
			for (int i = 0; i < moves.size(); i++)
			{
				if (moves[i].score < bestScore)
				{
					bestMove = i;
					bestScore = moves[i].score;
				}
			}
		}
		return moves[bestMove];
	}
}
