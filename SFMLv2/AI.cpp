#include "AI.h"
#include "IrregularShip2.h"
#include "IrregularShip3.h"
#include "TextureHandler.h"
#include "DVector2i.h"


bool AI::checkSurround(const sf::Vector2i & pos, int** ships) const
{
	if (!(pos.x >= 0 && pos.x < number && pos.y >= 0 && pos.y < number))
		return false;
	if (pos.x - 1 >= 0)
		if (!(ships[pos.x - 1][pos.y] != -2))
			return false;
	if (pos.x + 1 < number)
		if (!(ships[pos.x + 1][pos.y] != -2))
			return false;
	if (pos.y - 1 >= 0)
		if (!(ships[pos.x][pos.y - 1] != -2))
			return false;
	if (pos.y + 1 < number)
		if (!(ships[pos.x][pos.y + 1] != -2))
			return false;
	return true;
}

void AI::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (shipsSetUp)
		target.draw(rect, states);
}

void AI::updateMaximumHits()
{
	if (maximumHitsTemp > maximumHits)
	{
		maximumHits = maximumHitsTemp;
	}
	maximumHitsTemp = 0;
}

void AI::updateMaximumMisses()
{
	if (maximumMissesTemp > maximumMisses)
	{
		maximumMisses = maximumMissesTemp;
	}
	maximumMissesTemp = 0;
}

void AI::actionsAfterHittingStandardShip(int size)
{
	if (count == 0)
		modifiedSetMinus1();
	++count;
	if (count == size)
	{
		//++ai_ships_destroyed;
		count = 0;
		copyPlayerShips();
		shootWithBounds = false;
	}
	else
	{
		setModifiedValue(last.position, 0, size);
		shootWithBounds = true;
	}
}

void AI::actionsAfterHittingIrregular2()
{
	if (count == 0)
		modifiedSetMinus1();
	++count;
	if (count == 3)
	{
		//ai_ships_destroyed++;
		count = 0;
		copyPlayerShips();
		shootWithBounds = false;
	}
	else
	{
		setModifiedValue(last.position, 0, 10);
		shootWithBounds = true;
	}
}

void AI::actionsAfterHittingIrregular3()
{
	if (count == 0)
		modifiedSetMinus1();
	++count;
	if (count == 6)
	{
		count = 0;
		copyPlayerShips();
		shootWithBounds = false;
	}
	else
	{
		setModifiedValue(last.position, 0, 11);
		shootWithBounds = true;
	}
}

AI::AI(const sf::Vector2i & dim, const sf::Vector2f & SquareSize, const sf::Vector2f & enemy_setpoints, int ** enemy_ships, const sf::Vector2f & player_setpoints, 
	const sf::RectangleShape & missedShot, const sf::RectangleShape & hit, sf::RectangleShape ** square_tab_2, sf::RectangleShape & rect)
	: boardDimensions(dim), squareSize(SquareSize), enemySetPoints(enemy_setpoints), AISetPoints(player_setpoints), enemyShips(enemy_ships),
	missedShot(missedShot), hit(hit), squareTab2(square_tab_2), rect(rect), totalHits(0), totalShots(0), rd()
{
	rect.setPosition(enemySetPoints);
	number = static_cast<int>(boardDimensions.x / SquareSize.x);
	mt = std::mt19937(rd());

	TextureHandler& textures = TextureHandler::getInstance();
	setShips = new Board*[countOfShips];
	setShips[0] = new Ships(5, SquareSize, boardDimensions, AISetPoints, &textures.texture_handler["big_body_final"]);
	setShips[1] = new Ships(4, SquareSize, boardDimensions, AISetPoints, &textures.texture_handler["big_body_final"]);
	setShips[2] = new Ships(3, SquareSize, boardDimensions, AISetPoints, &textures.texture_handler["big_body_final"]);
	setShips[3] = new Ships(2, SquareSize, boardDimensions, AISetPoints, &textures.texture_handler["big_body_final"]);
	setShips[4] = new IrregularShip2(SquareSize, boardDimensions, AISetPoints, &textures.texture_handler["irregular2"]);
	setShips[5] = new IrregularShip3(SquareSize, boardDimensions, AISetPoints, &textures.texture_handler["irregular3"]);

	AIShips = new int*[number];
	for (int i = 0; i < number; i++)
	{
		AIShips[i] = new int[number];
		for (int j = 0; j < number; j++)
			AIShips[i][j] = 0;
	}

	modifiedEnemyShips = new int*[AI::number];
	for (int i = 0; i < AI::number; i++)
		modifiedEnemyShips[i] = new int[AI::number];

	this->shipsSetUp = false;
}

