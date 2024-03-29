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
		this->_data->assets.LoadFont("Win Font", FONT);
		
		_winText.setFont(this->_data->assets.GetFont("Win Font"));
		_winText.setFillColor(Color::Black);
		
		_winText.setCharacterSize(120);
		_winText.move(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 + 300);
		_gridSprite.setTexture(this->_data->assets.GetTexture("Grid Sprite"));
		
		this->_data->assets.LoadTexture("Pause Button", PAUSE_BUTTON);
		_pauseButton.setTexture(this->_data->assets.GetTexture("Pause Button"));
		_pauseButton.setPosition(this->_data->window.getSize().x - _pauseButton.getLocalBounds().width, _pauseButton.getPosition().y);
		
		_gridSprite.setPosition((SCREEN_WIDTH / 2) - (_gridSprite.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (_gridSprite.getGlobalBounds().height / 2));
		InitGridPieces();
		
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				_board.PlacePiece(j, i, EMPTY_PIECE);
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
//					this->CheckAndPlacePiece();
				}
			}
		}
	}
	
	void GameState::Update(float dt) {}
	
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
		this->_data->window.draw(_winText);
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
		int column = -1, row = -1;
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
		
//		if (AI_PIECE == _turn) {
//			this->PlaceAIPiece();
//			return;
//		}
		
		if (_board.At(column - 1, row - 1) == EMPTY_PIECE) {
			_board.PlacePiece(column - 1, row - 1, _turn);
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
			PrintBoard(_board);
		}
	}
	
	void GameState::PrintBoard(Board _board) {
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				switch (_board.At(j, i))
				{
					case X_PIECE:
						cout << "X";
						break;
					case O_PIECE:
						cout << "O";
						break;
					case EMPTY_PIECE:
						cout << " ";
						break;
				}
				if (j < 2)
					cout << "|";
			}
			if (i < 2)
				cout << "\n-+-+-\n";
		}
		cout << endl;
	}
	
	void GameState::PlaceAIPiece() {
		Move bestMove = _ai.FindBestMove(_board, AI_PIECE);
		int column = bestMove.y;
		int row = bestMove.x;
		cout << column << ", " << row << endl;
		if (_board.At(column, row) == EMPTY_PIECE) {
			_board.PlacePiece(column, row, _turn);
			_gridPieces[column][row].setTexture(this->_data->assets.GetTexture("O Piece Sprite"));
			this->CheckPlayerHasWon(_turn);
			_turn = PLAYER_PIECE;
		}
		_gridPieces[column][row].setColor(Color::White);
		PrintBoard(_board);
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
				if (EMPTY_PIECE != _board.At(i, j)) {
					_emptyNum--;
				}
			}
		}
		
		if (_emptyNum == 0 && _gameState != STATE_WON && _gameState != STATE_LOSE) {
			_gameState = STATE_DRAW;
			_gridSprite.setTexture(this->_data->assets.GetTexture("Draw Grid Sprite"));
			_winText.setString("DRAW");
		}
		if (STATE_DRAW == _gameState || STATE_LOSE == _gameState || STATE_WON == _gameState) {
//			Show Game Over
		}
	}
	
	void GameState::Check3PiecesForMatch(int x1, int y1, int x2, int y2, int x3, int y3, int pieceToCheck) {
		if (_board.At(x1, y1) + _board.At(x2, y2) + _board.At(x3, y3) == pieceToCheck * 3) {
			string winningPieceStr;
			if (O_PIECE == pieceToCheck) {
				winningPieceStr = "O Win Sprite";
			} else {
				winningPieceStr = "X Win Sprite";
			}
			_gridPieces[x1][y1].setTexture(this->_data->assets.GetTexture(winningPieceStr));
			_gridPieces[x2][y2].setTexture(this->_data->assets.GetTexture(winningPieceStr));
			_gridPieces[x3][y3].setTexture(this->_data->assets.GetTexture(winningPieceStr));
			
			string winner = "";
			if (X_PIECE == pieceToCheck)
			{
				winner = "X WON";
				_gameState = STATE_WON;
				_winText.setString(winner);
			}
			if (O_PIECE == pieceToCheck) {
				winner = "O WON";
				_gameState = STATE_LOSE;
				_winText.setString(winner);
			}
		}
	}
}
