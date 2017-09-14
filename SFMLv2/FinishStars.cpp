#include "FinishStars.h"
#include "TextureHandler.h"


void FinishStars::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (const sf::RectangleShape& star : stars)
		target.draw(star, states);
}

FinishStars::FinishStars(const sf::Vector2f & starSize, const sf::Vector2f & position)
{
	stars = { sf::RectangleShape(starSize),sf::RectangleShape(starSize),sf::RectangleShape(starSize),sf::RectangleShape(starSize),sf::RectangleShape(starSize) };
	stars[0].setOrigin(2.5f*starSize.x, starSize.y / 2);
	stars[1].setOrigin(1.5f*starSize.x, starSize.y / 2);
	stars[2].setOrigin(0.5f*starSize.x, starSize.y / 2);
	stars[3].setOrigin(-0.5f*starSize.x, starSize.y / 2);
	stars[4].setOrigin(-1.5f*starSize.x, starSize.y / 2);
	setPosition(position);

	for (sf::RectangleShape& star : stars)
	{
		star.setTexture(&TextureHandler::getInstance().texture_handler["star"]);
		star.setFillColor(starTransparency);
	}
}

void FinishStars::setPosition(const sf::Vector2f & position)
{
	for (sf::RectangleShape& star : stars)
	{
		star.setPosition(position);
	}
}

void FinishStars::clickStars(int numberOfStars, const sf::Time & dt)
{
	if (antimationTime.asSeconds() > timeBetweenStars.asSeconds()*(numberOfStars + 1))
		return;

	if (numberOfStars < 0)
		return;
	else if (numberOfStars > this->numberOfStars)
		numberOfStars = this->numberOfStars;

	antimationTime += dt;

	for (int i = 0; i < numberOfStars; ++i)
	{
		if (antimationTime.asSeconds() > timeBetweenStars.asSeconds()*(i + 1))
			stars[i].setFillColor(sf::Color::White);
	}
}

