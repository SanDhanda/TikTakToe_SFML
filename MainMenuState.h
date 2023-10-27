#pragma once
#include "State.hpp"
#include <SFML/Graphics.hpp>
#include "Game.hpp"

namespace TikTakToeGame {

	class MainMenuState : public State
	{
	public:
		MainMenuState(GameDataRef data);
		void Init();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;
		sf::Clock _clock;
		sf::Sprite _background;
		sf::Sprite _playButton;
		sf::Sprite _playButtonOuter; 
		sf::Sprite _title;

		void LoadTextures();
		void SetTextures();
		void SetPositions();
	};
}

