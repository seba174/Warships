#pragma once
#include "Board.h"


class IrregularShip2 :
	public Board
{
	sf::RectangleShape shipv2;
	bool placeShip;

public:
	IrregularShip2(sf::Vector2f squaresize, sf::Vector2i boarddimensions, sf::Vector2f setPoints, sf::Texture* texture);
	bool CanChangePositionX(const sf::Vector2f newposition) const;
	bool CanChangePositionY(const sf::Vector2f newposition) const;
	void setPosition(const sf::Vector2f mousepos);
	void setPositionWithoutCheck(const sf::Vector2f newposition);
	sf::RectangleShape& return_ship();
	bool getplaceShip() const;
	void setplaceShip(bool set);
	void rotate_ship();
	bool placePlayerShip(int **ships, int tabs_size, std::vector<Board*>&, sf::Texture* texture);
	void updateTexture(const sf::Time&);
};

