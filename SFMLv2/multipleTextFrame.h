#pragma once
#include "RectangleWithText.h"

class MultipleTextFrame
	: public sf::Drawable
{
	std::list<RectangleWithText> frames;
	sf::Vector2f position;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	MultipleTextFrame(unsigned int numberOfFrames);

	// sets string for all text frames
	// NOTE that stringList size and mapSize of textFrames of object must be the same
	// returns false when sizes of stringList and mapSize of textFrames are not equal
	bool setStrings(const std::list<std::wstring>& stringList);

	// sets position of the center of all textFrames
	void setPosition(const sf::Vector2f& position);

	// sets size for ONE textFrame
	// NOTE that all of textFrames have always the same size
	void setSize(const sf::Vector2f& size);

	void setFontSize(float fontSize);

	void setFont(const sf::Font& font);
	
	// gets a list with wstrings from all textFrames
	std::list<std::wstring> getStrings() const;
};

