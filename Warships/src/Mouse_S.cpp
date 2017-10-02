#include "stdafx.h"
#include "Mouse_S.h"

Mouse_S::Mouse_S(const sf::Vector2f& bounds_x, const sf::Vector2f & bounds_y, sf::RenderWindow *window)
	: bounds_x(bounds_x), bounds_y(bounds_y),window(window)
{
}

bool Mouse_S::isMouseWithinArea() const
{
	sf::Vector2i exp= sf::Mouse::getPosition(*window);
	sf::Vector2f mouseposition = (*window).mapPixelToCoords(exp);
	
	if (mouseposition.x >= bounds_x.x && mouseposition.x <= bounds_x.y)
		if (mouseposition.y >= bounds_y.x&&mouseposition.y <= bounds_y.y)
			return true;
	return false;
}

sf::Vector2f Mouse_S::returnPositionInBounds() const
{
	sf::Vector2i exp = sf::Mouse::getPosition(*window);
	sf::Vector2f mouseposition = (*window).mapPixelToCoords(exp);
	//return sf::Vector2f(sf::Mouse::getPosition(*window).x - bounds_x.x, sf::Mouse::getPosition(*window).y - bounds_y.x);
	return sf::Vector2f(mouseposition.x - bounds_x.x, mouseposition.y - bounds_y.x);
}
