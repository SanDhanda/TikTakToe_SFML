#include "GameState.hpp"
#include "State.hpp"
#include "PauseState.hpp"
#include "GameOverState.hpp"
#include <sstream>
#include "DEFINITIONS.hpp"
#include <iostream>



namespace TikTakToeGame {

	GameState::GameState(GameDataRef data) :_data(data) {}

	void GameState::Init() {
		
		gameState = STATE_PLAYING;
		turn = PLAYER_ONE_PIECE;
		this->ai = new AI(turn, this->_data);
		LoadTextures();
		SetTextures();
		SetPositions();
		InitGridPieces();
		SetGridToEmpty();
	}

	void GameState::LoadTextures() {
		this->_data->assets.LoadTexture("Pause Button", PAUSE_BUTTON);
		this->_data->assets.LoadTexture("Grid", GAME_GRID_FILEPATH);
		this->_data->assets.LoadTexture("X Piece", X_FILEPATH);
		this->_data->assets.LoadTexture("O Piece", O_FILEPATH);
		this->_data->assets.LoadTexture("X Win Piece", X_WIN_FILEPATH);
		this->_data->assets.LoadTexture("O Win Piece", O_WIN_FILEPATH);
	}

	void GameState::SetTextures()
	{
		this->_background.setTexture(this->_data->assets.GetTexture("Background"));
		this->_pauseButton.setTexture(this->_data->assets.GetTexture("Pause Button"));
		this->_gridSprite.setTexture(this->_data->assets.GetTexture("Grid"));
	}

	void GameState::SetPositions()
	{
		this->_pauseButton.setPosition(this->_data->window.getSize().x - _pauseButton.getLocalBounds().width, _pauseButton.getPosition().y);
		this->_gridSprite.setPosition(SCREEN_WIDTH / 2 - _gridSprite.getGlobalBounds().width / 2, SCREEN_HEIGHT / 2 - _gridSprite.getGlobalBounds().height / 2);
	}
	void GameState::InitGridPieces() {
		sf::Vector2u tempSpriteSize = this->_data->assets.GetTexture("X Piece").getSize();

		for (int x = 0; x < 3; x++) {
			for (int y = 0; y < 3; y++) {
				_gridPieces[x][y].setTexture(this->_data->assets.GetTexture("X Piece"));
				_gridPieces[x][y].setPosition(_gridSprite.getPosition().x + (tempSpriteSize.x * x) - 7, _gridSprite.getPosition().y + (tempSpriteSize.y * y) - 7);
				_gridPieces[x][y].setColor(sf::Color(255, 255, 255, 0));
			}
		}
	}
	void GameState::SetGridToEmpty() {
		for (int x = 0; x < 3; x++) {
			for (int y = 0; y < 3; y++) {
				gridArray[x][y] = EMPTY;
			}
		}
	}

	void GameState::HandleInput() {
		sf::Event event;
		while (this->_data->window.pollEvent(event)) {
			if (sf::Event::Closed == event.type) {
				this->_data->window.close();
			}
			if (this->_data->input.IsSpriteClicked(this->_pauseButton, sf::Mouse::Left, this->_data->window)) {
				this->_data->machine.AddState(StateRef(new PauseState(_data)), false);
			}
			else if (this->_data->input.IsSpriteClicked(this->_gridSprite, sf::Mouse::Left, this->_data->window)) {
				if (STATE_PLAYING == gameState) {
					if (this->_data->machine.GetIsSinglePlayer()) {
						std::cout << "single player" << std::endl;
						this->CheckAndPlacePiece(true);
					}
					else {
						std::cout << "two player" << std::endl;
						this->CheckAndPlacePiece(false);
					}
				}

			}
		}
	}

	void GameState::Update(float dt) {
		if (IsGameOver()) {
			if (this->_clock.getElapsedTime().asSeconds() > TIME_BEFORE_SHOWING_GAME_OVER) {
				this->_data->machine.AddState(StateRef(new GameOverState(_data)), true);
			}
		}
	}

	void GameState::Draw(float dt) {
		this->_data->window.clear();
		this->_data->window.draw(this->_background);
		this->_data->window.draw(this->_pauseButton);
		this->_data->window.draw(this->_gridSprite);
		DrawGridPieces();
		this->_data->window.display();
	}

	void GameState::DrawGridPieces() {
		for (int x = 0; x < 3; x++) {
			for (int y = 0; y < 3; y++) {
				this->_data->window.draw(this->_gridPieces[x][y]);
			}
		}
	}

	void GameState::CheckAndPlacePiece(bool isSinglePlayer) {
		sf::Vector2i touchpoint = this->_data->input.GetMousePosition(this->_data->window);
		sf::FloatRect gridSize = _gridSprite.getGlobalBounds();
		sf::Vector2f gapOutsideOfGrid = sf::Vector2f((SCREEN_WIDTH - gridSize.width) / 2, (SCREEN_HEIGHT - gridSize.height) / 2);
		sf::Vector2f gridLocalTouchPos = sf::Vector2f(touchpoint.x - gapOutsideOfGrid.x, touchpoint.y - gapOutsideOfGrid.y);
		sf::Vector2f gridSectionSize = sf::Vector2f(gridSize.width / 3, gridSize.height / 3);

		int column = GetColumn(gridLocalTouchPos, gridSectionSize, gridSize);
		int row = GetRow(gridLocalTouchPos, gridSectionSize, gridSize);


		if (isSinglePlayer) {
			CheckAndPlacePiece_SinglePlayer(column, row);
		}
		else {
			CheckAndPlacePiece_TwoPlayer(column, row);
		}

	}

