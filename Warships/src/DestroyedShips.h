#pragma once

enum shipOrder {Ship5, Ship4, Ship2x4, Ship3, Ship2, Ship2x2};

class DestroyedShips
	: public sf::Drawable
{
protected:
	// number of ships in game
	const int count_of_ships = 6;

	std::vector<sf::RectangleShape> vec_ships;
	sf::Text info;
	sf::Vector2i boardDimensions;
	sf::Vector2f squareSize;
	sf::Vector2f setPoint;
	float interfaceScale;

	// color of destroyed ship (initialized in constructor)
	sf::Color destroyed;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	// NOTE: boardDimensions must be large enought to cover all ships, if it is not, the ships will overlap	
	// setPoint is a vector used to set position of ships
	DestroyedShips(const sf::Vector2i & boardDimensions, const sf::Vector2f& squareSize, const sf::Vector2f& setPoint, float interfaceSacle);

	// sets additional Y offset to setPoint position given while constructing
	void setPosition(int y);

	// marks ship of given number destroyed
	void markDestroyed(unsigned int number);

	void setDisplayedString(const std::wstring& str) { info.setString(str); setPosition(0); }

	virtual ~DestroyedShips() {};
};

