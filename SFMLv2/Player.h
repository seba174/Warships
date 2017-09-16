#pragma once
#include "Ships_HP.h"
#include "Ships.h"


class Player
{
public:
	Ships_HP HP;
	static const int maximumPlayerNameSize = 10;

protected:
	sf::Vector2i boardDimensions;
	sf::Vector2f squareSize;
	sf::Vector2f enemySetPoints;
	sf::Vector2f playerSetPoints;
	unsigned int totalShots, totalHits;
	bool counterToSet = false;
	unsigned int maximumHitsTemp, maximumHits, maximumMissesTemp, maximumMisses;

	Board** setShips;
	bool shipsSetUp;
	int counter = 0;

	//mapSize of ships in game
	const int countOfShips = 6;

	int** playerShips;
	int **enemyShips;
	sf::RectangleShape** squareTab2;
	sf::RectangleShape missedShot;
	sf::RectangleShape hit;
	bool playerMoved = false;
	int mapSize;
	sf::Vector2i cursorPosition;
	std::wstring name;
	sf::RectangleShape& rect;

	void updateMaximumHits();
	void updateMaximumMisses();

public:
	Player(const sf::Vector2i& dim, const sf::Vector2f& SquareSize, const sf::Vector2f& enemy_setpoints, int** enemy_ships, const sf::Vector2f& player_setpoints,
		const sf::RectangleShape& missedShot, const sf::RectangleShape& hit, sf::RectangleShape** square_tab_2, sf::RectangleShape& rect);

	bool playerMoves(const sf::Vector2i& position);

	void playerMouseInput(const sf::Time& dt, const sf::Vector2f& mousepos);

	void playerSetShips(const sf::Vector2f & position, std::vector<Board*>& vect_ship_to_draw);

	void draw(sf::RenderTarget& Window) const;

	void setPlayersCursorPositon(const sf::Vector2i& newPos) { cursorPosition = newPos; }

	sf::Vector2i getPlayersCursorPosition() const { return cursorPosition; }

	bool isMouseInEnemyBounds(const sf::Vector2f& mousepos) const;

	void resetSquareTab(int num, sf::RectangleShape** newSquareTab);

	float returnAccuracy() const;

	~Player();

	sf::Vector2i getRectPositionInGame() const
	{
		return sf::Vector2i(static_cast<int>(round((rect.getPosition().x - enemySetPoints.x) / squareSize.x)),
			static_cast<int>(round((rect.getPosition().y - enemySetPoints.y) / squareSize.y)));
	}

	void setPlaceShip() { setShips[counter]->setplaceShip(true); }

	int** getPlayerShips() { return playerShips; }

	void setEnemyShips(int ** ships) { enemyShips = ships; }

	bool getShipsSetUp() const { return shipsSetUp; }

	bool& getPlayerMoved() { return playerMoved; }

	void rotateShip() { setShips[counter]->rotate_ship(); }

	sf::RectangleShape** returnSquareTab() { return squareTab2; }

	void setPlayerName(const std::wstring& newName) { name = newName; }

	std::wstring getPlayerName() const { return name; }

	unsigned int returnTotalShotsNumber()const { return totalShots; }

	unsigned int returnTotalHitsNumber() const { return totalHits; }

	unsigned int retrunMaximumHits() { updateMaximumHits(); return maximumHits; }

	unsigned int returnMaximumMisses() { updateMaximumMisses(); return maximumMisses; }
};

