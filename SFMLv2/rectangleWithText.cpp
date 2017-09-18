#include "RectangleWithText.h"

RectangleWithText::RectangleWithText()
	: position(0,0)
{
	rect.setFillColor(sf::Color::Black);
}

void RectangleWithText::setTextPosition()
{
	text.setPosition(sf::Vector2f(rect.getPosition().x - text.getGlobalBounds().width / 2, rect.getPosition().y - (text.getLocalBounds().top + text.getLocalBounds().height / 2)));
}

void RectangleWithText::setOrigin()
{
	rect.setOrigin(rect.getSize().x / 2, rect.getSize().y / 2);
}

void RectangleWithText::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(rect, states);
	target.draw(text, states);
}

void RectangleWithText::setString(const std::wstring & newString)
{
	text.setString(newString);
	setTextPosition();
}

void RectangleWithText::setSize(const sf::Vector2f & size)
{
	rect.setSize(size);
	setOrigin();
	setPosition(position);
}

void RectangleWithText::setPosition(const sf::Vector2f & pos)
{
	position = pos;
	rect.setPosition(pos);
	setTextPosition();
}

void RectangleWithText::setFontSize(float fontSize)
{
	text.setCharacterSize(static_cast<unsigned>(fontSize));
}

void RectangleWithText::setFont(const sf::Font & font)
{
	text.setFont(font);
}

