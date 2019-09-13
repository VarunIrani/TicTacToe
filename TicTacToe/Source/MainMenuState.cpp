#include <sstream>
#include "MainMenuState.hpp"
#include "DEFINITIONS.hpp"
#include "GameState.hpp"
#include <iostream>
using namespace std;

namespace TTT {
	MainMenuState::MainMenuState(GameDataRef data) : _data(data) {}
	
	void MainMenuState::Init() {
		this->_data->assets.LoadTexture("Main Menu Background", MAIN_MENU_BACKGROUND_PATH);
		_background.setTexture(this->_data->assets.GetTexture("Main Menu Background"));
		
		this->_data->assets.LoadTexture("Game Title", GAME_TITLE_PATH);
		_title.setTexture(this->_data->assets.GetTexture("Game Title"));
		
		this->_data->assets.LoadTexture("Main Menu Play Button", MAIN_MENU_PLAY_BUTTON);
		_playButton.setTexture(this->_data->assets.GetTexture("Main Menu Play Button"));
		
		this->_data->assets.LoadTexture("Main Menu Play Button Outer", MAIN_MENU_PLAY_BUTTON_OUTER);
		_playButtonOuter.setTexture(this->_data->assets.GetTexture("Main Menu Play Button Outer"));
		
		_playButton.setPosition((SCREEN_WIDTH / 2) - (_playButton.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (_playButton.getGlobalBounds().height / 2));
		_playButtonOuter.setPosition((SCREEN_WIDTH / 2) - (_playButtonOuter.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (_playButtonOuter.getGlobalBounds().height / 2));
		
		_title.setPosition((SCREEN_WIDTH / 2) - (_title.getGlobalBounds().width / 2), this->_title.getGlobalBounds().height * 0.1);
		
	}
	
	void MainMenuState::HandleInput() {
		Event event;
		while (this->_data->window.pollEvent(event)) {
			if (Event::Closed == event.type) {
				this->_data->window.close();
			}
			if (this->_data->input.IsSpriteClicked(this->_playButton, Mouse::Left, this->_data->window)) {
				this->_data->machine.AddState(StateRef(new GameState(this->_data)), true);
			}
		}
	}
	
	void MainMenuState::Update(float dt) {}
	
	void MainMenuState::Draw(float dt) {
		this->_data->window.clear();
		this->_data->window.draw(this->_background);
		this->_data->window.draw(this->_title);
		this->_data->window.draw(this->_playButton);
		this->_data->window.draw(this->_playButtonOuter);
		this->_data->window.display();
	}
}
