#pragma once
#include <random>
#include "Board.h"

class Info
{
public:
	sf::Vector2i position;
	int what_hit;

	Info(sf::Vector2i position = sf::Vector2i(0,0), int what_hit = 0);
};


class AI
{
protected:
	sf::Vector2i BoardDimensions;
	sf::Vector2f& SquareSize;
	sf::Vector2f Player_SetPoints;
	
	int** ships;

	int number;
	std::random_device rd;
	std::mt19937 mt;

public:

	AI(const sf::Vector2i dim, sf::Vector2f& SquareSize, const sf::Vector2f player_setpoints);
	void place_ships(std::vector<Board*>& VectRect, Board**, int);

	Info attack_with_bounds(int ** ships, const sf::Vector2i boundsX, const sf::Vector2i boundsY);
	Info attack(int **ships);
	int** get_AI_ships() { return ships; }
	virtual ~AI();
};