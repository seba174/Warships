#include "IrregularShip3.h"
#include "TextureHandler.h"


IrregularShip3::IrregularShip3(const sf::Vector2f& squaresize, const sf::Vector2i& boarddimensions, const sf::Vector2f& setPoints, sf::Texture * texture)
	:Board(boarddimensions, squaresize, setPoints), placeShip(false)
{
	shipv2 = sf::RectangleShape(sf::Vector2f(2 * squaresize.x, 4 * squaresize.y));
	shipv2.setTexture(texture);
	shipv2.setTextureRect(sf::IntRect(counter * (shipv2.getTexture()->getSize().x / 5), 0, shipv2.getTexture()->getSize().x / 5, shipv2.getTexture()->getSize().y));
	shipv2.setPosition(SetPoints.x, SetPoints.y);
}

bool IrregularShip3::CanChangePositionX(const sf::Vector2f& newposition) const
{
	float rotation = shipv2.getRotation();
	switch (static_cast<int>(rotation))
	{
	case 0:
		if (newposition.x >= 0 && newposition.x + shipv2.getSize().x <= BoardDimensions.x)
			return true;
		break;
	case 90:
		if (newposition.x - shipv2.getSize().y >= 0 && newposition.x <= BoardDimensions.x)
			return true;
		break;
	case 180:
		if (newposition.x - shipv2.getSize().x >= 0 && newposition.x <= BoardDimensions.x)
			return true;
		break;
	case 270:
		if (newposition.x >= 0 && newposition.x + shipv2.getSize().y <= BoardDimensions.x)
			return true;
		break;
	}
	return false;
}

bool IrregularShip3::CanChangePositionY(const sf::Vector2f& newposition) const
{
	float rotation = shipv2.getRotation();
	switch (static_cast<int>(rotation))
	{
	case 0:
		if (newposition.y >= 0 && newposition.y + shipv2.getSize().y <= BoardDimensions.y)
			return true;
		break;
	case 90:
		if (newposition.y >= 0 && newposition.y + shipv2.getSize().x <= BoardDimensions.y)
			return true;
		break;
	case 180:
		if (newposition.y - shipv2.getSize().y >= 0 && newposition.y <= BoardDimensions.y)
			return true;
		break;
	case 270:
		if (newposition.y - shipv2.getSize().x >= 0 && newposition.y <= BoardDimensions.y)
			return true;
		break;
	}
	return false;
}

