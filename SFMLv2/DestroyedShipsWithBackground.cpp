#include "stdafx.h"
#include "DestroyedShipsWithBackground.h"
#include "LanguageManager.h"
#include "FontHandler.h"



void DestroyedShipsWithBackground::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(background, states);
	target.draw(time, states);
	DestroyedShips::draw(target, states);
}

void DestroyedShipsWithBackground::setTimePosition()
{
	time.setOrigin(time.getGlobalBounds().width / 2, time.getGlobalBounds().height / 2);
	time.setPosition(sf::Vector2f(timePos.x, timePos.y - 1.5f*time.getGlobalBounds().height));
}

DestroyedShipsWithBackground::DestroyedShipsWithBackground(const sf::Vector2i & boardDimensions, const sf::Vector2f & squareSize, const sf::Vector2f & setPoint, float interfaceScale,
	LanguageManager& langMan)
	: DestroyedShips(boardDimensions, sf::Vector2f(static_cast<float>(boardDimensions.x)/11, static_cast<float>(boardDimensions.x)/11), setPoint, interfaceScale),
	background(sf::Vector2f(static_cast<float>(boardDimensions.x), static_cast<float>(boardDimensions.y)))
{
	timePos = sf::Vector2f(setPoint.x + boardDimensions.x / 2, setPoint.y + boardDimensions.y);
	time.setFont(FontHandler::getInstance().font_handler["Mecha"]);
	time.setString(langMan.getText("Game time") + L" " + L"00:00");
	sf::Color background_color(0, 0, 0, 225);
	background.setPosition(setPoint);
	background.setFillColor(background_color);
}

void DestroyedShipsWithBackground::setTimeString(const std::wstring & newTime, LanguageManager& langMan)
{
	time.setString(langMan.getText("Game time") + L" " + newTime);
}
