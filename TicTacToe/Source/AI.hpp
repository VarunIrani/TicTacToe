#pragma once
#include <algorithm>
#include "DEFINITIONS.hpp"
#include <array>
#include <vector>
using namespace std;

namespace TTT {
	class AI {
	public:
		AI();
		Move FindBestMove(Board board, int player);
	private:
		int Evaluate(Board b);
		bool MovesLeft(Board b);
	};
}
