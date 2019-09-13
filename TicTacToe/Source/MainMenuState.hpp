#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

using namespace sf;

namespace TTT {
	class MainMenuState : public State {
	public:
		MainMenuState(GameDataRef data);
		void Init();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);
		
	private:
		GameDataRef _data;
		Sprite _background;
		Sprite _playButton;
		Sprite _playButtonOuter;
		Sprite _title;
	};
}
