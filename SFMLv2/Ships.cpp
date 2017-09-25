#include "stdafx.h"
#include "Ships.h"
#include "TextureHandler.h"


Ships::Ships(int size, const sf::Vector2f& squaresize, const sf::Vector2i& boarddimensions, const sf::Vector2f& setPoints, sf::Texture* texture)
	:rotationHorizontally(false), Board(boarddimensions, squaresize, setPoints), size(size), placeShip(false)
{
	shipv2 = sf::RectangleShape(sf::Vector2f(squaresize.x, size*squaresize.y));
	shipv2.setTexture(texture);
	shipv2.setTextureRect(sf::IntRect(counter * (shipv2.getTexture()->getSize().x / 5), 0, shipv2.getTexture()->getSize().x / 5, shipv2.getTexture()->getSize().y));
	shipv2.setPosition(setPoints.x, setPoints.y);
}

void Ships::setPosition(const sf::Vector2f& mousepos)
{
	sf::Vector2f newposition = sf::Vector2f(floor(mousepos.x / squareSize.x)*squareSize.x, floor(mousepos.y / squareSize.y)*squareSize.y);
	
	if (CanChangePositionX(newposition))
		shipv2.setPosition(sf::Vector2f(setPoints.x + newposition.x, shipv2.getPosition().y));
	else if(rotationHorizontally)
		shipv2.setPosition(sf::Vector2f(setPoints.x + boardDimensions.x - size*squareSize.x, shipv2.getPosition().y));

	if (CanChangePositionY(newposition))
	{
		if (!rotationHorizontally)
			shipv2.setPosition(sf::Vector2f(shipv2.getPosition().x, setPoints.y + newposition.y));
		else
			shipv2.setPosition(sf::Vector2f(shipv2.getPosition().x, setPoints.y + newposition.y + squareSize.y));
	}
	else if(!rotationHorizontally)
		shipv2.setPosition(sf::Vector2f(shipv2.getPosition().x, setPoints.y + boardDimensions.y - size*squareSize.y));
}

bool Ships::CanChangePositionX(const sf::Vector2f& newposition) const
{
	sf::Vector2f PixelSize;
	if (!rotationHorizontally)
		PixelSize = sf::Vector2f(squareSize.x, size*squareSize.y);
	else
		PixelSize = sf::Vector2f(size*squareSize.x, squareSize.y);

	if (newposition.x >= 0 && newposition.x + PixelSize.x <= boardDimensions.x)
		return true;

	return false;
}

bool Ships::CanChangePositionY(const sf::Vector2f& newposition) const
{
	sf::Vector2f PixelSize;
	if (!rotationHorizontally)
		PixelSize = sf::Vector2f(squareSize.x, size*squareSize.y);
	else
		PixelSize = sf::Vector2f(size*squareSize.y, squareSize.x);
	
	if (newposition.y + squareSize.y >= 0 && newposition.y + PixelSize.y <= boardDimensions.y)
		return true;

	return false;
}

void Ships::rotateShip()
{
	if (!rotationHorizontally)
	{
		rotationHorizontally = true;
		if (!CanChangePositionX(sf::Vector2f(shipv2.getPosition().x - setPoints.x, shipv2.getPosition().y - setPoints.y)))
			setPositionWithoutCheck(sf::Vector2f(setPoints.x + boardDimensions.x - size*squareSize.x, shipv2.getPosition().y));

		shipv2.setRotation(270);
		shipv2.setSize(sf::Vector2f(squareSize.y, size*squareSize.x));
	}
	else
	{
		rotationHorizontally = false;
		if (!CanChangePositionY(sf::Vector2f(shipv2.getPosition().x - setPoints.x, shipv2.getPosition().y - setPoints.y - squareSize.y)))
			setPositionWithoutCheck(sf::Vector2f(shipv2.getPosition().x, setPoints.y + boardDimensions.y - size*squareSize.y));

		shipv2.setRotation(0);
		shipv2.setSize(sf::Vector2f(squareSize.x, size*squareSize.y));
	}
}

bool Ships::placePlayerShip(std::vector<std::vector<int>>& ships, int tabs_size, std::vector<Board*>& VectRect)
{
	float accuracy = 0.97f;
	int x = static_cast<int>(floor((shipv2.getPosition().x - setPoints.x) / (accuracy*squareSize.x)));
	int y;
	placeShip = false;
	
	if (!rotationHorizontally)
	{
		y = static_cast<int>(floor((shipv2.getPosition().y - setPoints.y) / (accuracy*squareSize.y)));
		for (int i = y; i < y + size; i++)
			if (ships[x][i])
				return false;
		for (int i = y; i < y + size; i++)
			ships[x][i] = size;

		VectRect.push_back(this);
	}
	else
	{
		y = static_cast<int>(floor((shipv2.getPosition().y - setPoints.y - squareSize.y) / (accuracy*squareSize.y)));
		for (int i = x; i < x + size; i++)
			if (ships[i][y])
				return false;
		for (int i = x; i < x + size; i++)
			ships[i][y] = size;

		VectRect.push_back(this);
	}
	return true;
}

void Ships::updateTexture(const sf::Time& timen)
{
	this->time += timen;

	if (time.asSeconds() >= 0.25)
	{
		time = sf::Time();
		counter++;
		if (counter > 4)
			counter = 0;
		shipv2.setTextureRect(sf::IntRect(counter * 122, 0 , shipv2.getTexture()->getSize().x/5, shipv2.getTexture()->getSize().y));
	}
}

void Ships::setDestroyedTexture()
{
	TextureHandler &text = TextureHandler::getInstance();
	shipv2.setTexture(&text.texture_handler["big_body_final_destroyed"]);
}
