#include "GameOverState.hpp"
#include "State.hpp"
#include "MainMenuState.h"
#include "GameState.hpp"
#include <sstream>
#include "DEDFINITIONS.hpp"
#include <iostream>



namespace TikTakToeGame {

	GameOverState::GameOverState(GameDataRef data) :_data(data) {}

	void GameOverState::Init() {
		LoadTextures();
		SetTextures();
		SetPositions();
	}

	void GameOverState::HandleInput() {
		sf::Event event;
		while (this->_data->window.pollEvent(event)) {
			if (sf::Event::Closed == event.type) {
				this->_data->window.close();
			}
			if (this->_data->input.IsSpriteClicked(this->_retryButton, sf::Mouse::Left, this->_data->window)) {
				this->_data->machine.AddState(StateRef(new GameState(_data)), true);
			}
			if (this->_data->input.IsSpriteClicked(this->_homeButton, sf::Mouse::Left, this->_data->window)) {
				_data->machine.AddState(StateRef(new MainMenuState(this->_data)), true);
			}
		}
	}

	void GameOverState::Update(float dt) {

	}

	void GameOverState::Draw(float dt) {
		this->_data->window.clear();
		this->_data->window.draw(this->_background);
		this->_data->window.draw(this->_retryButton);
		this->_data->window.draw(this->_homeButton);
		this->_data->window.display();
	}


	void GameOverState::LoadTextures() {
		this->_data->assets.LoadTexture("Retry Button", RETRY_BUTTON);
		this->_data->assets.LoadTexture("Game Over Background", GAME_OVER_BACKGROUND);
		this->_data->assets.LoadTexture("Home Button", HOME_BUTTON);
	}

	void GameOverState::SetTextures()
	{
		this->_background.setTexture(this->_data->assets.GetTexture("Game Over Background"));
		this->_retryButton.setTexture(this->_data->assets.GetTexture("Retry Button"));
		this->_homeButton.setTexture(this->_data->assets.GetTexture("Home Button"));
	}

	void GameOverState::SetPositions()
	{
		this->_retryButton.setPosition((this->_data->window.getSize().x / 2) - (_retryButton.getLocalBounds().width / 2), (this->_data->window.getSize().y / 3) - (_retryButton.getLocalBounds().width / 2));
		this->_homeButton.setPosition((this->_data->window.getSize().x / 2) - (_homeButton.getLocalBounds().width / 2), (this->_data->window.getSize().y / 3) * 2 - (_homeButton.getLocalBounds().width / 2));
	}

}