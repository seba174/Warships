#include "IrregularShip2.h"


IrregularShip2::IrregularShip2(const sf::Vector2f& squaresize, const sf::Vector2i& boarddimensions, const sf::Vector2f& setPoints, sf::Texture* texture)
	:Board(boarddimensions, squaresize, setPoints), placeShip(false)
{
	shipv2 = sf::RectangleShape(sf::Vector2f(2 * squaresize.x, 2 * squaresize.y));
	shipv2.setTexture(texture);
	shipv2.setPosition(setPoints.x, setPoints.y);
}


bool IrregularShip2::CanChangePositionX(const sf::Vector2f& newposition) const
{
	float rotation = shipv2.getRotation();
	switch (static_cast<int>(rotation))
	{
	case 0:
		if (newposition.x >= 0 && newposition.x + shipv2.getSize().x <= boardDimensions.x)
			return true;
		break;
	case 90:
		if (newposition.x - shipv2.getSize().x >= 0 && newposition.x <= boardDimensions.x)
			return true;
		break;
	case 180:
		if (newposition.x - shipv2.getSize().x >= 0 && newposition.x <= boardDimensions.x)
			return true;
		break;
	case 270:
		if (newposition.x >= 0 && newposition.x + shipv2.getSize().x <= boardDimensions.x)
			return true;
		break;
	}
	return false;
}

bool IrregularShip2::CanChangePositionY(const sf::Vector2f& newposition) const
{
	float rotation = shipv2.getRotation();
	switch (static_cast<int>(rotation))
	{
	case 0:
		if (newposition.y >= 0 && newposition.y + shipv2.getSize().y <= boardDimensions.y)
			return true;
		break;
	case 90:
		if (newposition.y >= 0 && newposition.y + shipv2.getSize().y <= boardDimensions.y)
			return true;
		break;
	case 180:
		if (newposition.y - shipv2.getSize().y >= 0 && newposition.y <= boardDimensions.y)
			return true;
		break;
	case 270:
		if (newposition.y - shipv2.getSize().y >= 0 && newposition.y <= boardDimensions.y)
			return true;
		break;
	}
	return false;
}

void IrregularShip2::setPosition(const sf::Vector2f& mousepos)
{
	sf::Vector2f newposition = sf::Vector2f(floor(mousepos.x / squareSize.x)*squareSize.x, floor(mousepos.y / squareSize.y)*squareSize.y);

	//int rotation = static_cast<int>(shipv2.getRotation());
	//if (rotation == 270)
	//	rotation = 0;
	//if (rotation == 90)
	//	rotation = 180;
	//switch (rotation)
	//{
	//case 0:
	//	if (CanChangePositionX(newposition))
	//		shipv2.setPosition(sf::Vector2f(setPoints.x + newposition.x, shipv2.getPosition().y));
	//	else
	//		shipv2.setPosition(sf::Vector2f(setPoints.x + boardDimensions.x - shipv2.getSize().x, shipv2.getPosition().y));
	//	break;
	//case 180:
	//	if (CanChangePositionX(sf::Vector2f(newposition.x + squareSize.x, newposition.y)))
	//		shipv2.setPosition(sf::Vector2f(setPoints.x + newposition.x + squareSize.x, shipv2.getPosition().y));
	//	else if (shipv2.getPosition().x - setPoints.x > boardDimensions.x-shipv2.getSize().x)	
	//		shipv2.setPosition(sf::Vector2f(setPoints.x + boardDimensions.x, shipv2.getPosition().y));
	//	else
	//		shipv2.setPosition(sf::Vector2f(setPoints.x + shipv2.getSize().x, shipv2.getPosition().y));
	//	break;
	//}
	//rotation = static_cast<int>(shipv2.getRotation());
	//if (rotation == 90)
	//	rotation = 0;
	//if (rotation == 180)
	//	rotation = 270;
	//switch (rotation)
	//{
	//case 0:
	//	if (CanChangePositionY(newposition))
	//		shipv2.setPosition(sf::Vector2f(shipv2.getPosition().x, setPoints.y + newposition.y));
	//	else
	//		shipv2.setPosition(sf::Vector2f(shipv2.getPosition().x, setPoints.y + boardDimensions.y - shipv2.getSize().y));
	//	break;
	//case 270:
	//	if (CanChangePositionY(sf::Vector2f(newposition.x, newposition.y+squareSize.y)))
	//		shipv2.setPosition(sf::Vector2f(shipv2.getPosition().x, setPoints.y + newposition.y+squareSize.y));
	//	else if(shipv2.getPosition().y-setPoints.y>boardDimensions.y-shipv2.getSize().y)
	//		shipv2.setPosition(sf::Vector2f(shipv2.getPosition().x, setPoints.y + boardDimensions.y));
	//	else
	//		shipv2.setPosition(sf::Vector2f(shipv2.getPosition().x, setPoints.y + shipv2.getSize().y));
	//	break;
	//}

	shipv2.setOrigin(sf::Vector2f(shipv2.getSize().x / 2, shipv2.getSize().y / 2));
	if (newposition.x >= squareSize.x && newposition.x < boardDimensions.x - squareSize.x)
		shipv2.setPosition(setPoints.x + newposition.x, shipv2.getPosition().y);
	else if (newposition.x < squareSize.x)
		shipv2.setPosition(setPoints.x + squareSize.x, shipv2.getPosition().y);
	else
		shipv2.setPosition(setPoints.x + boardDimensions.x - squareSize.x, shipv2.getPosition().y);

	if (newposition.y >= squareSize.y && newposition.y < boardDimensions.y - squareSize.y)
		shipv2.setPosition(shipv2.getPosition().x, setPoints.y + newposition.y);
	else if (newposition.y < squareSize.y)
		shipv2.setPosition(shipv2.getPosition().x, setPoints.y + squareSize.y);
	else
		shipv2.setPosition(shipv2.getPosition().x, setPoints.y + boardDimensions.y - squareSize.y);
}