void IrregularShip3::setPosition(const sf::Vector2f& mousepos)
{
	sf::Vector2f newposition = sf::Vector2f(floor(mousepos.x / SquareSize.x)*SquareSize.x, floor(mousepos.y / SquareSize.y)*SquareSize.y);
	int rotation = shipv2.getRotation();

	switch (rotation)
	{
	case 0:
		if (CanChangePositionX(newposition))
			shipv2.setPosition(sf::Vector2f(SetPoints.x + newposition.x, shipv2.getPosition().y));
		else
			shipv2.setPosition(sf::Vector2f(SetPoints.x + BoardDimensions.x - shipv2.getSize().x, shipv2.getPosition().y));
		break;
	case 90:
		if (CanChangePositionX(sf::Vector2f(newposition.x + SquareSize.x, newposition.y)))
			shipv2.setPosition(sf::Vector2f(SetPoints.x + newposition.x + SquareSize.x, shipv2.getPosition().y));
		else if (shipv2.getPosition().x - SetPoints.x > BoardDimensions.x/2)
			shipv2.setPosition(sf::Vector2f(SetPoints.x + BoardDimensions.x, shipv2.getPosition().y));
		else
			shipv2.setPosition(sf::Vector2f(SetPoints.x + shipv2.getSize().y, shipv2.getPosition().y));
		break;
	case 180:
		if (CanChangePositionX(sf::Vector2f(newposition.x + SquareSize.x, newposition.y)))
			shipv2.setPosition(sf::Vector2f(SetPoints.x + newposition.x + SquareSize.x, shipv2.getPosition().y));
		else if (shipv2.getPosition().x - SetPoints.x > BoardDimensions.x/2)
			shipv2.setPosition(sf::Vector2f(SetPoints.x + BoardDimensions.x, shipv2.getPosition().y));
		else
			shipv2.setPosition(sf::Vector2f(SetPoints.x + shipv2.getSize().x, shipv2.getPosition().y));
		break;
	case 270:
		if (CanChangePositionX(newposition))
			shipv2.setPosition(sf::Vector2f(SetPoints.x + newposition.x, shipv2.getPosition().y));
		else
			shipv2.setPosition(sf::Vector2f(SetPoints.x + BoardDimensions.x - shipv2.getSize().y, shipv2.getPosition().y));
		break;
	}
	rotation = shipv2.getRotation();
	switch (rotation)
	{
	case 0:
		if (CanChangePositionY(newposition))
			shipv2.setPosition(sf::Vector2f(shipv2.getPosition().x, SetPoints.y + newposition.y));
		else
			shipv2.setPosition(sf::Vector2f(shipv2.getPosition().x, SetPoints.y + BoardDimensions.y - shipv2.getSize().y));
		break;
	case 90:
		if (CanChangePositionY(newposition))
			shipv2.setPosition(sf::Vector2f(shipv2.getPosition().x, SetPoints.y + newposition.y));
		else
			shipv2.setPosition(sf::Vector2f(shipv2.getPosition().x, SetPoints.y + BoardDimensions.y - shipv2.getSize().x));
		break;
	case 180:
		if (CanChangePositionY(sf::Vector2f(newposition.x, newposition.y + SquareSize.y)))
			shipv2.setPosition(sf::Vector2f(shipv2.getPosition().x, SetPoints.y + newposition.y + SquareSize.y));
		else if (shipv2.getPosition().y - SetPoints.y > BoardDimensions.y-SquareSize.y)
			shipv2.setPosition(sf::Vector2f(shipv2.getPosition().x, SetPoints.y + BoardDimensions.y));
		else
			shipv2.setPosition(sf::Vector2f(shipv2.getPosition().x, SetPoints.y + shipv2.getSize().y));
		break;
	case 270:
		if (CanChangePositionY(sf::Vector2f(newposition.x, newposition.y + SquareSize.y)))
			shipv2.setPosition(sf::Vector2f(shipv2.getPosition().x, SetPoints.y + newposition.y + SquareSize.y));
		else if (shipv2.getPosition().y - SetPoints.y > BoardDimensions.y/2)
			shipv2.setPosition(sf::Vector2f(shipv2.getPosition().x, SetPoints.y + BoardDimensions.y));
		else
			shipv2.setPosition(sf::Vector2f(shipv2.getPosition().x, SetPoints.y + shipv2.getSize().x));
		break;
	}
}

void IrregularShip3::rotate_ship()
{
	float rotation = shipv2.getRotation();

	switch (static_cast<int>(rotation))
	{
	case 0:
		if (!CanChangePositionX(sf::Vector2f(shipv2.getPosition().x - SetPoints.x - shipv2.getSize().y, shipv2.getPosition().y - SetPoints.y)))
			setPositionWithoutCheck(sf::Vector2f(SetPoints.x + shipv2.getSize().y, shipv2.getPosition().y));
		shipv2.rotate(90);
		break;
	case 90:
		if (!CanChangePositionY(sf::Vector2f(shipv2.getPosition().x - SetPoints.x - shipv2.getSize().x, shipv2.getPosition().y - SetPoints.y - shipv2.getSize().y)))
			setPositionWithoutCheck(sf::Vector2f(shipv2.getPosition().x, SetPoints.y + shipv2.getSize().y));
		shipv2.rotate(90);
		break;
	case 180:
		if (!CanChangePositionX(sf::Vector2f(shipv2.getPosition().x - SetPoints.x + shipv2.getSize().y, shipv2.getPosition().y - SetPoints.y)))
			setPositionWithoutCheck(sf::Vector2f(SetPoints.x + BoardDimensions.x - shipv2.getSize().y, shipv2.getPosition().y));
		shipv2.rotate(90);
		break;
	case 270:
		if (!CanChangePositionY(sf::Vector2f(shipv2.getPosition().x - SetPoints.x - shipv2.getSize().x, shipv2.getPosition().y - SetPoints.y + shipv2.getSize().y)))
			setPositionWithoutCheck(sf::Vector2f(shipv2.getPosition().x, SetPoints.y + BoardDimensions.y - shipv2.getSize().y));
		shipv2.rotate(90);
		break;
	}
}

