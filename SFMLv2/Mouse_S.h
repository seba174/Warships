#pragma once
#include <SFML/Graphics.hpp>


class Mouse_S
{
	sf::Vector2f bounds_x;
	sf::Vector2f bounds_y;
	sf::RenderWindow *window;

public:
	Mouse_S(sf::Vector2f bounds_x, sf::Vector2f bounds_y, sf::RenderWindow *window);
	bool isMouseWithinArea() const;
	sf::Vector2f returnPositionInBounds() const;
};

