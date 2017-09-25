#pragma once

class RectangleWithText
	: public sf::Drawable
{
protected:
	sf::RectangleShape rect;
	sf::Text text;
	sf::Vector2f position;

	// FUNCTIONS

	// sets text position in the center of rect
	void setTextPosition();

	// sets origin of the rect to it's center
	void setOrigin();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	// default constructor
	RectangleWithText();

	void setString(const std::wstring& newString);

	// sets size of rectangle
	void setSize(const sf::Vector2f& size);

	// sets position of the center of rectangle
	void setPosition(const sf::Vector2f& pos);

	void setFontSize(float fontSize);

	void setFont(const sf::Font& font);

	std::wstring getString() const { return text.getString(); }

	sf::Vector2f getSize() const { return rect.getSize(); }
};

