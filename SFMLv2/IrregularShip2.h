#pragma once
#include "Board.h"


class IrregularShip2 :
	public Board
{
	sf::RectangleShape shipv2;
	bool placeShip;

public:
	IrregularShip2(const sf::Vector2f& squaresize, const sf::Vector2i& boarddimensions, const sf::Vector2f& setPoints, sf::Texture* texture);

	bool CanChangePositionX(const sf::Vector2f& newposition) const;

	bool CanChangePositionY(const sf::Vector2f& newposition) const;

	void setPosition(const sf::Vector2f& mousepos);

	void setPositionWithoutCheck(const sf::Vector2f& newposition) { shipv2.setPosition(newposition); }

	sf::RectangleShape& return_ship() { return shipv2; }

	bool getplaceShip() const { return placeShip; }

	void setplaceShip(bool set) { placeShip = set; }

	void rotate_ship();

	bool placePlayerShip(int **ships, int tabs_size, std::vector<Board*>&);

	void updateTexture(const sf::Time&);

	void setDestroyedTexture();
};

