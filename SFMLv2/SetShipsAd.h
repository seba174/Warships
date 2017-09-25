#pragma once

class SetShipsAd
	: public sf::Drawable
{

	sf::RectangleShape background;
	sf::RectangleShape logo;
	sf::Text text;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	SetShipsAd(const sf::Vector2i & boardDimensions, const sf::Vector2f& setPoint, float interfaceScale);

	void setLogoSize(const sf::Vector2f& logoSize);

	void setLogoPosition(const sf::Vector2f& logoPosition);
};

