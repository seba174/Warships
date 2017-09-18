#pragma once
#include <vector>
#include <memory>
#include "Ships_HP.h"
#include "Ships.h"


class Player
{
public:
	Ships_HP HP;
	static const int maximumPlayerNameSize = 10;

private:
	sf::Vector2i boardDimensions;
	sf::Vector2f squareSize;
	sf::Vector2f enemySetPoints;
	sf::Vector2f playerSetPoints;
	sf::RectangleShape missedShot;
	sf::RectangleShape hit;

	sf::RectangleShape& rect;
	std::wstring name;
	sf::Vector2i cursorPosition;
	bool playerMoved = false;
	unsigned int totalShots, totalHits;
	bool counterToSet = false;
	unsigned int maximumHitsTemp, maximumHits, maximumMissesTemp, maximumMisses;

	//number of ships in game
	const int countOfShips = 6;

	int mapSize;
	bool shipsSetUp;
	int counter = 0;

	std::vector<std::unique_ptr<Board>> setShips;
	std::vector<std::vector<int>> playerShips;
	std::vector<std::vector<int>>* enemyShips;
	std::vector<std::vector<sf::RectangleShape>> squareTab2;

		// FUNCTIONS
	void updateMaximumHits();

	void updateMaximumMisses();

public:
	Player(const sf::Vector2i& dim, const sf::Vector2f& SquareSize, const sf::Vector2f& enemy_setpoints, std::vector<std::vector<int>>* enemy_ships,
		const sf::Vector2f& player_setpoints, const sf::RectangleShape& missedShot, const sf::RectangleShape& hit, sf::RectangleShape& rect);

	bool playerMoves(const sf::Vector2i& position);

	void playerMouseInput(const sf::Time& dt, const sf::Vector2f& mousepos);

	void playerSetShips(const sf::Vector2f & position, std::vector<Board*>& vect_ship_to_draw);

	void draw(sf::RenderTarget& Window) const;

	void drawSquareTab(sf::RenderTarget& target, sf::RenderStates states) const;

	void setPlayersCursorPositon(const sf::Vector2i& newPos) { cursorPosition = newPos; }

	sf::Vector2i getPlayersCursorPosition() const { return cursorPosition; }

	bool isMouseInEnemyBounds(const sf::Vector2f& mousepos) const;

	void resetSquareTab(int num, std::vector<std::vector<sf::RectangleShape>>& newSquareTab);

	// returns accuracy of Player in range [0-100]
	float returnAccuracy() const;

	sf::Vector2i getRectPositionInGame() const
	{
		return sf::Vector2i(static_cast<int>(round((rect.getPosition().x - enemySetPoints.x) / squareSize.x)),
			static_cast<int>(round((rect.getPosition().y - enemySetPoints.y) / squareSize.y)));
	}

	void setPlaceShip() { setShips[counter]->setPlaceShip(true); }

	std::vector<std::vector<int>>* getPlayerShips() { return &playerShips;}

	void setEnemyShips(std::vector<std::vector<int>>* ships) { enemyShips = ships; }

	// returns true if Player has set its ships
	// returns false otherwise
	bool getShipsSetUp() const { return shipsSetUp; }

	bool& getPlayerMoved() { return playerMoved; }

	void rotateShip() { setShips[counter]->rotateShip(); }

	std::vector<std::vector<sf::RectangleShape>>& returnSquareTab() { return squareTab2; }

	void setPlayerName(const std::wstring& newName) { name = newName; }

	std::wstring getPlayerName() const { return name; }

	unsigned int returnTotalShotsNumber()const { return totalShots; }

	unsigned int returnTotalHitsNumber() const { return totalHits; }

	unsigned int retrunMaximumHits() { updateMaximumHits(); return maximumHits; }

	unsigned int returnMaximumMisses() { updateMaximumMisses(); return maximumMisses; }
};

