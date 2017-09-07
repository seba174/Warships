#pragma once
#include "SFML\Graphics.hpp"

class rectangleWithText
	: public sf::Drawable
{
	sf::RectangleShape rect;
	sf::Text text;
	sf::Vector2f position;

	// FUNCTIONS
	void setTextPosition();
	void setOrigin();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	rectangleWithText();

	void setString(const std::wstring& newString);

	void setSize(const sf::Vector2f& size);

	void setPosition(const sf::Vector2f& pos);

	void setFontSize(float fontSize);

	void setFont(const sf::Font& font);

	sf::Vector2f getSize() const { return rect.getSize(); }
};

