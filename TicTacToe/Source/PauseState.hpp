#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
using namespace sf;

namespace TTT {
	class PauseState : public State {
	public:
		PauseState(GameDataRef data);
		void Init();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);
		
	private:
		GameDataRef _data;
		Sprite _background;
		Sprite _resumeButton;
		Sprite _retryButton;
		Sprite _homeButton;
	};
}
