#include "Ships.h"
#include "TextureHandler.h"


Ships::Ships(int size, const sf::Vector2f& squaresize, const sf::Vector2i& boarddimensions, const sf::Vector2f& setPoints, sf::Texture* texture)
	:rotation_horizontally(false), Board(boarddimensions, squaresize, setPoints), size(size), placeShip(false)
{
	shipv2 = sf::RectangleShape(sf::Vector2f(squaresize.x, size*squaresize.y));
	shipv2.setTexture(texture);
	shipv2.setTextureRect(sf::IntRect(counter * (shipv2.getTexture()->getSize().x / 5), 0, shipv2.getTexture()->getSize().x / 5, shipv2.getTexture()->getSize().y));
	shipv2.setPosition(SetPoints.x, SetPoints.y);
}

void Ships::setPosition(const sf::Vector2f& mousepos)
{
	sf::Vector2f newposition = sf::Vector2f(floor(mousepos.x / SquareSize.x)*SquareSize.x, floor(mousepos.y / SquareSize.y)*SquareSize.y);
	
	if (CanChangePositionX(newposition))
		shipv2.setPosition(sf::Vector2f(SetPoints.x + newposition.x, shipv2.getPosition().y));
	else if(rotation_horizontally)
		shipv2.setPosition(sf::Vector2f(SetPoints.x + BoardDimensions.x - size*SquareSize.x, shipv2.getPosition().y));

	if (CanChangePositionY(newposition))
	{
		if (!rotation_horizontally)
			shipv2.setPosition(sf::Vector2f(shipv2.getPosition().x, SetPoints.y + newposition.y));
		else
			shipv2.setPosition(sf::Vector2f(shipv2.getPosition().x, SetPoints.y + newposition.y + SquareSize.y));
	}
	else if(!rotation_horizontally)
		shipv2.setPosition(sf::Vector2f(shipv2.getPosition().x, SetPoints.y + BoardDimensions.y - size*SquareSize.y));
}

bool Ships::CanChangePositionX(const sf::Vector2f& newposition) const
{
	sf::Vector2f PixelSize;
	if (!rotation_horizontally)
		PixelSize = sf::Vector2f(SquareSize.x, size*SquareSize.y);
	else
		PixelSize = sf::Vector2f(size*SquareSize.x, SquareSize.y);

	if (newposition.x >= 0 && newposition.x + PixelSize.x <= BoardDimensions.x)
		return true;

	return false;
}

bool Ships::CanChangePositionY(const sf::Vector2f& newposition) const
{
	sf::Vector2f PixelSize;
	if (!rotation_horizontally)
		PixelSize = sf::Vector2f(SquareSize.x, size*SquareSize.y);
	else
		PixelSize = sf::Vector2f(size*SquareSize.y, SquareSize.x);
	
	if (newposition.y + SquareSize.y >= 0 && newposition.y + PixelSize.y <= BoardDimensions.y)
		return true;

	return false;
}

void Ships::rotate_ship()
{
	if (!rotation_horizontally)
	{
		rotation_horizontally = true;
		if (!CanChangePositionX(sf::Vector2f(shipv2.getPosition().x - SetPoints.x, shipv2.getPosition().y - SetPoints.y)))
			setPositionWithoutCheck(sf::Vector2f(SetPoints.x + BoardDimensions.x - size*SquareSize.x, shipv2.getPosition().y));

		shipv2.setRotation(270);
		shipv2.setSize(sf::Vector2f(SquareSize.y, size*SquareSize.x));
	}
	else
	{
		rotation_horizontally = false;
		if (!CanChangePositionY(sf::Vector2f(shipv2.getPosition().x - SetPoints.x, shipv2.getPosition().y - SetPoints.y - SquareSize.y)))
			setPositionWithoutCheck(sf::Vector2f(shipv2.getPosition().x, SetPoints.y + BoardDimensions.y - size*SquareSize.y));

		shipv2.setRotation(0);
		shipv2.setSize(sf::Vector2f(SquareSize.x, size*SquareSize.y));
	}
}

bool Ships::placePlayerShip(int **ships, int tabs_size, std::vector<Board*>& VectRect, sf::Texture* texture)
{
	float accuracy = 0.98f;
	int x = static_cast<int>(floor((shipv2.getPosition().x - SetPoints.x) / (accuracy*SquareSize.x)));
	int y;
	placeShip = false;
	
	if (!rotation_horizontally)
	{
		y = static_cast<int>(floor((shipv2.getPosition().y - SetPoints.y) / (accuracy*SquareSize.y)));
		for (int i = y; i < y + size; i++)
			if (ships[x][i])
				return false;
		for (int i = y; i < y + size; i++)
			ships[x][i] = size;

		VectRect.push_back(this);
	}
	else
	{
		y = static_cast<int>(floor((shipv2.getPosition().y - SetPoints.y - SquareSize.y) / (accuracy*SquareSize.y)));
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
