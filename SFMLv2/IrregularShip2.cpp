#include "IrregularShip2.h"


IrregularShip2::IrregularShip2(sf::Vector2f squaresize, sf::Vector2i boarddimensions, sf::Vector2f setPoints, sf::Texture* texture)
	:Board(boarddimensions, squaresize, setPoints), placeShip(false)
{
	shipv2 = sf::RectangleShape(sf::Vector2f(2 * squaresize.x, 2 * squaresize.y));
	shipv2.setTexture(texture);
	//shipv2.setFillColor(sf::Color::Green);
	shipv2.setPosition(SetPoints.x, SetPoints.y);
}


bool IrregularShip2::CanChangePositionX(const sf::Vector2f newposition) const
{
	float rotation = shipv2.getRotation();
	switch ((int)rotation)
	{
	case 0:
		if (newposition.x >= 0 && newposition.x + shipv2.getSize().x <= BoardDimensions.x)
			return true;
		break;
	case 90:
		if (newposition.x - shipv2.getSize().x >= 0 && newposition.x <= BoardDimensions.x)
			return true;
		break;
	case 180:
		if (newposition.x - shipv2.getSize().x >= 0 && newposition.x <= BoardDimensions.x)
			return true;
		break;
	case 270:
		if (newposition.x >= 0 && newposition.x + shipv2.getSize().x <= BoardDimensions.x)
			return true;
		break;
	}
	return false;
}

bool IrregularShip2::CanChangePositionY(const sf::Vector2f newposition) const
{
	float rotation = shipv2.getRotation();
	switch ((int)rotation)
	{
	case 0:
		if (newposition.y >= 0 && newposition.y + shipv2.getSize().y <= BoardDimensions.y)
			return true;
		break;
	case 90:
		if (newposition.y >= 0 && newposition.y + shipv2.getSize().y <= BoardDimensions.y)
			return true;
		break;
	case 180:
		if (newposition.y - shipv2.getSize().y >= 0 && newposition.y <= BoardDimensions.y)
			return true;
		break;
	case 270:
		if (newposition.y - shipv2.getSize().y >= 0 && newposition.y <= BoardDimensions.y)
			return true;
		break;
	}
	return false;
}

void IrregularShip2::setPosition(const sf::Vector2f mousepos)
{
	sf::Vector2f newposition = sf::Vector2f(floor(mousepos.x / SquareSize.x)*SquareSize.x, floor(mousepos.y / SquareSize.y)*SquareSize.y);

	int rotation = shipv2.getRotation();
	if (rotation == 270)
		rotation = 0;
	if (rotation == 90)
		rotation = 180;
	switch (rotation)
	{
	case 0:
		if (CanChangePositionX(newposition))
			shipv2.setPosition(sf::Vector2f(SetPoints.x + newposition.x, shipv2.getPosition().y));
		else
			shipv2.setPosition(sf::Vector2f(SetPoints.x + BoardDimensions.x - shipv2.getSize().x, shipv2.getPosition().y));
		break;
	case 180:
		if (CanChangePositionX(sf::Vector2f(newposition.x + SquareSize.x, newposition.y)))
			shipv2.setPosition(sf::Vector2f(SetPoints.x + newposition.x + SquareSize.x, shipv2.getPosition().y));
		else if (shipv2.getPosition().x - SetPoints.x > BoardDimensions.x-shipv2.getSize().x)	
			shipv2.setPosition(sf::Vector2f(SetPoints.x + BoardDimensions.x, shipv2.getPosition().y));
		else
			shipv2.setPosition(sf::Vector2f(SetPoints.x + shipv2.getSize().x, shipv2.getPosition().y));
		break;
	}
	rotation = shipv2.getRotation();
	if (rotation == 90)
		rotation = 0;
	if (rotation == 180)
		rotation = 270;
	switch (rotation)
	{
	case 0:
		if (CanChangePositionY(newposition))
			shipv2.setPosition(sf::Vector2f(shipv2.getPosition().x, SetPoints.y + newposition.y));
		else
			shipv2.setPosition(sf::Vector2f(shipv2.getPosition().x, SetPoints.y + BoardDimensions.y - shipv2.getSize().y));
		break;
	case 270:
		if (CanChangePositionY(sf::Vector2f(newposition.x, newposition.y+SquareSize.y)))
			shipv2.setPosition(sf::Vector2f(shipv2.getPosition().x, SetPoints.y + newposition.y+SquareSize.y));
		else if(shipv2.getPosition().y-SetPoints.y>BoardDimensions.y-shipv2.getSize().y)
			shipv2.setPosition(sf::Vector2f(shipv2.getPosition().x, SetPoints.y + BoardDimensions.y));
		else
			shipv2.setPosition(sf::Vector2f(shipv2.getPosition().x, SetPoints.y + shipv2.getSize().y));
		break;
	}
}

