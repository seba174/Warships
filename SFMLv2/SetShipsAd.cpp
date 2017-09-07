#include "SetShipsAd.h"
#include "FontHandler.h"
#include "TextureHandler.h"



void SetShipsAd::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(background, states);
	target.draw(logo, states);
	target.draw(text, states);
}

SetShipsAd::SetShipsAd(const sf::Vector2i & boardDimensions, const sf::Vector2f & setPoint, float interfaceScale)
	:background(sf::Vector2f(static_cast<float>(boardDimensions.x), static_cast<float>(boardDimensions.y)))
{
	float fontSize = 70;
	logo.setTexture(&TextureHandler::getInstance().texture_handler["logo"]);

	sf::Color background_color(0, 0, 0, 225);
	background.setPosition(setPoint);
	background.setFillColor(background_color);

	text.setString(std::string("Warships"));
	text.setFont(FontHandler::getInstance().font_handler["Mecha"]);
	text.setCharacterSize(fontSize * interfaceScale);
	text.setPosition(sf::Vector2f(static_cast<float>(boardDimensions.x / 2 + setPoint.x-text.getGlobalBounds().width/2), static_cast<float>(boardDimensions.y / 2 + setPoint.y-text.getGlobalBounds().height)));
}

void SetShipsAd::setLogoSize(const sf::Vector2f & logoSize)
{
	logo.setSize(logoSize);
	logo.setOrigin(logoSize.x / 2, logoSize.y / 2);
}

void SetShipsAd::setLogoPosition(const sf::Vector2f & logoPosition)
{
	logo.setPosition(logoPosition);
}

