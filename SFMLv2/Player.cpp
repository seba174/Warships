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
	const sf::Vector2f& player_setpoints, const sf::RectangleShape& pudlo, const sf::RectangleShape& trafienie, sf::RectangleShape ** square_tab_2,
	sf::RectangleShape& rect)
	: BoardDimensions(dim), SquareSize(SquareSize), Enemy_SetPoints(enemy_setpoints), Player_setPoints(player_setpoints), enemy_ships(enemy_ships),
	pudlo(pudlo), trafienie(trafienie), square_tab_2(square_tab_2), rect(rect), totalHits(0),totalShots(0)
{
	rect.setPosition(Enemy_SetPoints);
	number = static_cast<int>(BoardDimensions.x / SquareSize.x);

	TextureHandler& textures = TextureHandler::getInstance();
	set_ships = new Board*[count_of_ships];
	set_ships[0] = new Ships(5, SquareSize, BoardDimensions, Player_setPoints, &textures.texture_handler["big_body_final"]);
	set_ships[1] = new Ships(4, SquareSize, BoardDimensions, Player_setPoints, &textures.texture_handler["big_body_final"]);
	set_ships[2] = new Ships(3, SquareSize, BoardDimensions, Player_setPoints, &textures.texture_handler["big_body_final"]);
	set_ships[3] = new Ships(2, SquareSize, BoardDimensions, Player_setPoints, &textures.texture_handler["big_body_final"]);
	set_ships[4] = new IrregularShip2(SquareSize, BoardDimensions, Player_setPoints, &textures.texture_handler["irregular2"]);
	set_ships[5] = new IrregularShip3(SquareSize, BoardDimensions, Player_setPoints, &textures.texture_handler["irregular3"]);

	player_ships = new int*[number];
	for (int i = 0; i < number; i++)
	{
		player_ships[i] = new int[number];
		for (int j = 0; j < number; j++)
			player_ships[i][j] = 0;
	}
	this->ships_set_up = false;
}

bool Player::Player_moves(const sf::Vector2i & position)
{
	// chcecks if player has clicked button
	if (!getplmoved())
		return false;

	if (enemy_ships[position.x][position.y] == -2)
	{
	}
	else if (enemy_ships[position.x][position.y] == 0)
	{
		square_tab_2[position.x][position.y] = pudlo;
		square_tab_2[position.x][position.y].setPosition(sf::Vector2f(Enemy_SetPoints.x + SquareSize.x*position.x, Enemy_SetPoints.y + SquareSize.y*position.y));
		enemy_ships[position.x][position.y] = -2;
		plmoved = false;
		++totalShots;
		++maximumMissesTemp;
		updateMaximumHits();
		return true;
	}
	else if (enemy_ships[position.x][position.y])
	{
		switch (enemy_ships[position.x][position.y])
		{
		case 2: HP.size_2--; break;
		case 3: HP.size_3--; break;
		case 4: HP.size_4--; break;
		case 5: HP.size_5--; break;
		case 10: HP.size_ir2--; break;
		case 11: HP.size_ir3--; break;
		}
		enemy_ships[position.x][position.y] = -2;
		square_tab_2[position.x][position.y] = trafienie;
		square_tab_2[position.x][position.y].setPosition(sf::Vector2f(Enemy_SetPoints.x + SquareSize.x*position.x, Enemy_SetPoints.y + SquareSize.y*position.y));
		++totalHits;
		++totalShots;
		++maximumHitsTemp;
		updateMaximumMisses();
	}
	plmoved = false;
	return false;
}

void Player::PlayerMouseInput(const sf::Time & dt, const sf::Vector2f & mousepos)
{
	sf::Vector2f cords(floor((mousepos.x - Enemy_SetPoints.x) / SquareSize.x), floor((mousepos.y - Enemy_SetPoints.y) / SquareSize.y));

	if (isMouseInEnemyBounds(mousepos))
	{
		rect.setPosition(sf::Vector2f(cords.x*SquareSize.x + Enemy_SetPoints.x, cords.y*SquareSize.y + Enemy_SetPoints.y));
	}
}

void Player::Player_Set_ships(const sf::Vector2f & position, std::vector<Board*>& vect_ship_to_draw)
{
	if (!ships_set_up)
	{
		switch (counter)
		{
		case 0:; case 1:; case 2:; case 3:
			set_ships[counter]->setPosition(position);
			if (set_ships[counter]->getplaceShip())
			{
				if (set_ships[counter]->placePlayerShip(player_ships, number, vect_ship_to_draw, nullptr))
					counter_to_set = true;
			}

			break;
		case 4:; case 5:
			set_ships[counter]->setPosition(position);
			if (set_ships[counter]->getplaceShip())
			{
				if (set_ships[counter]->placePlayerShip(player_ships, number, vect_ship_to_draw, nullptr))
					counter_to_set = true;
			}
			break;
		}

		if (counter_to_set)
		{
			++counter;
			counter_to_set = false;
			if (counter == count_of_ships)
				ships_set_up = true;
			else
				set_ships[counter]->setPosition(position);
		}
	}
}

void Player::Draw(sf::RenderTarget & Window) const
{	
	if (ships_set_up)
		Window.draw(rect);
	else
		Window.draw(set_ships[counter]->return_ship());
}

bool Player::isMouseInEnemyBounds(const sf::Vector2f& mousepos) const
{
	if (mousepos.x >= Enemy_SetPoints.x && mousepos.x < Enemy_SetPoints.x + number*SquareSize.x && mousepos.y >= Enemy_SetPoints.y && mousepos.y < Enemy_SetPoints.y + number*SquareSize.y)
		return true;
	return false;
}

void Player::resetSquareTab(int num, sf::RectangleShape** newSquareTab)
{
	for (int i = 0; i < number; ++i)
		for (int j = 0; j < number; ++j)
		{
			if (set_ships[num]->return_ship().getGlobalBounds().contains(Player_setPoints.x + SquareSize.x / 2 + SquareSize.x*j, Player_setPoints.y + SquareSize.y / 2 + SquareSize.y*i))
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
	for (int i = 0; i < count_of_ships; i++)
		delete set_ships[i];
	delete[] set_ships;
	
	for (int i = 0; i < number; i++)
		delete[] player_ships[i];
	delete[] player_ships;
}

