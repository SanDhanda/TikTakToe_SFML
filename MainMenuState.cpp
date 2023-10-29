#include "MainMenuState.h"
#include <sstream>
#include "DEFINITIONS.hpp"
#include "GameState.hpp"
#include <iostream>



namespace TikTakToeGame {

	MainMenuState::MainMenuState(GameDataRef data) :_data(data){}

	void MainMenuState::Init() {
		LoadTextures();
		SetTextures();
		SetPositions();
	}

	void MainMenuState::HandleInput() {
		sf::Event event;
		while (this->_data->window.pollEvent(event)) {
			if (sf::Event::Closed == event.type) {
				this->_data->window.close();
			}
			/*if (this->_data->input.IsSpriteClicked(this->_playButton, sf::Mouse::Left, this->_data->window)) {
				this->_data->machine.AddState(StateRef(new GameState(_data)), true);
			}*/
			if (this->_data->input.IsSpriteClicked(this->_singlePlayerButton, sf::Mouse::Left, this->_data->window)) {
				this->_data->machine.AddState(StateRef(new GameState(_data)), true);
				this->_data->machine.SetIsSinglePlayer(true);
			}
			if (this->_data->input.IsSpriteClicked(this->_twoPlayerButton, sf::Mouse::Left, this->_data->window)) {
				this->_data->machine.AddState(StateRef(new GameState(_data)), true);
				this->_data->machine.SetIsSinglePlayer(false);
			}
		}
	}

	void MainMenuState::Update(float dt) {
		
	}

	void MainMenuState::Draw(float dt) {
		this->_data->window.clear();
		this->_data->window.draw(this->_background);
		this->_data->window.draw(this->_title);
		this->_data->window.draw(this->_playButtonOuterOne);
		//this->_data->window.draw(this->_playButton);
		this->_data->window.draw(this->_singlePlayerButton);
		this->_data->window.draw(this->_playButtonOuterTwo);
		this->_data->window.draw(this->_twoPlayerButton);


		this->_data->window.display();
	}

	void MainMenuState::LoadTextures() {
		this->_data->assets.LoadTexture("Background", MAIN_MENU_BACKGROUND_FILEPATH);
		//this->_data->assets.LoadTexture("Play Button", MAIN_MENU_PLAY_BUTTON);
		this->_data->assets.LoadTexture("Single Player Button", MAIN_MENU_SINGLE_PLAYER_BUTTON);
		this->_data->assets.LoadTexture("Two Player Button", MAIN_MENU_TWO_PLAYER_BUTTON);

		this->_data->assets.LoadTexture("Play Button Outer", MAIN_MENU_PLAY_BUTTON_OUTER);
		this->_data->assets.LoadTexture("Title", MAIN_MENU_TITLE_PATH);
	}

	void MainMenuState::SetTextures()
	{
		this->_background.setTexture(this->_data->assets.GetTexture("Background"));
		//this->_playButton.setTexture(this->_data->assets.GetTexture("Play Button"));
		this->_singlePlayerButton.setTexture(this->_data->assets.GetTexture("Single Player Button"));
		this->_twoPlayerButton.setTexture(this->_data->assets.GetTexture("Two Player Button"));


		this->_playButtonOuterOne.setTexture(this->_data->assets.GetTexture("Play Button Outer"));
		this->_playButtonOuterTwo.setTexture(this->_data->assets.GetTexture("Play Button Outer"));
		this->_title.setTexture(this->_data->assets.GetTexture("Title"));
	}

	void MainMenuState::SetPositions()
	{
		//this->_playButton.setPosition((SCREEN_WIDTH / 2 - this->_playButton.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2 - this->_playButton.getGlobalBounds().height / 2));
		this->_singlePlayerButton.setPosition((SCREEN_WIDTH / 2 - this->_singlePlayerButton.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2 - this->_singlePlayerButton.getGlobalBounds().height / 2));
		this->_playButtonOuterOne.setPosition((SCREEN_WIDTH / 2 - this->_playButtonOuterOne.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2 - this->_playButtonOuterOne.getGlobalBounds().height / 2));


		this->_twoPlayerButton.setPosition((SCREEN_WIDTH / 2 - this->_twoPlayerButton.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2 - this->_twoPlayerButton.getGlobalBounds().height / 2) + this->_singlePlayerButton.getGlobalBounds().height * 1.25);
		this->_playButtonOuterTwo.setPosition((SCREEN_WIDTH / 2 - this->_playButtonOuterTwo.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2 - this->_playButtonOuterTwo.getGlobalBounds().height / 2) + this->_singlePlayerButton.getGlobalBounds().height *1.25);
		
		
		this->_title.setPosition((SCREEN_WIDTH / 2 - this->_title.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 4 - this->_title.getGlobalBounds().height / 2));
	}


}