	void GameState::CheckAndPlacePiece_SinglePlayer(int column, int row) {


		if (gridArray[column - 1][row - 1] == EMPTY) {
			gridArray[column - 1][row - 1] = turn;
			if (PLAYER_ONE_PIECE == turn) {
				_gridPieces[column - 1][row - 1].setTexture(this->_data->assets.GetTexture("X Piece"));
				this->CheckForWin(turn, true);
			}
			_gridPieces[column - 1][row - 1].setColor(sf::Color(255, 255, 255, 255));
		}

	}

	void GameState::CheckAndPlacePiece_TwoPlayer(int column, int row) {
		

		if (gridArray[column - 1][row - 1] == EMPTY) {
			gridArray[column - 1][row - 1] = turn;
			if (PLAYER_ONE_PIECE == turn) {
				_gridPieces[column - 1][row - 1].setTexture(this->_data->assets.GetTexture("X Piece"));
				this->CheckForWin(turn, false);
				turn = PLAYER_TWO_PIECE;

			}
			else if (PLAYER_TWO_PIECE == turn) {
				_gridPieces[column - 1][row - 1].setTexture(this->_data->assets.GetTexture("O Piece"));
				this->CheckForWin(turn, false);
				turn = PLAYER_ONE_PIECE;
			}
			_gridPieces[column - 1][row - 1].setColor(sf::Color(255, 255, 255, 255));
		}

	}

	int GameState::GetColumn(sf::Vector2f gridLocalTouchPos, sf::Vector2f gridSectionSize, sf::FloatRect gridSize)
	{
		if (gridLocalTouchPos.x < gridSectionSize.x) {
			return 1;
		}
		else if (gridLocalTouchPos.x < gridSectionSize.x * 2) {
			return 2;
		}
		else if (gridLocalTouchPos.x < gridSize.width) {
			return 3;
		}
	}

	int GameState::GetRow(sf::Vector2f gridLocalTouchPos, sf::Vector2f gridSectionSize, sf::FloatRect gridSize)
	{
		if (gridLocalTouchPos.y < gridSectionSize.y) {
			return 1;
		}
		else if (gridLocalTouchPos.y < gridSectionSize.y * 2) {
			return 2;
		}
		else if (gridLocalTouchPos.y < gridSize.height) {
			return 3;
		}
	}

	void GameState::CheckPieces(int playerTurn, bool isSinglePlayer) {
		Check3PeicesForMatch(0, 0, 1, 0, 2, 0, playerTurn, isSinglePlayer);
		Check3PeicesForMatch(0, 1, 1, 1, 2, 1, playerTurn, isSinglePlayer);
		Check3PeicesForMatch(0, 2, 1, 2, 2, 2, playerTurn, isSinglePlayer);
		Check3PeicesForMatch(0, 0, 0, 1, 0, 2, playerTurn, isSinglePlayer);
		Check3PeicesForMatch(1, 0, 1, 1, 1, 2, playerTurn, isSinglePlayer);
		Check3PeicesForMatch(2, 0, 2, 1, 2, 2, playerTurn, isSinglePlayer);
		Check3PeicesForMatch(0, 0, 1, 1, 2, 2, playerTurn, isSinglePlayer);
		Check3PeicesForMatch(0, 2, 1, 1, 2, 0, playerTurn, isSinglePlayer);
	}

	void GameState::CheckForWin(int turn, bool isSinglePlayer) {
		CheckPieces(turn, true);

		if (isSinglePlayer) {
			if (STATE_WON != gameState) {
				gameState = STATE_AI_PLAYING;
				ai->PlacePiece(&gridArray, _gridPieces, &gameState);
				CheckPieces(AI_PIECE, true);
			}
		}

		int emptyNum = 9;
		for (int x = 0; x < 3; x++) {
			for (int y = 0; y < 3; y++) {
				if (EMPTY != gridArray[x][y]) {
					emptyNum--;
				}
			}
		}
		if (IsGameDrawn(emptyNum)) {
			gameState = STATE_DRAW;
			std::cout << "Game Drawn" << std::endl;
		}
		if (IsGameOver()) {
			//restart clock to wait for time to show game over 
			this->_clock.restart();
		}
	}

	void GameState::Check3PeicesForMatch(int x1, int y1, int x2, int y2, int x3, int y3, int pieceToCheck, bool isSinglePlayer) {

		if (pieceToCheck == gridArray[x1][y1] && pieceToCheck == gridArray[x2][y2] && pieceToCheck == gridArray[x3][y3]) {
			std::string winningPieceStr;
			if (O == pieceToCheck) {
				winningPieceStr = "O Win Piece";
			}
			else {
				winningPieceStr = "X Win Piece";
			}
			_gridPieces[x1][y1].setTexture(this->_data->assets.GetTexture(winningPieceStr));
			_gridPieces[x2][y2].setTexture(this->_data->assets.GetTexture(winningPieceStr));
			_gridPieces[x3][y3].setTexture(this->_data->assets.GetTexture(winningPieceStr));

			if (PLAYER_ONE_PIECE == pieceToCheck) {
				gameState = STATE_WON;
				if (isSinglePlayer) {
					std::cout << "WINNER" << std::endl;
				}
				else {
					std::cout << "PLAYER 1 WINS" << std::endl;
				}
			}
			else {
				gameState = STATE_LOSE;
				if (isSinglePlayer) {
					std::cout << "LOSER" << std::endl;
				}
				else {
					std::cout << "PLAYER 2 WINS" << std::endl;
				}

			}
		}
	}

	bool GameState::IsGameDrawn(int emptyNum) {
		return emptyNum == 0 && STATE_WON != gameState && STATE_LOSE != gameState;
	}

	bool GameState::IsGameOver() {
		return gameState == STATE_WON || gameState == STATE_DRAW || gameState == STATE_LOSE;
	}

}