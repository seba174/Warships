#pragma once
#include <list>
#include "SFML/Graphics.hpp"
#include "rectangleWithText.h"

class multipleTextFrame
	: public sf::Drawable
{
	std::list<rectangleWithText> frames;
	sf::Vector2f position;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	multipleTextFrame(unsigned int numberOfFrames);

	bool setStrings(const std::list<std::wstring>& stringList);

	void setPosition(const sf::Vector2f& position);

	void setSize(const sf::Vector2f& size);

	void setFontSize(float fontSize);

	void setFont(const sf::Font& font);
};

