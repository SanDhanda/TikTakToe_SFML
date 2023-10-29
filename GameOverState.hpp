#pragma once
#include "State.hpp"
#include <SFML/Graphics.hpp>
#include "Game.hpp"

namespace TikTakToeGame {

	class GameOverState : public State
	{
	public:
		GameOverState(GameDataRef data, int resultState);
		void Init();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;
		sf::Clock _clock;
		sf::Sprite _background;
		sf::Sprite _homeButton;
		sf::Sprite _retryButton;

		sf::Sprite _message;

		int _resultState;

		void LoadTextures();
		void SetTextures();
		void SetPositions();
		void SetBackgroundColour();
	};
}