void IrregularShip2::rotate_ship()
{
	shipv2.setSize(sf::Vector2f(shipv2.getSize().y, shipv2.getSize().x));
	shipv2.rotate(90);
	shipv2.setOrigin(sf::Vector2f(shipv2.getSize().x / 2, shipv2.getSize().y / 2));

	//float rotation = shipv2.getRotation();

	//switch (static_cast<int>(rotation))
	//{
	//case 0:
	//	if (!CanChangePositionX(sf::Vector2f(shipv2.getPosition().x - setPoints.x - shipv2.getSize().x, shipv2.getPosition().y - setPoints.y)))
	//		setPositionWithoutCheck(sf::Vector2f(setPoints.x + shipv2.getSize().x, shipv2.getPosition().y));
	//	shipv2.rotate(90);
	//	break;
	//case 90:
	//	if (!CanChangePositionY(sf::Vector2f(shipv2.getPosition().x - setPoints.x - shipv2.getSize().x, shipv2.getPosition().y - setPoints.y - shipv2.getSize().y)))
	//		setPositionWithoutCheck(sf::Vector2f(shipv2.getPosition().x, setPoints.y + shipv2.getSize().y));
	//	shipv2.rotate(90);
	//	break;
	//case 180:
	//	if (!CanChangePositionX(sf::Vector2f(shipv2.getPosition().x - setPoints.x + shipv2.getSize().x, shipv2.getPosition().y - setPoints.y)))
	//		setPositionWithoutCheck(sf::Vector2f(setPoints.x + boardDimensions.x - shipv2.getSize().x, shipv2.getPosition().y));
	//	shipv2.rotate(90);
	//	break;
	//case 270:
	//	if (!CanChangePositionY(sf::Vector2f(shipv2.getPosition().x - setPoints.x - shipv2.getSize().x, shipv2.getPosition().y - setPoints.y + shipv2.getSize().y)))
	//		setPositionWithoutCheck(sf::Vector2f(shipv2.getPosition().x, setPoints.y + boardDimensions.y - shipv2.getSize().y));
	//	shipv2.rotate(90);
	//	break;
	//}
}

