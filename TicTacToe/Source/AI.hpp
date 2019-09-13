#pragma once
#include <algorithm>
#include "DEFINITIONS.hpp"
#include <array>
using namespace std;

namespace TTT {
	class AI {
	public:
		AI();
		pair<int, int> findBestMove(int b[3][3]);
	private:
		int minimax(int b[3][3], int depth, bool isMax);
		bool isWin(int player, int b[3][3]);
		int movesLeft(int b[3][3]);
	};
}
