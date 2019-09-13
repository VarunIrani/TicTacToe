#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "AI.hpp"
#include <algorithm>
using namespace sf;
using namespace std;

namespace TTT {
	class GameState : public State {
	public:
		GameState(GameDataRef data);
		void Init();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);
	private:
		void InitGridPieces();
		void CheckAndPlacePiece();
		void CheckPlayerHasWon(int player);
		void Check3PiecesForMatch(int x1, int y1, int x2, int y2, int x3, int y3, int pieceToCheck);
		void PlaceAIPiece();
		GameDataRef _data;
		Sprite _background;
		Sprite _pauseButton;
		Sprite _gridSprite;
		Sprite _gridPieces[3][3];
		int _grid[3][3];
		int _turn;
		int _gameState;
		AI _ai;
	};
}
