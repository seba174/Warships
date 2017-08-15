#include "DestroyedShips.h"
#include "TextureHandler.h"



void DestroyedShips::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (const sf::RectangleShape& rect : vec_ships)
	{
		target.draw(rect, states);
	}
}

DestroyedShips::DestroyedShips(const sf::Vector2i & boardDimensions, const sf::Vector2f & squareSize, const sf::Vector2f& setPoint)
	:boardDimensions(boardDimensions), squareSize(squareSize), setPoint(setPoint)
{
	destroyed = sf::Color(255, 0, 0, 190);

	TextureHandler& textures = TextureHandler::getInstance();

	vec_ships.push_back(sf::RectangleShape(sf::Vector2f(squareSize.x, 5 * squareSize.y)));
	vec_ships[Ship5].setTexture(&textures.texture_handler["big_body_no_waves"]);

	vec_ships.push_back(sf::RectangleShape(sf::Vector2f(squareSize.x, 4 * squareSize.y)));
	vec_ships[Ship4].setTexture(&textures.texture_handler["big_body_no_waves"]);

	vec_ships.push_back(sf::RectangleShape(sf::Vector2f(2 * squareSize.x, 4 * squareSize.y)));
	vec_ships[Ship2x4].setTexture(&textures.texture_handler["irregular3_no_waves"]);

	vec_ships.push_back(sf::RectangleShape(sf::Vector2f(squareSize.x, 3 * squareSize.y)));
	vec_ships[Ship3].setTexture(&textures.texture_handler["big_body_no_waves"]);

	vec_ships.push_back(sf::RectangleShape(sf::Vector2f(squareSize.x, 2 * squareSize.y)));
	vec_ships[Ship2].setTexture(&textures.texture_handler["big_body_no_waves"]);

	vec_ships.push_back(sf::RectangleShape(sf::Vector2f(2 * squareSize.x, 2 * squareSize.y)));
	vec_ships[Ship2x2].setTexture(&textures.texture_handler["irregular2_no_waves"]);

	setPosition(0);
}

void DestroyedShips::setPosition(int y)
{
	// X size of all ships
	float size = (1 + 1 + 1 + 1 + 2 + 2)*squareSize.x;
	// the distance between neighboring ships
	float offset = (boardDimensions.x - size) / (static_cast<float>(count_of_ships) + 1);

	sf::Vector2f pos = setPoint;
	pos.y += y;
	pos.x += offset;
	for (sf::RectangleShape& rect : vec_ships)
	{
		rect.setPosition(pos);
		pos.x += rect.getSize().x;
		pos.x += offset;
	}
}

void DestroyedShips::markDestroyed(int number)
{
	if (number >= 0 && number < vec_ships.size())
	{
		vec_ships[number].setFillColor(destroyed);
	}
}
