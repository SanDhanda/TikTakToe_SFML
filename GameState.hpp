#pragma once
#include "State.hpp"
#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "AI.hpp"

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
		sf::Sprite _gridSprite;
		sf::Sprite _gridPieces[3][3];
		int gridArray[3][3];
		int turn;
		int gameState;
		bool singlePlayer;
		AI* ai;

		void LoadTextures();
		void SetTextures();
		void SetPositions();
		void CheckAndPlacePiece(bool isSinglePlayer);
		void CheckAndPlacePiece_SinglePlayer(int column, int row);
		void CheckAndPlacePiece_TwoPlayer(int column, int row);

		void CheckForWin(int turn, bool isSinglePlayer);
		void Check3PeicesForMatch(int x1, int y1, int x2, int y2, int x3, int y3, int pieceToCheck, bool isSinglePlayer);

		void InitGridPieces();
		void SetGridToEmpty();
		void DrawGridPieces();
		int GetColumn(sf::Vector2f gridLocalTouchPos, sf::Vector2f gridSectionSize, sf::FloatRect gridSize);
		int GetRow(sf::Vector2f gridLocalTouchPos, sf::Vector2f gridSectionSize, sf::FloatRect gridSize);
		void SetPlayerPiece(int column, int row);
		void SetAIPiece(int column, int row);
		bool IsGameDrawn(int emptyNum);
		bool IsGameOver();

		void CheckPieces(int playerTurn, bool isSinglePlayer);

	};
}

