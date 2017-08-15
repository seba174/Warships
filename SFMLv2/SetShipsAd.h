#pragma once
#include <SFML\Graphics.hpp>


class SetShipsAd
	: public sf::Drawable
{

	sf::RectangleShape background;
	sf::Text text;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	SetShipsAd(const sf::Vector2i & boardDimensions, const sf::Vector2f& setPoint, float interfaceScale);
};

