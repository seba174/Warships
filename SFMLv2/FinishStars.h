#pragma once
#include "SFML/Graphics.hpp"
#include <memory>

class FinishStars
	: public sf::Drawable
{
	std::vector<sf::RectangleShape> stars;
	sf::Time antimationTime;

	sf::Color starTransparency = sf::Color(255, 255, 255, 150);
	sf::Time timeBetweenStars = sf::Time(sf::seconds(0.8f));

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	// changes in Constructor must be made when numberOfStars is changed
	static const int numberOfStars = 5;

	// starSize is a size for ONE star
	// position is a position of the center of ALL stars
	FinishStars(const sf::Vector2f& starSize, const sf::Vector2f& position);

	// sets position of the center of ALL stars
	void setPosition(const sf::Vector2f& position);

	// function animates stars shining
	// numberOfStars is a number of stars to shine
	void clickStars(int numberOfStars, const sf::Time& dt);
};

