#pragma once
#include "Board.h"


class IrregularShip2 :
	public Board
{
	sf::RectangleShape shipv2;
	bool placeShip;

	void setPositionWithoutCheck(const sf::Vector2f& newposition) { shipv2.setPosition(newposition); }

	bool CanChangePositionX(const sf::Vector2f& newposition) const;

	bool CanChangePositionY(const sf::Vector2f& newposition) const;

public:
	IrregularShip2(const sf::Vector2f& squaresize, const sf::Vector2i& boarddimensions, const sf::Vector2f& setPoints, sf::Texture* texture);

	void setPosition(const sf::Vector2f& mousepos);

	sf::RectangleShape& returnShip() { return shipv2; }

	bool getPlaceShip() const { return placeShip; }

	void setPlaceShip(bool set) { placeShip = set; }

	void rotateShip();

	bool placePlayerShip(std::vector<std::vector<int>>& ships, int tabs_size, std::vector<Board*>&);

	void updateTexture(const sf::Time&);

	void setDestroyedTexture();

	void setAlphaChannel(unsigned alpha);
};

