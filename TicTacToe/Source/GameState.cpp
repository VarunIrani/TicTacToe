#include <sstream>
#include "GameState.hpp"
#include "MainMenuState.hpp"
#include "DEFINITIONS.hpp"
#include "PauseState.hpp"
#include "GameOverState.hpp"
#include <iostream>

namespace TTT {
	GameState::GameState(GameDataRef data) : _data(data) {}
	
	void GameState::Init() {
		_gameState = STATE_PLAYING;
		_turn = PLAYER_PIECE;
		_ai = AI();
		
		_background.setTexture(this->_data->assets.GetTexture("Main Menu Background"));
		
		this->_data->assets.LoadTexture("Grid Sprite", GRID_SPRITE_PATH);
		this->_data->assets.LoadTexture("Draw Grid Sprite", DRAW_GRID_SPRITE_PATH);
		this->_data->assets.LoadTexture("X Piece Sprite", X_PIECE_PATH);
		this->_data->assets.LoadTexture("O Piece Sprite", O_PIECE_PATH);
		this->_data->assets.LoadTexture("X Win Sprite", X_WIN_PATH);
		this->_data->assets.LoadTexture("O Win Sprite", O_WIN_PATH);
		
		_gridSprite.setTexture(this->_data->assets.GetTexture("Grid Sprite"));
		
		this->_data->assets.LoadTexture("Pause Button", PAUSE_BUTTON);
		_pauseButton.setTexture(this->_data->assets.GetTexture("Pause Button"));
		_pauseButton.setPosition(this->_data->window.getSize().x - _pauseButton.getLocalBounds().width, _pauseButton.getPosition().y);
		
		_gridSprite.setPosition((SCREEN_WIDTH / 2) - (_gridSprite.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (_gridSprite.getGlobalBounds().height / 2));
		InitGridPieces();
		
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				_grid[i][j] = EMPTY_PIECE;
	}
	
	void GameState::HandleInput() {
		Event event;
		while (this->_data->window.pollEvent(event)) {
			if (Event::Closed == event.type) {
				this->_data->window.close();
			}
			if (this->_data->input.IsSpriteClicked(this->_pauseButton, Mouse::Left, this->_data->window)) {
				this->_data->machine.AddState(StateRef(new PauseState(this->_data)), false);
			} else if (this->_data->input.IsSpriteClicked(this->_gridSprite, Mouse::Left, this->_data->window)){
				if (STATE_PLAYING == _gameState) {
					this->CheckAndPlacePiece();
				}
			}
		}
	}
	
	void GameState::Update(float dt) {
//		if (STATE_PLAYING == _gameState && _turn == AI_PIECE) {
//			this->PlaceAIPiece();
//		}
	}
	
	void GameState::Draw(float dt) {
		this->_data->window.clear();
		this->_data->window.draw(this->_background);
		this->_data->window.draw(this->_pauseButton);
		this->_data->window.draw(this->_gridSprite);
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				this->_data->window.draw(this->_gridPieces[i][j]);
			}
		}
		this->_data->window.display();
	}
	
	void GameState::InitGridPieces() {
		Vector2u tempSpriteSize = this->_data->assets.GetTexture("X Piece Sprite").getSize();
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				_gridPieces[i][j].setTexture(this->_data->assets.GetTexture("X Piece Sprite"));
				_gridPieces[i][j].setPosition(_gridSprite.getPosition().x + (tempSpriteSize.x * i) - 7, _gridSprite.getPosition().y + (tempSpriteSize.y * j) - 7);
				_gridPieces[i][j].setColor(Color::Transparent);
			}
		}
	}
	
	void GameState::CheckAndPlacePiece() {
		Vector2i touchPoint = this->_data->input.GetMousePosition(this->_data->window);
		FloatRect gridSize = _gridSprite.getGlobalBounds();
		Vector2f gapOutsideOfGrid = Vector2f((SCREEN_WIDTH - gridSize.width) / 2, (SCREEN_HEIGHT - gridSize.height) / 2);
		Vector2f gridLocalTouchPos = Vector2f(touchPoint.x - gapOutsideOfGrid.x, touchPoint.y - gapOutsideOfGrid.y);
		Vector2f gridSectionSize = Vector2f(gridSize.width / 3, gridSize.height / 3);
		int column, row;
		if (gridLocalTouchPos.x < gridSectionSize.x) {
			column = 1;
		} else if (gridLocalTouchPos.x < gridSectionSize.x * 2) {
			column = 2;
		} else if (gridLocalTouchPos.x < gridSize.width) {
			column = 3;
		}
		if (gridLocalTouchPos.y < gridSectionSize.y) {
			row = 1;
		} else if (gridLocalTouchPos.y < gridSectionSize.y * 2) {
			row = 2;
		} else if (gridLocalTouchPos.y < gridSize.height) {
			row = 3;
		}
		
		if (_grid[column - 1][row - 1] == EMPTY_PIECE) {
			_grid[column - 1][row - 1] = _turn;
			if (PLAYER_PIECE == _turn) {
				_gridPieces[column - 1][row - 1].setTexture(this->_data->assets.GetTexture("X Piece Sprite"));
				this->CheckPlayerHasWon(_turn);
				_turn = AI_PIECE;
			} else if (AI_PIECE == _turn) {
				_gridPieces[column - 1][row - 1].setTexture(this->_data->assets.GetTexture("O Piece Sprite"));
				this->CheckPlayerHasWon(_turn);
				_turn = PLAYER_PIECE;
			}
			_gridPieces[column - 1][row - 1].setColor(Color::White);
		}
	}
	
	void GameState::PlaceAIPiece() {
		pair<int, int> bestMove = _ai.findBestMove(_grid);
		int column = bestMove.first;
		int row = bestMove.second;
		cout << column << ", " << row << endl;
		_gridPieces[column][row].setTexture(this->_data->assets.GetTexture("X Piece Sprite"));
		this->CheckPlayerHasWon(_turn);
		_turn = PLAYER_PIECE;
		_gridPieces[column][row].setColor(Color::White);
	}
	
	void GameState::CheckPlayerHasWon(int player) {
//	Columns
		Check3PiecesForMatch(0, 0, 1, 0, 2, 0, player);
		Check3PiecesForMatch(0, 1, 1, 1, 2, 1, player);
		Check3PiecesForMatch(0, 2, 1, 2, 2, 2, player);
//	Rows
		Check3PiecesForMatch(0, 0, 0, 1, 0, 2, player);
		Check3PiecesForMatch(1, 0, 1, 1, 1, 2, player);
		Check3PiecesForMatch(2, 0, 2, 1, 2, 2, player);
//	Diagonals
		Check3PiecesForMatch(0, 0, 1, 1, 2, 2, player);
		Check3PiecesForMatch(0, 2, 1, 1, 2, 0, player);
		
		int _emptyNum = 9;
		
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (EMPTY_PIECE != _grid[i][j]) {
					_emptyNum--;
				}
			}
		}
		
		cout << _emptyNum << endl;
		
		if (_emptyNum == 0 && _gameState != STATE_WON && _gameState != STATE_LOSE) {
			_gameState = STATE_DRAW;
			_gridSprite.setTexture(this->_data->assets.GetTexture("Draw Grid Sprite"));
		}
		if (STATE_DRAW == _gameState || STATE_LOSE == _gameState || STATE_WON == _gameState) {
//			Show Game Over
		}
	}
	
	void GameState::Check3PiecesForMatch(int x1, int y1, int x2, int y2, int x3, int y3, int pieceToCheck) {
		if (_grid[x1][y1] + _grid[x2][y2] + _grid[x3][y3] == pieceToCheck * 3) {
			string winningPieceStr;
			if (O_PIECE == pieceToCheck) {
				winningPieceStr = "O Win Sprite";
			} else {
				winningPieceStr = "X Win Sprite";
			}
			_gridPieces[x1][y1].setTexture(this->_data->assets.GetTexture(winningPieceStr));
			_gridPieces[x2][y2].setTexture(this->_data->assets.GetTexture(winningPieceStr));
			_gridPieces[x3][y3].setTexture(this->_data->assets.GetTexture(winningPieceStr));
			
			if (PLAYER_PIECE == pieceToCheck) {
				_gameState = STATE_WON;
			} else {
				_gameState = STATE_LOSE;
			}
		}
	}
}
