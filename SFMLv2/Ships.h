#pragma once
#include "Board.h"

class Ships: public Board
{
	int size;
	bool rotation_horizontally;
	sf::RectangleShape shipv2;
	bool placeShip;

public:
	Ships(int size, sf::Vector2f squaresize, sf::Vector2i boarddimensions, sf::Vector2f setPoints, sf::Texture* texture);
	void setPosition(const sf::Vector2f mousepos); 
	void setPositionWithoutCheck(const sf::Vector2f newposition);
	bool CanChangePositionX(const sf::Vector2f newposition) const;
	bool CanChangePositionY(const sf::Vector2f newposition) const;
	sf::RectangleShape& return_ship();
	bool getplaceShip() const;
	void setplaceShip(bool set);
	void rotate_ship();
	bool placePlayerShip(int **ships, int tabs_size, std::vector<Board*>&, sf::Texture* texture);
	void updateTexture(const sf::Time& timen);
};