void AI::placeShips(std::vector<Board*>& VectRect)
{
	int counter = 0;
	std::uniform_int_distribution<int> dist_num(0, number - 1), dist_rot(0, 3);

	while (counter < countOfShips)
	{
		sf::Vector2f position(dist_num(mt)*squareSize.x, (dist_num(mt))*squareSize.y);
		int rotation = dist_rot(mt);
		
		for (int i = 0; i < rotation; i++)
			setShips[counter]->rotate_ship();

		setShips[counter]->setPosition(position);
		if (setShips[counter]->placePlayerShip(AIShips, number, VectRect)) 
			counter++;
	}
	shipsSetUp = true;
}

Info AI::attack() 
{
	int counter = 0;
	int max = 10 * number;
	std::uniform_int_distribution<int> dist_num(0, number - 1);
	while (true)
	{
		sf::Vector2i rand(dist_num(mt), dist_num(mt));
		if (counter < max)
		{
			if (modifiedEnemyShips[rand.x][rand.y] != -1 && modifiedEnemyShips[rand.x][rand.y] != -2 && checkSurround(rand, modifiedEnemyShips))
				return Info(rand, modifiedEnemyShips[rand.x][rand.y]);
		}
		else
		{
			if (modifiedEnemyShips[rand.x][rand.y] != -1 && modifiedEnemyShips[rand.x][rand.y] != -2)
				return Info(rand, modifiedEnemyShips[rand.x][rand.y]);
		}
		++counter;
	}
}

void AI::modifiedSetMinus1()
{
	for (int i = 0; i < AI::number; i++)
		for (int j = 0; j < AI::number; j++)
			if (modifiedEnemyShips[i][j] != -2)
				modifiedEnemyShips[i][j] = -1;
}

void AI::copyPlayerShips()
{
	for (int i = 0; i < AI::number; i++)
		for (int j = 0; j < AI::number; j++)
			if (modifiedEnemyShips[i][j] != -2)
				modifiedEnemyShips[i][j] = enemyShips[i][j];
}

bool AI::isOnMap(const sf::Vector2i & pos) const
{
	if (pos.x >= 0 && pos.x < AI::number)
		return true;
	return false;
}