bool IrregularShip3::placePlayerShip(int ** ships, int tabs_size, std::vector<Board*>&VectRect, sf::Texture * texture)
{
	float accuracy = 0.98;
	sf::Vector2i pos(floor((shipv2.getPosition().x - SetPoints.x) / (accuracy*SquareSize.x)), floor((shipv2.getPosition().y - SetPoints.y) / (accuracy*SquareSize.y)));
	placeShip = false;

	int rotation = shipv2.getRotation();
	switch (rotation)
	{
	case 0:
		if (!ships[pos.x][pos.y+1] && !ships[pos.x][pos.y + 2] && !ships[pos.x][pos.y + 3]
			&& !ships[pos.x+1][pos.y] && !ships[pos.x+1][pos.y + 1] && !ships[pos.x + 1][pos.y + 2])
		{
			ships[pos.x][pos.y + 1] = 11;
			ships[pos.x][pos.y + 2] = 11;
			ships[pos.x][pos.y + 3] = 11;
			ships[pos.x + 1][pos.y] = 11;
			ships[pos.x + 1][pos.y + 1] = 11;
			ships[pos.x + 1][pos.y + 2] = 11;

			VectRect.push_back(this);
			return true;
		}
		break;
	case 90:
		if (!ships[pos.x - 2][pos.y] && !ships[pos.x - 3][pos.y] && !ships[pos.x - 4][pos.y]
			&& !ships[pos.x -1][pos.y+1] && !ships[pos.x - 2][pos.y+1] && !ships[pos.x - 3][pos.y+1])
		{
			ships[pos.x - 2][pos.y] = 11;
			ships[pos.x - 3][pos.y] = 11;
			ships[pos.x - 4][pos.y] = 11;
			ships[pos.x - 1][pos.y + 1] = 11;
			ships[pos.x - 2][pos.y + 1] = 11;
			ships[pos.x - 3][pos.y + 1] = 11;

			VectRect.push_back(this);
			return true;
		}
		break;

	case 180:
		if (!ships[pos.x - 1][pos.y - 2] && !ships[pos.x - 1][pos.y - 3] && !ships[pos.x - 1][pos.y - 4]
			&& !ships[pos.x - 2][pos.y - 1] && !ships[pos.x - 2][pos.y - 2] && !ships[pos.x - 2][pos.y - 3])
		{
			ships[pos.x - 1][pos.y - 2] = 11;
			ships[pos.x - 1][pos.y - 3] = 11;
			ships[pos.x - 1][pos.y - 4] = 11;
			ships[pos.x - 2][pos.y - 1] = 11;
			ships[pos.x - 2][pos.y - 2] = 11;
			ships[pos.x - 2][pos.y - 3] = 11;

			VectRect.push_back(this);
			return true;
		}
		break;

	case 270:
		if (!ships[pos.x][pos.y - 2] && !ships[pos.x + 1][pos.y - 2] && !ships[pos.x + 2][pos.y - 2]
			&& !ships[pos.x + 1][pos.y - 1] && !ships[pos.x + 2][pos.y - 1] && !ships[pos.x + 3][pos.y - 1])
		{
			ships[pos.x][pos.y - 2] = 11;
			ships[pos.x + 1][pos.y - 2] = 11;
			ships[pos.x + 2][pos.y - 2] = 11;
			ships[pos.x + 1][pos.y - 1] = 11;
			ships[pos.x + 2][pos.y - 1] = 11;
			ships[pos.x + 3][pos.y - 1] = 11;

			VectRect.push_back(this);
			return true;
		}
		break;
	}
	return false;
}

void IrregularShip3::updateTexture(const sf::Time& timen)
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

void IrregularShip3::setDestroyedTexture()
{
	TextureHandler &text = TextureHandler::getInstance();
	shipv2.setTexture(&text.texture_handler["irregular3_destroyed"]);
}
