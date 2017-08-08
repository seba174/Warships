#include "AI.h"
#include <iostream>



bool AI::checkSurround(const sf::Vector2i & pos, int** ships) const
{
	if (!(pos.x >= 0 && pos.x < number && pos.y >= 0 && pos.y < number))
		return false;
	if (pos.x - 1 >= 0)
		if (!(ships[pos.x - 1][pos.y] != -2))
			return false;
	if (pos.x + 1 < number)
		if (!(ships[pos.x + 1][pos.y] != -2))
			return false;
	if (pos.y - 1 >= 0)
		if (!(ships[pos.x][pos.y - 1] != -2))
			return false;
	if (pos.y + 1 < number)
		if (!(ships[pos.x][pos.y + 1] != -2))
			return false;
	return true;
}

AI::AI(const sf::Vector2i& dim, const sf::Vector2f& SquareSize, const sf::Vector2f& player_setpoints)
	: BoardDimensions(dim), SquareSize(SquareSize), Player_SetPoints(player_setpoints),rd()
{
	number = BoardDimensions.x / SquareSize.x;
	mt = std::mt19937(rd());

	ships = new int*[number];
	for (int i = 0; i < number; i++)
	{
		ships[i] = new int[number];
		for (int j = 0; j < number; j++)
			ships[i][j] = 0;
	}
}

void AI::place_ships(std::vector<Board*>& VectRect, Board** set_ships, int count_of_ships)
{
	int counter = 0;
	std::uniform_int_distribution<int> dist_num(0, number - 1), dist_rot(0, 3);

	while (counter < count_of_ships)
	{
		sf::Vector2f position(dist_num(mt)*SquareSize.x, (dist_num(mt))*SquareSize.y);
		int rotation = dist_rot(mt);
		
		set_ships[counter]->setPosition(position);
		for (int i = 0; i < rotation; i++)
			set_ships[counter]->rotate_ship();
		if (set_ships[counter]->placePlayerShip(ships, number, VectRect, nullptr)) //UWAGA (nullptr czy text)
			counter++;
	}
}

Info AI::attack(int ** ships) 
{
	int counter = 0;
	int max = 10 * number;
	std::uniform_int_distribution<int> dist_num(0, number - 1);
	while (true)
	{
		sf::Vector2i rand(dist_num(mt), dist_num(mt));
		if (counter < max)
		{
			std::cout << "nie_przekroczono" << std::endl;
			if (ships[rand.x][rand.y] != -1 && ships[rand.x][rand.y] != -2 && checkSurround(rand, ships))
				return Info(rand, ships[rand.x][rand.y]);
		}
		else
		{
			std::cout << "przekroczono" << std::endl;
			if (ships[rand.x][rand.y] != -1 && ships[rand.x][rand.y] != -2)
				return Info(rand, ships[rand.x][rand.y]);
		}
		++counter;
	}
}

AI::~AI()
{
	for (int i = 0; i < number; i++)
		delete[] ships[i];
	delete[] ships;
}

Info AI::attack_with_bounds(int ** ships, const sf::Vector2i& boundsX, const sf::Vector2i& boundsY) 
{
	
	std::uniform_int_distribution<int> dist_num_x(boundsX.x, boundsX.y), dist_num_y(boundsY.x, boundsY.y);
	while (true)
	{
		std::cout << "attack_with_bounds" << std::endl;
		sf::Vector2i rand(dist_num_x(mt), dist_num_y(mt));
		if (ships[rand.x][rand.y] != -1 && ships[rand.x][rand.y] != -2)
			return Info(rand, ships[rand.x][rand.y]);
	}
}

Info::Info(const sf::Vector2i & position, int what_hit): position(position), what_hit(what_hit)
{
}
