#pragma once
#include <random>
#include "Board.h"

class Info
{
public:
	sf::Vector2i position;
	int what_hit;

	Info(const sf::Vector2i & position = sf::Vector2i(0,0), int what_hit = 0);
};


class AI
{
protected:
	sf::Vector2i BoardDimensions;
	sf::Vector2f SquareSize;
	sf::Vector2f Enemy_SetPoints;
	sf::Vector2f AI_SetPoints;
	unsigned int totalShots, totalHits;
	bool counter_to_set = false;
	unsigned int maximumHitsTemp, maximumHits, maximumMissesTemp, maximumMisses;
	
	int** AI_ships;
	int **enemy_ships;
	int **modified_enemy_ships;

	int number;
	std::random_device rd;
	std::mt19937 mt;

	// checks if there is any ship or missed shot in surrounding of given position
	bool checkSurround(const sf::Vector2i& pos, int** ships) const;

public:

	AI(const sf::Vector2i& dim, const sf::Vector2f& SquareSize, const sf::Vector2f& player_setpoints);

	void place_ships(std::vector<Board*>& VectRect, Board**, int);

	Info attack_with_bounds(int ** ships, const sf::Vector2i& boundsX, const sf::Vector2i& boundsY);

	Info attack(int **ships);

	int** get_AI_ships() { return AI_ships; }

	virtual ~AI();
};