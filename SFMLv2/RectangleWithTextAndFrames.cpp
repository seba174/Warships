#include "stdafx.h"
#include "RectangleWithTextAndFrames.h"


void RectangleWithTextAndFrames::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(secondRect, states);
	RectangleWithText::draw(target, states);
}

RectangleWithTextAndFrames::RectangleWithTextAndFrames()
{
	additionalSecondRectSize = 0;
	secondRect.setFillColor(sf::Color::Black);
}

void RectangleWithTextAndFrames::setSize(const sf::Vector2f & size)
{
	RectangleWithText::setSize(size);
	secondRect.setSize(sf::Vector2f(rect.getSize().x + additionalSecondRectSize, rect.getSize().y + additionalSecondRectSize));
	secondRect.setOrigin(secondRect.getSize().x / 2, secondRect.getSize().y / 2);
	RectangleWithTextAndFrames::setPosition(position);
}

void RectangleWithTextAndFrames::setPosition(const sf::Vector2f & pos)
{
	RectangleWithText::setPosition(pos);
	secondRect.setPosition(rect.getPosition());
}

void RectangleWithTextAndFrames::setFillColor(const sf::Color & color)
{
	rect.setFillColor(color);
	secondRect.setFillColor(color);
}

void RectangleWithTextAndFrames::setOutlineColor(const sf::Color & color)
{
	rect.setOutlineColor(color);
	secondRect.setOutlineColor(color);
}

void RectangleWithTextAndFrames::setOutlineThickness(float thickness)
{
	rect.setOutlineThickness(thickness);
	secondRect.setOutlineThickness(thickness);
}


