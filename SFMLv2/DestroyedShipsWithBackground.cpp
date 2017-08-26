#include "DestroyedShipsWithBackground.h"



void DestroyedShipsWithBackground::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(background, states);
	DestroyedShips::draw(target, states);
}

DestroyedShipsWithBackground::DestroyedShipsWithBackground(const sf::Vector2i & boardDimensions, const sf::Vector2f & squareSize, const sf::Vector2f & setPoint, float interfaceScale)
	: DestroyedShips(boardDimensions, sf::Vector2f(static_cast<float>(boardDimensions.x)/11, static_cast<float>(boardDimensions.x)/11), setPoint, interfaceScale),
	background(sf::Vector2f(static_cast<float>(boardDimensions.x), static_cast<float>(boardDimensions.y)))
{
	sf::Color background_color(0, 0, 0, 225);
	background.setPosition(setPoint);
	background.setFillColor(background_color);
}
