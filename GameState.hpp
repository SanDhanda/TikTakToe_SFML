#pragma once
#include "State.hpp"
#include <SFML/Graphics.hpp>
#include "Game.hpp"

namespace TikTakToeGame {

	class GameState : public State
	{
	public:
		GameState(GameDataRef data);
		void Init();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;
		sf::Clock _clock;
		sf::Sprite _background;
		sf::Sprite _pauseButton;
		int turn;
		int gameState;

		void LoadTextures();
		void SetTextures();
		void SetPositions();

	};
}

