#pragma once
#include "DestroyedShips.h"



class DestroyedShipsWithBackground :
	public DestroyedShips
{
	sf::RectangleShape background;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:

	DestroyedShipsWithBackground(const sf::Vector2i & boardDimensions, const sf::Vector2f& squareSize, const sf::Vector2f& setPoint, float interfaceScale);

	virtual ~DestroyedShipsWithBackground() {};
};

