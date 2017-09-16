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

Player::Player(const sf::Vector2i& dim, const sf::Vector2f& SquareSize, const sf::Vector2f& enemy_setpoints, int ** enemy_ships,
	const sf::Vector2f& player_setpoints, const sf::RectangleShape& missedShot, const sf::RectangleShape& hit, sf::RectangleShape ** square_tab_2,
	sf::RectangleShape& rect)
	: boardDimensions(dim), squareSize(SquareSize), enemySetPoints(enemy_setpoints), playerSetPoints(player_setpoints), enemyShips(enemy_ships),
	missedShot(missedShot), hit(hit), squareTab2(square_tab_2), rect(rect), totalHits(0),totalShots(0)
{
	rect.setPosition(enemySetPoints);
	mapSize = static_cast<int>(boardDimensions.x / SquareSize.x);

	TextureHandler& textures = TextureHandler::getInstance();
	setShips = new Board*[countOfShips];
	setShips[0] = new Ships(5, SquareSize, boardDimensions, playerSetPoints, &textures.texture_handler["big_body_final"]);
	setShips[1] = new Ships(4, SquareSize, boardDimensions, playerSetPoints, &textures.texture_handler["big_body_final"]);
	setShips[2] = new Ships(3, SquareSize, boardDimensions, playerSetPoints, &textures.texture_handler["big_body_final"]);
	setShips[3] = new Ships(2, SquareSize, boardDimensions, playerSetPoints, &textures.texture_handler["big_body_final"]);
	setShips[4] = new IrregularShip2(SquareSize, boardDimensions, playerSetPoints, &textures.texture_handler["irregular2"]);
	setShips[5] = new IrregularShip3(SquareSize, boardDimensions, playerSetPoints, &textures.texture_handler["irregular3"]);

	playerShips = new int*[mapSize];
	for (int i = 0; i < mapSize; i++)
	{
		playerShips[i] = new int[mapSize];
		for (int j = 0; j < mapSize; j++)
			playerShips[i][j] = 0;
	}
	this->shipsSetUp = false;
}

bool Player::playerMoves(const sf::Vector2i & position)
{
	// chcecks if player has clicked button
	if (!getPlayerMoved())
		return false;

	if (enemyShips[position.x][position.y] == -2)
	{
	}
	else if (enemyShips[position.x][position.y] == 0)
	{
		squareTab2[position.x][position.y] = missedShot;
		squareTab2[position.x][position.y].setPosition(sf::Vector2f(enemySetPoints.x + squareSize.x*position.x, enemySetPoints.y + squareSize.y*position.y));
		enemyShips[position.x][position.y] = -2;
		playerMoved = false;
		++totalShots;
		++maximumMissesTemp;
		updateMaximumHits();
		return true;
	}
	else if (enemyShips[position.x][position.y])
	{
		switch (enemyShips[position.x][position.y])
		{
		case 2: HP.size_2--; break;
		case 3: HP.size_3--; break;
		case 4: HP.size_4--; break;
		case 5: HP.size_5--; break;
		case 10: HP.size_ir2--; break;
		case 11: HP.size_ir3--; break;
		}
		enemyShips[position.x][position.y] = -2;
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
			if (setShips[counter]->getplaceShip())
			{
				if (setShips[counter]->placePlayerShip(playerShips, mapSize, vect_ship_to_draw))
					counterToSet = true;
			}

			break;
		case 4:; case 5:
			setShips[counter]->setPosition(position);
			if (setShips[counter]->getplaceShip())
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
		Window.draw(setShips[counter]->return_ship());
}

bool Player::isMouseInEnemyBounds(const sf::Vector2f& mousepos) const
{
	if (mousepos.x >= enemySetPoints.x && mousepos.x < enemySetPoints.x + mapSize*squareSize.x && mousepos.y >= enemySetPoints.y && mousepos.y < enemySetPoints.y + mapSize*squareSize.y)
		return true;
	return false;
}

void Player::resetSquareTab(int num, sf::RectangleShape** newSquareTab)
{
	for (int i = 0; i < mapSize; ++i)
		for (int j = 0; j < mapSize; ++j)
		{
			if (setShips[num]->return_ship().getGlobalBounds().contains(playerSetPoints.x + squareSize.x / 2 + squareSize.x*j, playerSetPoints.y + squareSize.y / 2 + squareSize.y*i))
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

Player::~Player()
{
	for (int i = 0; i < countOfShips; i++)
		delete setShips[i];
	delete[] setShips;
	
	for (int i = 0; i < mapSize; i++)
		delete[] playerShips[i];
	delete[] playerShips;
}

