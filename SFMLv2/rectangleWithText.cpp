#include "rectangleWithText.h"

rectangleWithText::rectangleWithText()
	: position(0,0)
{
}

void rectangleWithText::setTextPosition()
{
	text.setPosition(sf::Vector2f(rect.getPosition().x - text.getGlobalBounds().width / 2, rect.getPosition().y - text.getGlobalBounds().height / 2));
}

void rectangleWithText::setOrigin()
{
	rect.setOrigin(rect.getSize().x / 2, rect.getSize().y / 2);
}

void rectangleWithText::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(rect, states);
	target.draw(text, states);
}

void rectangleWithText::setString(const std::wstring & newString)
{
	text.setString(newString);
	setTextPosition();
}

void rectangleWithText::setSize(const sf::Vector2f & size)
{
	rect.setSize(size);
	setOrigin();
	setPosition(position);
}

void rectangleWithText::setPosition(const sf::Vector2f & pos)
{
	position = pos;
	rect.setPosition(pos);
	setTextPosition();
}

void rectangleWithText::setFontSize(float fontSize)
{
	text.setCharacterSize(fontSize);
}

void rectangleWithText::setFont(const sf::Font & font)
{
	text.setFont(font);
}

