#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <array>

#include "Game.hpp"

namespace TikTakToeGame {
	class AI
	{
	public:
		AI(int playerPiece, GameDataRef data);
		void PlacePiece(int (*gridArray)[3][3], sf::Sprite gridPieces[3][3], int *gameSate);

	private:
		void CheckSection(int x1, int y1, int x2, int y2, int x, int y, int pieceToCheck, int (*gridArray)[3][3], sf::Sprite gridPieces[3][3]);

		void CheckIfPieceIsEmpty(int x, int y, int(*gridArray)[3][3], sf::Sprite gridPieces[3][3]);

		int aiPiece;
		int playerPiece;

		std::vector<std::array<int, 6>> checkMatchVector;

		GameDataRef _date;

		void SetupCheckMatchVector();

	};
}

