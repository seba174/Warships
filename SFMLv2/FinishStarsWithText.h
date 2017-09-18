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
	// starSize is a size for ONE star
	// position is a position of the center of object
	FinishStarsWithText(const sf::Vector2f& wholeSize, const sf::Vector2f& starSize, const sf::Vector2f& centerPosition, int fontSize);

	void setTextString(const std::wstring& newString);

	// function animates stars shining
	// numberOfStars is a mapSize of stars to shine
	void clickStars(int numberOfStars, const sf::Time& dt) { stars.clickStars(numberOfStars, dt); }

	// sets additionalTexture
	// additionalTexture is to the left of the text
	void setAdditionalTexture(const sf::Texture* newTexture) { additionalTexture.setTexture(newTexture); additionalTexture.setFillColor(sf::Color::White);}

	// sets additional space between texture and text (texutre is to the left of the text)
	void setAdditionalTextureOffset(int newOffset) { additionalTextureOffset = newOffset; setTextString(text.getString()); }
};

