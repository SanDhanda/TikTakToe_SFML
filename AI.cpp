#include "AI.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>

using namespace std;

namespace TikTakToeGame {

	AI::AI(int playerPiece, GameDataRef data) {
		this->_date = data;
		this->playerPiece = playerPiece;

		if (playerPiece == O) {
			aiPiece = X;
		}
		else {
			aiPiece = O;
		}
		SetupCheckMatchVector();
		
	}

	void AI::PlacePiece(int(*gridArray)[3][3], sf::Sprite gridPieces[3][3], int* gameSate)
	{
		try {
			for (int i = 0; i < checkMatchVector.size(); i++) {
				CheckSection(checkMatchVector[i][0], checkMatchVector[i][1], checkMatchVector[i][2], checkMatchVector[i][3], checkMatchVector[i][4], checkMatchVector[i][5],
					AI_PIECE, gridArray, gridPieces);
			}
			for (int i = 0; i < checkMatchVector.size(); i++) {
				CheckSection(checkMatchVector[i][0], checkMatchVector[i][1], checkMatchVector[i][2], checkMatchVector[i][3], checkMatchVector[i][4], checkMatchVector[i][5],
					PLAYER_PIECE, gridArray, gridPieces);
			}
			//isCentre is empty
			CheckIfPieceIsEmpty(1, 1, gridArray, gridPieces);
			CheckIfPieceIsEmpty(0, 0, gridArray, gridPieces);
			CheckIfPieceIsEmpty(0, 2, gridArray, gridPieces);
			CheckIfPieceIsEmpty(2, 0, gridArray, gridPieces);
			CheckIfPieceIsEmpty(2, 2, gridArray, gridPieces);

			CheckIfPieceIsEmpty(0, 1, gridArray, gridPieces);
			CheckIfPieceIsEmpty(1, 2, gridArray, gridPieces);
			CheckIfPieceIsEmpty(2, 1, gridArray, gridPieces);
			CheckIfPieceIsEmpty(1, 0, gridArray, gridPieces);
		}
		catch (int error) {

		}
		*gameSate = STATE_PLAYING;
	}

	void AI::CheckSection(int x1, int y1, int x2, int y2, int x, int y, int pieceToCheck, int(*gridArray)[3][3], sf::Sprite gridPieces[3][3])
	{
		if ((*gridArray)[x1][y1] == pieceToCheck && (*gridArray)[x2][y2] == pieceToCheck) {
			if (EMPTY == (*gridArray)[x][y]) {
				(*gridArray)[x][y] = AI_PIECE;
				gridPieces[x][y].setTexture(this->_date->assets.GetTexture("O Piece"));
				gridPieces[x][y].setColor(sf::Color(255, 255, 255, 255));
				throw - 1;
			}
		}
	}

	void AI::CheckIfPieceIsEmpty(int x, int y, int(*gridArray)[3][3], sf::Sprite gridPieces[3][3])
	{
		if (EMPTY == (*gridArray)[x][y]) {
			(*gridArray)[x][y] = AI_PIECE;
			gridPieces[x][y].setTexture(this->_date->assets.GetTexture("O Piece"));
			gridPieces[x][y].setColor(sf::Color(255, 255, 255, 255));
			throw - 2;
		}
	}

	void AI::SetupCheckMatchVector() {
		checkMatchVector.push_back({ 0, 2, 1, 2, 2, 2 });
		checkMatchVector.push_back({ 0, 2, 0, 1, 0, 0 });
		checkMatchVector.push_back({ 0, 2, 1, 1, 2, 0 });
		checkMatchVector.push_back({ 2, 2, 1, 2, 0, 2 });
		checkMatchVector.push_back({ 2, 2, 2, 1, 2, 0 });
		checkMatchVector.push_back({ 2, 2, 1, 1, 0, 0 });
		checkMatchVector.push_back({ 0, 0, 0, 1, 0, 2 });
		checkMatchVector.push_back({ 0, 0, 1, 0, 2, 0 });
		checkMatchVector.push_back({ 0, 0, 1, 1, 2, 2 });
		checkMatchVector.push_back({ 2, 0, 2, 1, 2, 2 });
		checkMatchVector.push_back({ 2, 0, 1, 0, 0, 0 });
		checkMatchVector.push_back({ 2, 0, 1, 1, 0, 2 });
		checkMatchVector.push_back({ 0, 1, 1, 1, 2, 1 });
		checkMatchVector.push_back({ 1, 2, 1, 1, 1, 0 });
		checkMatchVector.push_back({ 2, 1, 1, 1, 0, 1 });
		checkMatchVector.push_back({ 1, 0, 1, 1, 1, 2 });
		checkMatchVector.push_back({ 0, 1, 2, 1, 1, 1 });
		checkMatchVector.push_back({ 1, 2, 1, 0, 1, 1 });
		checkMatchVector.push_back({ 0, 2, 2, 0, 1, 1 });
		checkMatchVector.push_back({ 2, 2, 0, 0, 1, 1 });
		checkMatchVector.push_back({ 0, 2, 2, 2, 1, 2 });
		checkMatchVector.push_back({ 0, 0, 2, 0, 1, 0 });
		checkMatchVector.push_back({ 0, 2, 0, 0, 0, 1 });
		checkMatchVector.push_back({ 2, 2, 2, 0, 2, 1 });
	}


}