void IrregularShip2::setPositionWithoutCheck(const sf::Vector2f newposition)
{
	shipv2.setPosition(newposition);
}

sf::RectangleShape & IrregularShip2::return_ship()
{
	return shipv2;
}

bool IrregularShip2::getplaceShip() const
{
	return placeShip;
}

void IrregularShip2::setplaceShip(bool set)
{
	placeShip = set;
}

void IrregularShip2::rotate_ship()
{
	float rotation = shipv2.getRotation();

	switch ((int)rotation)
	{
	case 0:
		if (!CanChangePositionX(sf::Vector2f(shipv2.getPosition().x - SetPoints.x - shipv2.getSize().x, shipv2.getPosition().y - SetPoints.y)))
			setPositionWithoutCheck(sf::Vector2f(SetPoints.x + shipv2.getSize().x, shipv2.getPosition().y));
		shipv2.rotate(90);
		break;
	case 90:
		if (!CanChangePositionY(sf::Vector2f(shipv2.getPosition().x - SetPoints.x - shipv2.getSize().x, shipv2.getPosition().y - SetPoints.y - shipv2.getSize().y)))
			setPositionWithoutCheck(sf::Vector2f(shipv2.getPosition().x, SetPoints.y + shipv2.getSize().y));
		shipv2.rotate(90);
		break;
	case 180:
		if (!CanChangePositionX(sf::Vector2f(shipv2.getPosition().x - SetPoints.x + shipv2.getSize().x, shipv2.getPosition().y - SetPoints.y)))
			setPositionWithoutCheck(sf::Vector2f(SetPoints.x + BoardDimensions.x - shipv2.getSize().x, shipv2.getPosition().y));
		shipv2.rotate(90);
		break;
	case 270:
		if (!CanChangePositionY(sf::Vector2f(shipv2.getPosition().x - SetPoints.x - shipv2.getSize().x, shipv2.getPosition().y - SetPoints.y + shipv2.getSize().y)))
			setPositionWithoutCheck(sf::Vector2f(shipv2.getPosition().x, SetPoints.y + BoardDimensions.y - shipv2.getSize().y));
		shipv2.rotate(90);
		break;
	}
}

bool IrregularShip2::placePlayerShip(int ** ships, int tabs_size, std::vector<Board*>&VectRect, sf::Texture * texture)
{
	sf::Vector2i pos(floor((shipv2.getPosition().x - SetPoints.x) / SquareSize.x), floor((shipv2.getPosition().y - SetPoints.y) / SquareSize.y));
	placeShip = false;

	int rotation = shipv2.getRotation();
	switch (rotation)
	{
	case 0:
		if (!ships[pos.x][pos.y] && !ships[pos.x][pos.y + 1] && !ships[pos.x + 1][pos.y + 1])
		{
			ships[pos.x][pos.y] = 10;
			ships[pos.x][pos.y + 1] = 10;
			ships[pos.x + 1][pos.y + 1] = 10;

			VectRect.push_back(this);	
			return true;
		}
		break;
	case 90:
		if (!ships[pos.x-1][pos.y] && !ships[pos.x-2][pos.y] && !ships[pos.x -2][pos.y +1])
		{
			ships[pos.x - 1][pos.y] = 10;
			ships[pos.x - 2][pos.y] = 10;
			ships[pos.x - 2][pos.y + 1] = 10;

			VectRect.push_back(this);
			return true;
		}
		break;

	case 180:
		if (!ships[pos.x - 1][pos.y-1] && !ships[pos.x - 1][pos.y-2] && !ships[pos.x - 2][pos.y - 2])
		{
			ships[pos.x - 1][pos.y - 1] = 10;
			ships[pos.x - 1][pos.y - 2] = 10;
			ships[pos.x - 2][pos.y - 2] = 10;

			VectRect.push_back(this);
			return true;
		}
		break;
	
	case 270:
		if (!ships[pos.x][pos.y - 1] && !ships[pos.x + 1][pos.y - 1] && !ships[pos.x + 1][pos.y - 2])
		{
			ships[pos.x][pos.y - 1] = 10;
			ships[pos.x + 1][pos.y - 1] = 10;
			ships[pos.x + 1][pos.y - 2] = 10;

			VectRect.push_back(this);
			return true;
		}
		break;
	}
	return false;
}

void IrregularShip2::updateTexture(const sf::Time& timen)
{
	this->time += timen;

	if (time.asSeconds() >= 0.25)
	{
		time = sf::Time();
		counter++;
		if (counter > 4)
			counter = 0;
		shipv2.setTextureRect(sf::IntRect(counter * (shipv2.getTexture()->getSize().x / 5), 0, shipv2.getTexture()->getSize().x / 5, shipv2.getTexture()->getSize().y));
	}
}


