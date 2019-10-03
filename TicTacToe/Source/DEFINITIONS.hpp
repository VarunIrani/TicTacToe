#pragma once
#include <string>
using namespace std;

const int SCREEN_WIDTH = 768;
const int SCREEN_HEIGHT = 1136;

const double SPLASH_STATE_SHOW_TIME = 3;

const string SPLASH_SCREEN_PATH = "Resources/res/Splash Background.png";
const string MAIN_MENU_BACKGROUND_PATH = "Resources/res/Main Menu Background.png";
const string GAME_SCREEN_BACKGROUND_PATH = "Resources/res/Main Menu Background.png";
const string PAUSE_SCREEN_BACKGROUND_PATH = "Resources/res/Pause Background.png";

const string GRID_SPRITE_PATH = "Resources/res/Grid.png";
const string DRAW_GRID_SPRITE_PATH = "Resources/res/Draw Grid.png";

const string GAME_TITLE_PATH = "Resources/res/Game Title.png";

const string MAIN_MENU_PLAY_BUTTON = "Resources/res/Play Button.png";
const string MAIN_MENU_PLAY_BUTTON_OUTER = "Resources/res/Play Button Outer.png";
const string PAUSE_BUTTON = "Resources/res/Pause Button.png";
const string RESUME_BUTTON = "Resources/res/Resume Button.png";
const string HOME_BUTTON = "Resources/res/Home Button.png";
const string RETRY_BUTTON = "Resources/res/Retry Button.png";

const string X_PIECE_PATH = "Resources/res/X.png";
const string O_PIECE_PATH = "Resources/res/O.png";
const string X_WIN_PATH = "Resources/res/X Win.png";
const string O_WIN_PATH = "Resources/res/O Win.png";

const int X_PIECE = 1;
const int O_PIECE = -1;
const int EMPTY_PIECE = 0;

const int PLAYER_PIECE = X_PIECE;
const int AI_PIECE = O_PIECE;

const int STATE_PLAYING = 98;
const int STATE_PAUSED = 97;
const int STATE_WON = 96;
const int STATE_LOSE = 95;
const int STATE_PLACING_PIECE = 94;
const int STATE_AI_PLAYING = 93;
const int STATE_DRAW = 92;

typedef struct Move {
	int x;
	int y;
	int score;
	Move() {}
	Move(int s) : score(s) {}
} Move;

class Board {
private:
	int _board[3][3];
public:
	void Clear() {
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				_board[i][j] = EMPTY_PIECE;
			}
		}
	}
	
	void PlacePiece(int x, int y, int player) {
		_board[x][y] = player;
	}
	
	int At(int x, int y) {
		return _board[x][y];
	}
};
