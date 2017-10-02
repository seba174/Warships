#include "stdafx.h"
#include "CenteredText.h"


void CenteredText::setOrginInCenter()
{
	sf::FloatRect textRect = getLocalBounds();
	Text::setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
}

CenteredText::CenteredText()
	: Text()
{
}

void CenteredText::setPosition(float x, float y)
{
	setOrginInCenter();
	Text::setPosition(x, y);
}

void CenteredText::setPosition(const sf::Vector2f & position)
{
	setOrginInCenter();
	Text::setPosition(position);
}

