#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

using namespace sf;
using namespace std;

namespace TTT {
	class SplashState : public State {
	public:
		SplashState(GameDataRef data);
		void Init();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);
		
	private:
		GameDataRef _data;
		Clock _clock;
		Sprite _background;
	};
}
