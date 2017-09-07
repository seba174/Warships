#pragma once
#include "SFML/Graphics.hpp"
#include <memory>

class FinishStars
	: public sf::Drawable
{
	std::vector<sf::RectangleShape> stars;

	sf::Color starTransparency = sf::Color(255, 255, 255, 150);
	sf::Time antimationTime;
	sf::Time timeBetweenStars = sf::Time(sf::seconds(0.8));

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	// changes in finish stars must be made when numberOfStars is changed
	static const int numberOfStars = 5;

	FinishStars(const sf::Vector2f& starSize, const sf::Vector2f& position);

	void setPosition(const sf::Vector2f& position);

	void clickStars(int numberOfStars, const sf::Time& dt);

	~FinishStars();
};

