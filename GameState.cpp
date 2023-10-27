#include "GameState.hpp"
#include "State.hpp"
#include "PauseState.hpp"
#include <sstream>
#include "DEDFINITIONS.hpp"
#include <iostream>



namespace TikTakToeGame {

	GameState::GameState(GameDataRef data) :_data(data) {}

	void GameState::Init() {
		gameState = STATE_PLAYING;
		turn = PLAYER_PEICE;
		LoadTextures();
		SetTextures();
		SetPositions();
	}

	void GameState::HandleInput() {
		sf::Event event;
		while (this->_data->window.pollEvent(event)) {
			if (sf::Event::Closed == event.type) {
				this->_data->window.close();
			}
			if (this->_data->input.IsSpriteClicked(this->_pauseButton, sf::Mouse::Left, this->_data->window)) {
				this->_data->machine.AddState(StateRef(new PauseState(_data)), true);
			}
		}
	}

	void GameState::Update(float dt) {

	}

	void GameState::Draw(float dt) {
		this->_data->window.clear();
		this->_data->window.draw(this->_background);
		this->_data->window.draw(this->_pauseButton);
		this->_data->window.display();
	}


	void GameState::LoadTextures() {
		this->_data->assets.LoadTexture("Pause Button", PAUSE_BUTTON);
	}

	void GameState::SetTextures()
	{
		this->_background.setTexture(this->_data->assets.GetTexture("Background"));
		this->_pauseButton.setTexture(this->_data->assets.GetTexture("Pause Button"));
	}

	void GameState::SetPositions()
	{
		this->_pauseButton.setPosition(this->_data->window.getSize().x - _pauseButton.getLocalBounds().width, _pauseButton.getPosition().y);
	}

}