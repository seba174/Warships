#include "GamePlayers.h"
#include <random>
#include <Windows.h>
#include <iostream>
#include "Input.h"

using std::cout;
using std::endl;


int GamePlayers::whoStarts() const
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist_num(1, 2);

	return dist_num(mt);
}

void GamePlayers::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	switch (currentState)
	{
	case player1_moves:
	{
		cout << "Draw player1 moves" << endl;
		target.draw(player1Background, states);
		player1.Draw(target);
	} break;

	case player2_moves:
	{
		cout << "Draw player2 moves" << endl;
		target.draw(player2Background, states);
		player2.Draw(target);
	} break;

	case player1_setships:
	{
		cout << "Draw player1 setships" << endl;
		for (Board* ship : vect_ship_to_draw_player1)
		{
			cout << "Draw player1 setships - update" << endl;
			ship->updateTexture(lastFrameTime);
			target.draw(ship->return_ship(), states);
		}
		player1.Draw(target);
	} break;

	case player2_setships:
	{
		cout << "Draw player2 setships" << endl;
		for (Board* ship : vect_ship_to_draw_player2)
		{
			cout << "Draw player2 setships - update" << endl;
			ship->updateTexture(lastFrameTime);
			target.draw(ship->return_ship(), states);
		}
		player2.Draw(target);
	} break;

	}
}

bool GamePlayers::checkForFinish() const
{
	return !(player1.HP.chceckhp() && player2.HP.chceckhp());
}

void GamePlayers::updateBackgroundInformation()
{
	if (player1.HP.size_5 == 0)
		player1Background.markDestroyed(shipOrder::Ship5);
	if (player1.HP.size_4 == 0)
		player1Background.markDestroyed(shipOrder::Ship4);
	if (player1.HP.size_3 == 0)
		player1Background.markDestroyed(shipOrder::Ship3);
	if (player1.HP.size_2 == 0)
		player1Background.markDestroyed(shipOrder::Ship2);
	if (player1.HP.size_ir2 == 0)
		player1Background.markDestroyed(shipOrder::Ship2x2);
	if (player1.HP.size_ir3 == 0)
		player1Background.markDestroyed(shipOrder::Ship2x4);

	if (player2.HP.size_5 == 0)
		player2Background.markDestroyed(shipOrder::Ship5);
	if (player2.HP.size_4 == 0)
		player2Background.markDestroyed(shipOrder::Ship4);
	if (player2.HP.size_3 == 0)
		player2Background.markDestroyed(shipOrder::Ship3);
	if (player2.HP.size_2 == 0)
		player2Background.markDestroyed(shipOrder::Ship2);
	if (player2.HP.size_ir2 == 0)
		player2Background.markDestroyed(shipOrder::Ship2x2);
	if (player2.HP.size_ir3 == 0)
		player2Background.markDestroyed(shipOrder::Ship2x4);
}



void GamePlayers::play(const sf::Time & dt, const sf::Vector2f & mousepos, const Input& input)
{
	lastFrameTime = dt;

	switch (currentState)
	{
	case player1_setships:
	{
		cout << "Play player1 setships" << endl;

		if (mouse_player1.isMouseWithinArea())
		{
			cout << "Play player1 setships - elseif" << endl;
			if (input.isMouseLeftButtonPressed() && !player1.get_ships_set_up())
				player1.setplaceship();
			else if (input.isMouseRightButtonPressed() && !player1.get_ships_set_up())
				player1.rotateShip();

			player1.Player_Set_ships(mouse_player1.returnPositionInBounds(), vect_ship_to_draw_player1);
		}

		if (player1.get_ships_set_up())
			currentState = player2_setships;
	} break;

	case player2_setships:
	{
		cout << "Play player2 setships" << endl;

		if (mouse_player2.isMouseWithinArea())
		{
			cout << "Play player2 setships - elseif" << endl;
			if (input.isMouseLeftButtonPressed() && !player2.get_ships_set_up())
				player2.setplaceship();
			else if (input.isMouseRightButtonPressed() && !player2.get_ships_set_up())
				player2.rotateShip();

			player2.Player_Set_ships(mouse_player2.returnPositionInBounds(), vect_ship_to_draw_player2);
		}

		if (player2.get_ships_set_up())
		{
			currentState = loadVariablesAndStart;
		}
	} break;

	case loadVariablesAndStart:
	{
		cout << "loadvariablesandstart" << endl;
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
		player1.PlayerMouseInput(dt, mousepos);
		cout << "Play player1 moves" << endl;
		if (input.isMouseLeftButtonPressed() && player1.isMouseInEnemyBounds(mousepos))
			player1.getplmoved() = true;

		if (player1.Player_moves(player1.getRectPositionInGame()))
		{
			POINT point;
			GetCursorPos(&point);
			player1.setPlayersCursorPositon(sf::Vector2i(point.x, point.y));
			if (player2.getPlayersCursorPosition() != sf::Vector2i())
				SetCursorPos(player2.getPlayersCursorPosition().x, player2.getPlayersCursorPosition().y);

			currentState = player2_moves;
		}

		updateBackgroundInformation();
		if (checkForFinish())
		{

		}
	} break;

	case player2_moves:
	{
		player2.PlayerMouseInput(dt, mousepos);
		cout << "Play player2 moves" << endl;
		if (input.isMouseLeftButtonPressed() && player2.isMouseInEnemyBounds(mousepos))
			player2.getplmoved() = true;
		if (player2.Player_moves(player2.getRectPositionInGame()))
		{
			POINT point;
			GetCursorPos(&point);
			player2.setPlayersCursorPositon(sf::Vector2i(point.x, point.y));
			if (player1.getPlayersCursorPosition() != sf::Vector2i())
				SetCursorPos(player1.getPlayersCursorPosition().x, player1.getPlayersCursorPosition().y);

			currentState = player1_moves;
		}

		updateBackgroundInformation();
		if (checkForFinish())
		{

		}
	} break;

	}
}


GamePlayers::GamePlayers(const sf::Vector2i & dim, const sf::Vector2f & SquareSize, const sf::Vector2f & player1_setpoints, const sf::Vector2f & player2_setpoints,
	const sf::RectangleShape & pudlo, const sf::RectangleShape & trafienie, sf::RectangleShape ** player1Square_tab_2, sf::RectangleShape ** player2Square_tab_2, int bar,
	sf::RectangleShape & player1Rect, sf::RectangleShape & player2Rect, const Mouse_S& pl1Mouse, const Mouse_S& pl2Mouse)
	: player1(dim, SquareSize, player2_setpoints, nullptr, player1_setpoints, pudlo, trafienie, player1Square_tab_2, bar, player1Rect),
	player2(dim, SquareSize, player1_setpoints, nullptr, player2_setpoints, pudlo, trafienie, player2Square_tab_2, bar, player2Rect),
	mouse_player1(pl1Mouse),
	mouse_player2(pl2Mouse),
	player1Background(dim, SquareSize, player1_setpoints),
	player2Background(dim, SquareSize, player2_setpoints)
{
	currentState = player1_setships;

	player1.setenemyships(player2.getplayerships());
	player2.setenemyships(player1.getplayerships());
}