void AI::setModifiedValue(const sf::Vector2i & pos, int num, int ship_num)
{
	if (isOnMap(sf::Vector2i(pos.x, pos.y - 1)))
		if (modifiedEnemyShips[pos.x][pos.y - 1] != -2)
		{
			if (enemyShips[pos.x][pos.y - 1] == 0)
				modifiedEnemyShips[pos.x][pos.y - 1] = num;
			else if (enemyShips[pos.x][pos.y - 1] == ship_num)
				modifiedEnemyShips[pos.x][pos.y - 1] = ship_num;
		}

	if (isOnMap(sf::Vector2i(pos.x + 1, pos.y)))
		if (modifiedEnemyShips[pos.x + 1][pos.y] != -2)
		{
			if (enemyShips[pos.x + 1][pos.y] == 0)
				modifiedEnemyShips[pos.x + 1][pos.y] = num;
			else if (enemyShips[pos.x + 1][pos.y] == ship_num)
				modifiedEnemyShips[pos.x + 1][pos.y] = ship_num;
		}
	if (isOnMap(sf::Vector2i(pos.x, pos.y + 1)))
		if (modifiedEnemyShips[pos.x][pos.y + 1] != -2)
		{
			if (enemyShips[pos.x][pos.y + 1] == 0)
				modifiedEnemyShips[pos.x][pos.y + 1] = num;
			else if (enemyShips[pos.x][pos.y + 1] == ship_num)
				modifiedEnemyShips[pos.x][pos.y + 1] = ship_num;
		}
	if (isOnMap(sf::Vector2i(pos.x - 1, pos.y)))
		if (modifiedEnemyShips[pos.x - 1][pos.y] != -2)
		{
			if (enemyShips[pos.x - 1][pos.y] == 0)
				modifiedEnemyShips[pos.x - 1][pos.y] = num;
			else if (enemyShips[pos.x - 1][pos.y] == ship_num)
				modifiedEnemyShips[pos.x - 1][pos.y] = ship_num;
		}
}

DVector2i AI::giveBounds(const sf::Vector2i & pos) const
{
	sf::Vector2i outX, outY;

	outX.x = (pos.x - 4) > 0 ? (pos.x - 4) : 0;
	outX.y = (pos.x + 4) < AI::number ? (pos.x + 4) : (AI::number - 1);
	outY.x = (pos.y - 4) > 0 ? (pos.y - 4) : 0;
	outY.y = (pos.y + 4) < AI::number ? (pos.y + 4) : (AI::number - 1);
	return DVector2i(outX, outY);
}

bool AI::AIMovesLevelEasy()
{
	Info info;

	if (first)
	{
		for (int i = 0; i < AI::number; i++)
		{
			for (int j = 0; j < AI::number; j++)
				modifiedEnemyShips[i][j] = enemyShips[i][j];
		}
		first = false;
	}
	info = AI::attack();

	if (info.what_hit)
	{
		squareTab2[info.position.x][info.position.y] = hit;
		squareTab2[info.position.x][info.position.y].setPosition(sf::Vector2f(info.position.x*AI::squareSize.x + enemySetPoints.x, info.position.y*AI::squareSize.y + enemySetPoints.y));
		rect.setPosition(squareTab2[info.position.x][info.position.y].getPosition());
		modifiedEnemyShips[info.position.x][info.position.y] = -2;
		last = info;

		switch (info.what_hit)
		{
		case 2: HP.size_2--; break;
		case 3: HP.size_3--; break;
		case 4: HP.size_4--; break;
		case 5: HP.size_5--; break;
		case 10: HP.size_ir2--; break;
		case 11: HP.size_ir3--; break;
		}

		++totalHits;
		++totalShots;
		++maximumHitsTemp;
		updateMaximumMisses();

		++count;
		return false;
	}
	else
	{
		squareTab2[info.position.x][info.position.y] = missedShot;
		squareTab2[info.position.x][info.position.y].setPosition(sf::Vector2f(info.position.x*AI::squareSize.x + enemySetPoints.x, info.position.y*AI::squareSize.y + enemySetPoints.y));
		rect.setPosition(squareTab2[info.position.x][info.position.y].getPosition());
		modifiedEnemyShips[info.position.x][info.position.y] = -2;

		++totalShots;
		++maximumMissesTemp;
		updateMaximumHits();
		return true;
	}
	return true;
}