bool IrregularShip2::placePlayerShip(int ** ships, int tabs_size, std::vector<Board*>&VectRect)
{
	float accuracy = 0.97f;
	sf::Vector2i pos(static_cast<int>(floor((shipv2.getPosition().x - setPoints.x) / (accuracy*squareSize.x))),
		static_cast<int>(floor((shipv2.getPosition().y - setPoints.y) / (accuracy*squareSize.y))));
	placeShip = false;

	
	int rotation = static_cast<int>(shipv2.getRotation());
	switch (rotation)
	{
	case 0:
		if (!ships[pos.x][pos.y] && !ships[pos.x - 1][pos.y] && !ships[pos.x - 1][pos.y - 1])
		{
			ships[pos.x][pos.y] = 10;
			ships[pos.x - 1][pos.y] = 10;
			ships[pos.x - 1][pos.y - 1] = 10;

			VectRect.push_back(this);
			return true;
		}
		break;
	case 90:
		if (!ships[pos.x - 1][pos.y] && !ships[pos.x - 1][pos.y - 1] && !ships[pos.x][pos.y - 1])
		{
			ships[pos.x - 1][pos.y] = 10;
			ships[pos.x - 1][pos.y - 1] = 10;
			ships[pos.x][pos.y - 1] = 10;

			VectRect.push_back(this);
			return true;
		}
		break;

	case 180:
		if (!ships[pos.x][pos.y] && !ships[pos.x][pos.y - 1] && !ships[pos.x - 1][pos.y - 1])
		{
			ships[pos.x][pos.y] = 10;
			ships[pos.x][pos.y - 1] = 10;
			ships[pos.x - 1][pos.y - 1] = 10;

			VectRect.push_back(this);
			return true;
		}
		break;
	
	case 270:
		if (!ships[pos.x][pos.y] && !ships[pos.x - 1][pos.y] && !ships[pos.x][pos.y - 1])
		{
			ships[pos.x][pos.y] = 10;
			ships[pos.x - 1][pos.y] = 10;
			ships[pos.x][pos.y - 1] = 10;

			VectRect.push_back(this);
			return true;
		}
		break;
	}
	return false;

	//int rotation = static_cast<int>(shipv2.getRotation());
	//switch (rotation)
	//{
	//case 0:
	//	if (!ships[pos.x][pos.y] && !ships[pos.x][pos.y + 1] && !ships[pos.x + 1][pos.y + 1])
	//	{
	//		ships[pos.x][pos.y] = 10;
	//		ships[pos.x][pos.y + 1] = 10;
	//		ships[pos.x + 1][pos.y + 1] = 10;

	//		VectRect.push_back(this);	
	//		return true;
	//	}
	//	break;
	//case 90:
	//	if (!ships[pos.x-1][pos.y] && !ships[pos.x-2][pos.y] && !ships[pos.x -2][pos.y +1])
	//	{
	//		ships[pos.x - 1][pos.y] = 10;
	//		ships[pos.x - 2][pos.y] = 10;
	//		ships[pos.x - 2][pos.y + 1] = 10;

	//		VectRect.push_back(this);
	//		return true;
	//	}
	//	break;

	//case 180:
	//	if (!ships[pos.x - 1][pos.y-1] && !ships[pos.x - 1][pos.y-2] && !ships[pos.x - 2][pos.y - 2])
	//	{
	//		ships[pos.x - 1][pos.y - 1] = 10;
	//		ships[pos.x - 1][pos.y - 2] = 10;
	//		ships[pos.x - 2][pos.y - 2] = 10;

	//		VectRect.push_back(this);
	//		return true;
	//	}
	//	break;
	//
	//case 270:
	//	if (!ships[pos.x][pos.y - 1] && !ships[pos.x + 1][pos.y - 1] && !ships[pos.x + 1][pos.y - 2])
	//	{
	//		ships[pos.x][pos.y - 1] = 10;
	//		ships[pos.x + 1][pos.y - 1] = 10;
	//		ships[pos.x + 1][pos.y - 2] = 10;

	//		VectRect.push_back(this);
	//		return true;
	//	}
	//	break;
	//}
	//return false;
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

void IrregularShip2::setDestroyedTexture()
{
}


