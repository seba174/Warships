#include "stdafx.h"
#include "FinishStarsWithText.h"
#include "FontHandler.h"


void FinishStarsWithText::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(stars, states);
	target.draw(additionalTexture, states);
	target.draw(text, states);
}

FinishStarsWithText::FinishStarsWithText(const sf::Vector2f & wholeSize, const sf::Vector2f & starSize, const sf::Vector2f & centerPosition, int fontSize)
	:stars(starSize, sf::Vector2f(centerPosition.x + wholeSize.x / 2 - (static_cast<float>(FinishStars::numberOfStars) / 2)*starSize.x, centerPosition.y)),
	centerPosition(centerPosition), 
	additionalTextureOffset(0)
{
	text.setCharacterSize(fontSize);
	text.setFont(FontHandler::getInstance().font_handler["Mecha"]);
	text.setPosition(sf::Vector2f(centerPosition.x - wholeSize.x / 2, centerPosition.y - text.getGlobalBounds().height / 2));
	additionalTexture.setSize(sf::Vector2f(wholeSize.y, wholeSize.y));
	additionalTexture.setFillColor(sf::Color::Transparent);
	additionalTexture.setOrigin(sf::Vector2f(additionalTexture.getSize().x, additionalTexture.getSize().y / 2));
}

void FinishStarsWithText::setTextString(const std::wstring & newString)
{
	text.setString(newString);
	text.setPosition(sf::Vector2f(text.getPosition().x, centerPosition.y - text.getGlobalBounds().height / 2));
	additionalTexture.setPosition(text.getPosition().x - additionalTextureOffset, centerPosition.y);
}

