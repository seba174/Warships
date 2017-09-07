#pragma once
#include "DestroyedShips.h"

class LanguageManager;

class DestroyedShipsWithBackground :
	public DestroyedShips
{
	sf::RectangleShape background;
	sf::Text time;
	sf::Vector2f timePos;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void setTimePosition();

public:

	DestroyedShipsWithBackground(const sf::Vector2i & boardDimensions, const sf::Vector2f& squareSize, const sf::Vector2f& setPoint, float interfaceScale, LanguageManager& langMan);

	void setTimeString(const std::wstring& newTime, LanguageManager& langMan);

	void setTimeFontSize(float fontSize) { time.setCharacterSize(fontSize); setTimePosition(); }

	virtual ~DestroyedShipsWithBackground() {};
};

