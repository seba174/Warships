#include "Player.h"
#include "IrregularShip2.h"
#include "IrregularShip3.h"
#include "TextureHandler.h"


void Player::updateMaximumHits()
{
	if (maximumHitsTemp > maximumHits)
	{
		maximumHits = maximumHitsTemp;
	}
	maximumHitsTemp = 0;
}

void Player::updateMaximumMisses()
{
	if (maximumMissesTemp > maximumMisses)
	{
		maximumMisses = maximumMissesTemp;
	}
	maximumMissesTemp = 0;
}

Player::Player(const sf::Vector2i& dim, const sf::Vector2f& SquareSize,
 const sf::Vector2f& enemy_setpoints, std::vector<std::vector<int>>* enemy_ships, const sf::Vector2f& player_setpoints, const sf::RectangleShape& missedShot, const sf::RectangleShape& hit, sf::RectangleShape& rect)
	: boardDimensions(dim), squareSize(SquareSize), enemySetPoints(enemy_setpoints), playerSetPoints(player_setpoints), 
	missedShot(missedShot), hit(hit), rect(rect), totalHits(0),totalShots(0), enemyShips(enemy_ships)
{
	rect.setPosition(enemySetPoints);
	mapSize = static_cast<int>(boardDimensions.x / SquareSize.x);

	squareTab2 = std::vector<std::vector<sf::RectangleShape>>(mapSize, std::vector<sf::RectangleShape>(mapSize, sf::RectangleShape()));
	playerShips = std::vector<std::vector<int>>(mapSize, std::vector<int>(mapSize, 0));

	TextureHandler& textures = TextureHandler::getInstance();

	setShips.push_back(std::make_unique<Ships>(5, SquareSize, boardDimensions, playerSetPoints, &textures.texture_handler["big_body_final"]));
	setShips.push_back(std::make_unique<Ships>(4, SquareSize, boardDimensions, playerSetPoints, &textures.texture_handler["big_body_final"]));
	setShips.push_back(std::make_unique<Ships>(3, SquareSize, boardDimensions, playerSetPoints, &textures.texture_handler["big_body_final"]));
	setShips.push_back(std::make_unique<Ships>(2, SquareSize, boardDimensions, playerSetPoints, &textures.texture_handler["big_body_final"]));
	setShips.push_back(std::make_unique<IrregularShip2>(SquareSize, boardDimensions, playerSetPoints, &textures.texture_handler["irregular2"]));
	setShips.push_back(std::make_unique<IrregularShip3>(SquareSize, boardDimensions, playerSetPoints, &textures.texture_handler["irregular3"]));
	
	this->shipsSetUp = false;
}

bool Player::playerMoves(const sf::Vector2i & position)
{
	// chcecks if player has clicked button
	if (!getPlayerMoved())
		return false;

	if ((*enemyShips)[position.x][position.y] == -2)
	{
	}
	else if ((*enemyShips)[position.x][position.y] == 0)
	{
		squareTab2[position.x][position.y] = missedShot;
		squareTab2[position.x][position.y].setPosition(sf::Vector2f(enemySetPoints.x + squareSize.x*position.x, enemySetPoints.y + squareSize.y*position.y));
		(*enemyShips)[position.x][position.y] = -2;
		playerMoved = false;
		++totalShots;
		++maximumMissesTemp;
		updateMaximumHits();
		return true;
	}
	else if ((*enemyShips)[position.x][position.y])
	{
		switch ((*enemyShips)[position.x][position.y])
		{
		case 2: HP.size_2--; break;
		case 3: HP.size_3--; break;
		case 4: HP.size_4--; break;
		case 5: HP.size_5--; break;
		case 10: HP.size_ir2--; break;
		case 11: HP.size_ir3--; break;
		}
		(*enemyShips)[position.x][position.y] = -2;
		squareTab2[position.x][position.y] = hit;
		squareTab2[position.x][position.y].setPosition(sf::Vector2f(enemySetPoints.x + squareSize.x*position.x, enemySetPoints.y + squareSize.y*position.y));
		++totalHits;
		++totalShots;
		++maximumHitsTemp;
		updateMaximumMisses();
	}
	playerMoved = false;
	return false;
}

void Player::playerMouseInput(const sf::Time & dt, const sf::Vector2f & mousepos)
{
	sf::Vector2f cords(floor((mousepos.x - enemySetPoints.x) / squareSize.x), floor((mousepos.y - enemySetPoints.y) / squareSize.y));

	if (isMouseInEnemyBounds(mousepos))
	{
		rect.setPosition(sf::Vector2f(cords.x*squareSize.x + enemySetPoints.x, cords.y*squareSize.y + enemySetPoints.y));
	}
}

void Player::playerSetShips(const sf::Vector2f & position, std::vector<Board*>& vect_ship_to_draw)
{
	if (!shipsSetUp)
	{
		switch (counter)
		{
		case 0:; case 1:; case 2:; case 3:
			setShips[counter]->setPosition(position);
			if (setShips[counter]->getPlaceShip())
			{
				if (setShips[counter]->placePlayerShip(playerShips, mapSize, vect_ship_to_draw))
					counterToSet = true;
			}
			break;
		case 4:; case 5:
			setShips[counter]->setPosition(position);
			if (setShips[counter]->getPlaceShip())
			{
				if (setShips[counter]->placePlayerShip(playerShips, mapSize, vect_ship_to_draw))
					counterToSet = true;
			}
			break;
		}

		if (counterToSet)
		{
			++counter;
			counterToSet = false;
			if (counter == countOfShips)
				shipsSetUp = true;
			else
				setShips[counter]->setPosition(position);
		}
	}
}

void Player::draw(sf::RenderTarget & Window) const
{	
	if (shipsSetUp)
		Window.draw(rect);
	else
		Window.draw(setShips[counter]->returnShip());
}

void Player::drawSquareTab(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (const std::vector<sf::RectangleShape>& i : squareTab2)
		for (const sf::RectangleShape& rect : i)
			target.draw(rect, states);
}

bool Player::isMouseInEnemyBounds(const sf::Vector2f& mousepos) const
{
	if (mousepos.x >= enemySetPoints.x && mousepos.x < enemySetPoints.x + mapSize*squareSize.x && mousepos.y >= enemySetPoints.y && mousepos.y < enemySetPoints.y + mapSize*squareSize.y)
		return true;
	return false;
}

void Player::resetSquareTab(int num, std::vector<std::vector<sf::RectangleShape>>& newSquareTab)
{
	for (int i = 0; i < mapSize; ++i)
		for (int j = 0; j < mapSize; ++j)
		{
			if (setShips[num]->returnShip().getGlobalBounds().contains(playerSetPoints.x + squareSize.x / 2 + squareSize.x*j, playerSetPoints.y + squareSize.y / 2 + squareSize.y*i))
				if (newSquareTab[j][i].getTexture() != &TextureHandler::getInstance().texture_handler["X"])
					newSquareTab[j][i] = sf::RectangleShape();
		}
}

float Player::returnAccuracy() const
{
	if (totalShots != 0)
		return (static_cast<float>(totalHits) / static_cast<float>(totalShots)) * 100;
	else return 0;
}

