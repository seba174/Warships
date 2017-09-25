#include "stdafx.h"
#include "DestroyedShips.h"
#include "TextureHandler.h"
#include "FontHandler.h"


void DestroyedShips::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (const sf::RectangleShape& rect : vec_ships)
	{
		target.draw(rect, states);
	}
	target.draw(info, states);
}

DestroyedShips::DestroyedShips(const sf::Vector2i & boardDimensions, const sf::Vector2f & squareSize, const sf::Vector2f& setPoint, float interfaceScale)
	:boardDimensions(boardDimensions), squareSize(squareSize), setPoint(setPoint), interfaceScale(interfaceScale)
{
	destroyed = sf::Color(255, 0, 0, 190);

	int char_size = static_cast<int>(45 * interfaceScale);
	info.setFont(FontHandler::getInstance().font_handler["Mecha"]);
	info.setCharacterSize(char_size);

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
	float infoOffset = 30 * interfaceScale;
	info.setPosition((setPoint.x + static_cast<float>(boardDimensions.x) / 2) - info.getGlobalBounds().width / 2, infoOffset);
	// X size of all ships
	float size = (1 + 1 + 1 + 1 + 2 + 2)*squareSize.x;
	// the distance between neighboring ships
	float offset = (boardDimensions.x - size) / (static_cast<float>(count_of_ships) + 1);

	sf::Vector2f pos = setPoint;
	pos.y += y;
	pos.y += infoOffset;
	pos.y += info.getGlobalBounds().height;
	pos.x += offset;
	for (sf::RectangleShape& rect : vec_ships)
	{
		rect.setPosition(pos);
		pos.x += rect.getSize().x;
		pos.x += offset;
	}
}

void DestroyedShips::markDestroyed(unsigned int number)
{
	if (number >= 0 && number < vec_ships.size())
	{
		vec_ships[number].setFillColor(destroyed);
	}
}