bool AI::AIMovesLevelMedium()
{
	Info info;

	if (first)
	{
		for (int i = 0; i < AI::number; i++)
		{
			for (int j = 0; j < AI::number; j++)
				modifiedEnemyShips[i][j] = enemyShips[i][j];
		}
		first = false;
	}

	if (!shootWithBounds)
		info = AI::attack();
	else
		info = AI::attackWithBounds(giveBounds(last.position).boundsX, giveBounds(last.position).boundsY);

	if (info.what_hit)
	{
		squareTab2[info.position.x][info.position.y] = hit;
		squareTab2[info.position.x][info.position.y].setPosition(
			sf::Vector2f(info.position.x*AI::squareSize.x + enemySetPoints.x, info.position.y*AI::squareSize.y + enemySetPoints.y));
		modifiedEnemyShips[info.position.x][info.position.y] = -2;
		rect.setPosition(squareTab2[info.position.x][info.position.y].getPosition());
		last = info;

		++totalHits;
		++totalShots;
		++maximumHitsTemp;
		updateMaximumMisses();

		switch (info.what_hit)
		{
		case 2:
		{
			actionsAfterHittingStandardShip(2);
			HP.size_2--;
		} break;
		case 3:
		{
			actionsAfterHittingStandardShip(3);
			HP.size_3--;
		} break;
		case 4:
		{
			actionsAfterHittingStandardShip(4);
			HP.size_4--;
		} break;
		case 5:
		{
			actionsAfterHittingStandardShip(5);
			HP.size_5--;
		} break;
		case 10:
		{
			actionsAfterHittingIrregular2();
			HP.size_ir2--;
		} break;
		case 11:
		{
			actionsAfterHittingIrregular3();
			HP.size_ir3--;
		} break;
		}
		return false;
	}
	else
	{
		squareTab2[info.position.x][info.position.y] = missedShot;
		squareTab2[info.position.x][info.position.y].setPosition(
			sf::Vector2f(info.position.x*AI::squareSize.x + enemySetPoints.x, info.position.y*AI::squareSize.y + enemySetPoints.y));
		rect.setPosition(squareTab2[info.position.x][info.position.y].getPosition());
		modifiedEnemyShips[info.position.x][info.position.y] = -2;

		++totalShots;
		++maximumMissesTemp;
		updateMaximumHits();
		return true;
	}
	return true;
}

bool AI::AIMovesLevelHard()
{
	return false;
}

void AI::resetSquareTab(int num, sf::RectangleShape ** newSquareTab)
{
	for (int i = 0; i < number; ++i)
		for (int j = 0; j < number; ++j)
		{
			if (setShips[num]->return_ship().getGlobalBounds().contains(AISetPoints.x + squareSize.x / 2 + squareSize.x*j, AISetPoints.y + squareSize.y / 2 + squareSize.y*i))
				if (newSquareTab[j][i].getTexture() != &TextureHandler::getInstance().texture_handler["X"])
					newSquareTab[j][i] = sf::RectangleShape();
		}
}

float AI::returnAccuracy() const
{
	if (totalShots != 0)
		return (static_cast<float>(totalHits) / static_cast<float>(totalShots)) * 100;
	else return 0;
}

AI::~AI()
{
	for (int i = 0; i < countOfShips; i++)
		delete setShips[i];
	delete[] setShips;

	for (int i = 0; i < number; i++)
		delete[] AIShips[i];
	delete[] AIShips;

	for (int i = 0; i < AI::number; i++)
		delete[] modifiedEnemyShips[i];
	delete[] modifiedEnemyShips;
}

Info AI::attackWithBounds(const sf::Vector2i& boundsX, const sf::Vector2i& boundsY) 
{
	
	std::uniform_int_distribution<int> dist_num_x(boundsX.x, boundsX.y), dist_num_y(boundsY.x, boundsY.y);
	while (true)
	{
		sf::Vector2i rand(dist_num_x(mt), dist_num_y(mt));
		if (modifiedEnemyShips[rand.x][rand.y] != -1 && modifiedEnemyShips[rand.x][rand.y] != -2)
			return Info(rand, modifiedEnemyShips[rand.x][rand.y]);
	}
}

Info::Info(const sf::Vector2i & position, int what_hit): position(position), what_hit(what_hit)
{
}
