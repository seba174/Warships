#pragma once
#include "Board.h"

class Ships
	: public Board
{
	int size;
	bool rotation_horizontally;
	sf::RectangleShape shipv2;
	bool placeShip;

public:
	Ships(int size, const sf::Vector2f& squaresize, const sf::Vector2i& boarddimensions, const sf::Vector2f& setPoints, sf::Texture* texture);

	void setPosition(const sf::Vector2f& mousepos);

	void setPositionWithoutCheck(const sf::Vector2f& newposition) { shipv2.setPosition(newposition); }

	bool CanChangePositionX(const sf::Vector2f& newposition) const;

	bool CanChangePositionY(const sf::Vector2f& newposition) const;

	sf::RectangleShape& return_ship() { return shipv2; }

	bool getplaceShip() const { return placeShip; }

	void setplaceShip(bool set) { placeShip = set; }

	void rotate_ship();

	bool placePlayerShip(int **ships, int tabs_size, std::vector<Board*>&);

	void updateTexture(const sf::Time& timen);

	void setDestroyedTexture();
};

