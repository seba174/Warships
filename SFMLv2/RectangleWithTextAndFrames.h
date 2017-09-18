#pragma once
#include "RectangleWithText.h"


class RectangleWithTextAndFrames :
	public RectangleWithText
{
	sf::RectangleShape secondRect;
	unsigned int additionalSecondRectSize;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	RectangleWithTextAndFrames();

	// sets size of rectangle
	void setSize(const sf::Vector2f& size);

	// sets position of the center of rectangle
	void setPosition(const sf::Vector2f& pos);

	void setFillColor(const sf::Color& color);

	void setAdditionalSecondRectSize(unsigned int newSize) { additionalSecondRectSize = newSize; }

	void setOutlineColor(const sf::Color& color);

	void setOutlineThickness(float thickness);

};

