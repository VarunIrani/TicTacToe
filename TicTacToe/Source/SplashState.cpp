#include <sstream>
#include "SplashState.hpp"
#include "MainMenuState.hpp"
#include "DEFINITIONS.hpp"

#include <iostream>

namespace TTT {
	SplashState::SplashState(GameDataRef data) : _data(data) {}
	
	void SplashState::Init() {
		this->_data->assets.LoadTexture("Splash State Background", SPLASH_SCREEN_PATH);
		_background.setTexture(this->_data->assets.GetTexture("Splash State Background"));
	}
	
	void SplashState::HandleInput() {
		Event event;
		while (this->_data->window.pollEvent(event)) {
			if (Event::Closed == event.type) {
				this->_data->window.close();
			}
		}
	}
	
	void SplashState::Update(float dt) {
		if (this->_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME) {
			this->_data->machine.AddState(StateRef(new MainMenuState(this->_data)), true);
		}
	}
	
	void SplashState::Draw(float dt) {
		this->_data->window.clear(Color::Red);
		this->_data->window.draw(this->_background);
		this->_data->window.display();
	}
}
