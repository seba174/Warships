#pragma once
#include "SFML/Graphics.hpp"
#include "FinishStars.h"

class FinishStarsWithText
	: public sf::Drawable
{
	FinishStars stars;
	sf::Text text;
	sf::RectangleShape additionalTexture;
	int additionalTextureOffset;

	sf::Vector2f centerPosition;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	FinishStarsWithText(const sf::Vector2f& wholeSize, const sf::Vector2f& starSize, const sf::Vector2f& centerPosition, int fontSize);

	void clickStars(int numberOfStars, const sf::Time& dt) { stars.clickStars(numberOfStars, dt); }

	void setTextString(const std::wstring& newString);

	void setAdditionalTexture(const sf::Texture* newTexture) { additionalTexture.setTexture(newTexture); additionalTexture.setFillColor(sf::Color::White);}

	void setAdditionalTextureOffset(int newOffset) { additionalTextureOffset = newOffset; setTextString(text.getString()); }
};

