#pragma once

class DVector2i
{
public:
	sf::Vector2i boundsX;
	sf::Vector2i boundsY;

	DVector2i(const sf::Vector2i & boundsX, const sf::Vector2i & boundsY)
		: boundsX(boundsX), boundsY(boundsY) {}
};
