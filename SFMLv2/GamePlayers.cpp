#include "GamePlayers.h"



int GamePlayers::whoStarts() const
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist_num(1, 2);

	return dist_num(mt);
}

void GamePlayers::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
}

bool GamePlayers::checkForFinish() const
{
	return !(player1.HP.chceckhp() || player2.HP.chceckhp());
}

GamePlayers::GamePlayers()
{
}

void GamePlayers::play(const sf::Time & dt, sf::Vector2i & position, const sf::Vector2f & mousepos, const Input& input)
{
	switch (currentState)
	{
	case player1_setships:
	{
		if (player1.get_ships_set_up())
			currentState = player2_setships;

		if (mouse_player1.isMouseWithinArea())
		{
			if (input.isMouseLeftButtonPressed() && !player1.get_ships_set_up())
				player1.setplaceship();
			if (input.isMouseRightButtonPressed() && !player1.get_ships_set_up())
				player1.setplaceship();

			player1.Player_Set_ships(mouse_player1.returnPositionInBounds(), vect_ship_to_draw_player1);
		}
	} break;

	case player2_setships:
	{
		if (player2.get_ships_set_up())
		{
			currentState = loadVariablesAndStart;
		}

		if (mouse_player2.isMouseWithinArea())
		{
			if (input.isMouseLeftButtonPressed() && !player2.get_ships_set_up())
				player2.setplaceship();
			if (input.isMouseRightButtonPressed() && !player2.get_ships_set_up())
				player2.setplaceship();

			player2.Player_Set_ships(mouse_player2.returnPositionInBounds(), vect_ship_to_draw_player2);
		}
	} break;

	case loadVariablesAndStart:
	{
		player1.setenemyships(player2.getplayerships());
		player2.setenemyships(player1.getplayerships());


		int who = whoStarts();

		if (who == 1)
			currentState = player1_moves;
		else if (who == 2)
			currentState = player2_moves;
	} break;

	case player1_moves:
	{
		if (player1.Player_moves(position))
		{
			currentState = player2_moves;
		}

		if (checkForFinish())
		{

		}
	} break;

	case player2_moves:
	{
		if (player2.Player_moves(position))
		{
			currentState = player1_moves;
		}

		if (checkForFinish())
		{

		}
	} break;


	}
}




GamePlayers::~GamePlayers()
{
}
