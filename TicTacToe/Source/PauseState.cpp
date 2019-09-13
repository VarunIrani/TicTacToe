#include <sstream>
#include "PauseState.hpp"
#include "DEFINITIONS.hpp"
#include "GameState.hpp"
#include "MainMenuState.hpp"

#include <iostream>
using namespace std;

namespace TTT {
	PauseState::PauseState(GameDataRef data) : _data(data) {}
	
	void PauseState::Init() {
		this->_data->assets.LoadTexture("Pause Screen Background", PAUSE_SCREEN_BACKGROUND_PATH);
		_background.setTexture(this->_data->assets.GetTexture("Pause Screen Background"));
		
		this->_data->assets.LoadTexture("Resume Button", RESUME_BUTTON);
		_resumeButton.setTexture(this->_data->assets.GetTexture("Resume Button"));
		
		this->_data->assets.LoadTexture("Retry Button", RETRY_BUTTON);
		_retryButton.setTexture(this->_data->assets.GetTexture("Retry Button"));
		
		this->_data->assets.LoadTexture("Home Button", HOME_BUTTON);
		_homeButton.setTexture(this->_data->assets.GetTexture("Home Button"));
		
		_resumeButton.setPosition((this->_data->window.getSize().x / 2) - (_resumeButton.getLocalBounds().width / 2), (this->_data->window.getSize().y / 4) - (_resumeButton.getLocalBounds().height / 2));
		
		_retryButton.setPosition((this->_data->window.getSize().x / 2) - (_retryButton.getLocalBounds().width / 2), (this->_data->window.getSize().y / 4 * 2) - (_retryButton.getLocalBounds().height / 2));
		
		_homeButton.setPosition((this->_data->window.getSize().x / 2) - (_homeButton.getLocalBounds().width / 2), (this->_data->window.getSize().y / 4 * 3) - (_homeButton.getLocalBounds().height / 2));
	}
	
	void PauseState::HandleInput() {
		Event event;
		while (this->_data->window.pollEvent(event)) {
			if (Event::Closed == event.type) {
				this->_data->window.close();
			}
			if (this->_data->input.IsSpriteClicked(this->_resumeButton, Mouse::Left, this->_data->window)) {
				this->_data->machine.RemoveState();
			}
			if (this->_data->input.IsSpriteClicked(this->_retryButton, Mouse::Left, this->_data->window)) {
				this->_data->machine.AddState(StateRef(new GameState(this->_data)), true);
			}
			if (this->_data->input.IsSpriteClicked(this->_homeButton, Mouse::Left, this->_data->window)) {
				this->_data->machine.RemoveState();
				this->_data->machine.AddState(StateRef(new MainMenuState(this->_data)), true);
			}
		}
	}
	
	void PauseState::Update(float dt) {}
	
	void PauseState::Draw(float dt) {
		this->_data->window.clear();
		this->_data->window.draw(this->_background);
		this->_data->window.draw(this->_resumeButton);
		this->_data->window.draw(this->_homeButton);
		this->_data->window.draw(this->_retryButton);
		this->_data->window.display();
	}
}
