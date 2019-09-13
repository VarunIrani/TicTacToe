#pragma once
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "StateMachine.hpp"
#include "AssetManager.hpp"
#include "InputManager.hpp"

using namespace std;
using namespace sf;

namespace TTT {
	struct GameData {
		StateMachine machine;
		RenderWindow window;
		AssetManager assets;
		InputManager input;
	};
	
	typedef shared_ptr<GameData> GameDataRef;
	
	class Game {
	public:
		Game(int width, int height, string title);
	private:
		const float dt = 1.0f / 60.0f;
		Clock _clock;
		GameDataRef _data = make_shared<GameData>();
		
		void Run();
	};
}
