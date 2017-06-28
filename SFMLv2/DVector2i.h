#pragma once
#include <SFML\Graphics.hpp>

class DVector2i
{
public:
	sf::Vector2i boundsX;
	sf::Vector2i boundsY;
	DVector2i(sf::Vector2i boundsX, sf::Vector2i boundsY);
};
