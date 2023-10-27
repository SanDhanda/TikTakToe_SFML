#include "PauseState.hpp"
#include "State.hpp"
#include "MainMenuState.h"
#include "GameState.hpp"
#include <sstream>
#include "DEDFINITIONS.hpp"
#include <iostream>



namespace TikTakToeGame {

	PauseState::PauseState(GameDataRef data) :_data(data) {}

	void PauseState::Init() {
		gameState = STATE_PAUSED;
		turn = PLAYER_PEICE;
		LoadTextures();
		SetTextures();
		SetPositions();
	}

	void PauseState::HandleInput() {
		sf::Event event;
		while (this->_data->window.pollEvent(event)) {
			if (sf::Event::Closed == event.type) {
				this->_data->window.close();
			}
			if (this->_data->input.IsSpriteClicked(this->_resumeButton, sf::Mouse::Left, this->_data->window)) {
				this->_data->machine.RemoveState();
			}
			if (this->_data->input.IsSpriteClicked(this->_homeButton, sf::Mouse::Left, this->_data->window)) {
				_data->machine.AddState(StateRef(new MainMenuState(this->_data)));
			}
		}
	}

	void PauseState::Update(float dt) {

	}

	void PauseState::Draw(float dt) {
		this->_data->window.clear();
		this->_data->window.draw(this->_background);
		this->_data->window.draw(this->_resumeButton);
		this->_data->window.draw(this->_homeButton);
		this->_data->window.display();
	}


	void PauseState::LoadTextures() {
		this->_data->assets.LoadTexture("Resume Button", RESUME_BUTTON);
		this->_data->assets.LoadTexture("Pause Window", PAUSE_WINDOW);
		this->_data->assets.LoadTexture("Pause Background", PAUSE_BACKGROUND);
		this->_data->assets.LoadTexture("Home Button", HOME_BUTTON);
	}

	void PauseState::SetTextures()
	{
		this->_background.setTexture(this->_data->assets.GetTexture("Pause Background"));
		this->_resumeButton.setTexture(this->_data->assets.GetTexture("Resume Button"));
		this->_pauseWindow.setTexture(this->_data->assets.GetTexture("Pause Window"));
		this->_homeButton.setTexture(this->_data->assets.GetTexture("Home Button"));
	}

	void PauseState::SetPositions()
	{
		this->_resumeButton.setPosition(this->_data->window.getSize().x - _resumeButton.getLocalBounds().width, _resumeButton.getPosition().y + 10);
		this->_homeButton.setPosition(this->_data->window.getSize().x - _resumeButton.getLocalBounds().width - (_homeButton.getLocalBounds().width *1.1), _homeButton.getPosition().y + 10);
	}

}