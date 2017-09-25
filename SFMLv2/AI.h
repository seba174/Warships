#pragma once
#include "Ships_HP.h"
#include "Ships.h"

class DVector2i;

class Info
{
public:
	sf::Vector2i position;

	int what_hit;

	Info(const sf::Vector2i & position = sf::Vector2i(0,0), int what_hit = 0);
};


class AI
	: public sf::Drawable
{
public:
	Ships_HP HP;
private:

	sf::Vector2i boardDimensions;
	sf::Vector2f squareSize;
	sf::Vector2f enemySetPoints;
	sf::Vector2f AISetPoints;
	sf::RectangleShape missedShot;
	sf::RectangleShape hit;
	bool shipsSetUp;
	bool first = true;

	std::vector<std::vector<sf::RectangleShape>> squareTab2;
	std::vector<std::unique_ptr<Board>> setShips;
	std::vector<std::vector<int>> AIShips;
	const std::vector<std::vector<int>>* enemyShips;
	std::vector<std::vector<int>> modifiedEnemyShips;
	int mapSize;

	//number of ships in game
	const int countOfShips = 6;

	std::wstring name;
	unsigned int totalShots, totalHits;
	unsigned int maximumHitsTemp, maximumHits, maximumMissesTemp, maximumMisses;
	sf::RectangleShape& rect;

	Info last;
	int count = 0;
	bool shootWithBounds = false;
	std::random_device rd;
	std::mt19937 mt;

	// FUNCTIONS

// checks if there is any ship or missed shot in surrounding of given position
	bool checkSurround(const sf::Vector2i& pos, const std::vector<std::vector<int>>& ships) const;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void updateMaximumHits();
	void updateMaximumMisses();
	void actionsAfterHittingStandardShip(int size);
	void actionsAfterHittingIrregular2();
	void actionsAfterHittingIrregular3();

	Info attackWithBounds(const sf::Vector2i& boundsX, const sf::Vector2i& boundsY);

	Info attack();

	void modifiedSetMinus1();

	void copyPlayerShips();

	bool isOnMap(const sf::Vector2i& pos) const;

	void setModifiedValue(const sf::Vector2i& pos, int num, int ship_num);

	DVector2i giveBounds(const sf::Vector2i& pos) const;

public:

	AI(const sf::Vector2i& dim, const sf::Vector2f& SquareSize, const sf::Vector2f& enemy_setpoints, std::vector<std::vector<int>>* enemy_ships,
		const sf::Vector2f& player_setpoints, const sf::RectangleShape& missedShot, const sf::RectangleShape& hit, sf::RectangleShape& rect);

	void placeShips(std::vector<Board*>& VectRect);

	// returns true when AI misses
	// returns false when AI hits target
	bool AIMovesLevelEasy();

	// returns true when AI misses
	// returns false when AI hits target
	bool AIMovesLevelMedium();

	// returns true when AI misses
	// returns false when AI hits target
	bool AIMovesLevelHard(bool& wasAIUsingSuperPowers);

	void resetSquareTab(int num);

	// returns accuracy of AI in range [0-100]
	float returnAccuracy() const;

	void drawSquareTab(sf::RenderTarget& target, sf::RenderStates states) const;

	// returns true if AI has set its ships
	// returns false otherwise
	bool getShipsSetUp() const { return shipsSetUp; }

	std::vector<std::vector<int>>* getAIShips() { return &AIShips; }

	void setEnemyShips(std::vector<std::vector<int>>* ships) { enemyShips = ships; }

	void setPlayerName(const std::wstring& newName) { name = newName; }

	std::wstring getPlayerName() const { return name; }

	unsigned int returnTotalShotsNumber() const { return totalShots; }

	unsigned int returnTotalHitsNumber() const { return totalHits; }

	unsigned int retrunMaximumHits() { updateMaximumHits(); return maximumHits; }

	unsigned int returnMaximumMisses() { updateMaximumMisses(); return maximumMisses; }
};