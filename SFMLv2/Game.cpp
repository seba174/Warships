#include "Game.h"


Game::Game(const sf::Vector2i& dim, const sf::Vector2f& SquareSize, const sf::Vector2f& ai_setpoints, const sf::Vector2f& player_setpoints,
	const sf::RectangleShape& pudlo, const  sf::RectangleShape& trafienie, sf::RectangleShape** square_tab, sf::RectangleShape** square_tab_2,
	int bar, sf::RectangleShape& rect, LevelsDifficulty level)
	:AI(dim,SquareSize,player_setpoints), trafienie(trafienie), pudlo(pudlo), square_tab(square_tab), state(no_hit_yet), level(level),
	player(dim,SquareSize,ai_setpoints, nullptr,player_setpoints,pudlo,trafienie,square_tab_2,bar,rect)
{
	ai_ships = AI::get_AI_ships();
	player.setenemyships(AI::get_AI_ships());
	player_ships = player.getplayerships();
	gamestate = Player_move;
	
	modified_player_ships = new int*[AI::number];
	for (int i = 0; i < AI::number; i++)
		modified_player_ships[i] = new int[AI::number];
	
}

void Game::modified_set_minus1()
{
	for (int i = 0; i < AI::number; i++)
		for (int j = 0; j < AI::number; j++)
			if (modified_player_ships[i][j] != -2)
				modified_player_ships[i][j] = -1;
}

void Game::copy_player_ships()
{
	for (int i = 0; i < AI::number; i++)
		for (int j = 0; j < AI::number; j++)
			if (modified_player_ships[i][j] != -2)
				modified_player_ships[i][j] = player_ships[i][j];
}

bool Game::is_on_map(const sf::Vector2i& pos) const
{
	if (pos.x >= 0 && pos.x < AI::number)
		return true;
	return false;
}

void Game::set_modified_value(const sf::Vector2i& pos, int num, int ship_num)
{
	if (is_on_map(sf::Vector2i(pos.x, pos.y - 1)))
		if (modified_player_ships[pos.x][pos.y - 1] != -2)
		{
			if (player_ships[pos.x][pos.y - 1] == 0)
				modified_player_ships[pos.x][pos.y - 1] = num;
			else if (player_ships[pos.x][pos.y - 1] == ship_num)
				modified_player_ships[pos.x][pos.y - 1] = ship_num;
		}
			
	if (is_on_map(sf::Vector2i(pos.x + 1, pos.y)))
		if (modified_player_ships[pos.x + 1][pos.y] != -2)
		{
			if (player_ships[pos.x + 1][pos.y] == 0)
				modified_player_ships[pos.x + 1][pos.y] = num;
			else if (player_ships[pos.x + 1][pos.y] == ship_num)
				modified_player_ships[pos.x + 1][pos.y] = ship_num;
		}
	if (is_on_map(sf::Vector2i(pos.x, pos.y + 1)))
		if (modified_player_ships[pos.x][pos.y + 1] != -2)
		{
			if (player_ships[pos.x][pos.y + 1] == 0)
				modified_player_ships[pos.x][pos.y + 1] = num;
			else if (player_ships[pos.x][pos.y + 1] == ship_num)
				modified_player_ships[pos.x][pos.y + 1] = ship_num;
		}
	if (is_on_map(sf::Vector2i(pos.x - 1, pos.y)))
		if (modified_player_ships[pos.x - 1][pos.y] != -2)
		{
			if (player_ships[pos.x - 1][pos.y] == 0)
				modified_player_ships[pos.x - 1][pos.y] = num;
			else if(player_ships[pos.x - 1][pos.y] == ship_num)
				modified_player_ships[pos.x - 1][pos.y] = ship_num;
		}
}

/*void Game::AI_moves()
{
	static Info last;
	static int count;
	Info info;
	
	if (first)
	{
		for (int i = 0; i < AI::number; i++)
		{
			for (int j = 0; j < AI::number; j++)
				modified_player_ships[i][j] = player_ships[i][j];
		}
		first = false;
	}

	switch (state)
	{
	case no_hit_yet:
			info = AI::attack(modified_player_ships);

		if (info.what_hit)
		{
			square_tab[info.position.x][info.position.y] = trafienie;
			square_tab[info.position.x][info.position.y].setPosition(sf::Vector2f(info.position.x*AI::SquareSize.x + Player_SetPoints.x, info.position.y*AI::SquareSize.y + Player_SetPoints.y));

			//sf::Vertex* quad = &(*square_tab_v2)[(info.position.x + info.position.y * AI::AI::number) * 4];
			//quad[0].position = sf::Vector2f(Player_SetPoints.x + info.position.x * AI::SquareSize.x, Player_SetPoints.y + info.position.y  * AI::SquareSize.y);
			//quad[1].position = sf::Vector2f((Player_SetPoints.x + info.position.x + 1) * AI::SquareSize.x, Player_SetPoints.y + info.position.y  * AI::SquareSize.y);
			//quad[2].position = sf::Vector2f((Player_SetPoints.x + info.position.x + 1) * AI::SquareSize.x, Player_SetPoints.y + (info.position.y + 1) * AI::SquareSize.y);
			//quad[3].position = sf::Vector2f(Player_SetPoints.x + info.position.x * AI::SquareSize.x, Player_SetPoints.y + (info.position.y + 1) * AI::SquareSize.y);

			//quad[0].color = sf::Color::Red;
			//quad[1].color = sf::Color::Red;
			//quad[2].color = sf::Color::Red;
			//quad[3].color = sf::Color::Red;

			modified_player_ships[info.position.x][info.position.y] = -2;
			last = info;
			switch (info.what_hit)
			{
			case 2: state = hit_2; break;
			case 3: state = hit_3; break;
			case 4: state = hit_4; break;
			case 5: state = hit_5; break;
			case 10: state = hit_irregular2; break;
			case 11: state = hit_irregular3; break;
			}
			AI_moves();
		}
		else
		{
			square_tab[info.position.x][info.position.y] = pudlo;
			square_tab[info.position.x][info.position.y].setPosition(sf::Vector2f(info.position.x*AI::SquareSize.x + Player_SetPoints.x, info.position.y*AI::SquareSize.y + Player_SetPoints.y));

			//sf::Vertex* quad = &(*square_tab_v2)[(info.position.x + info.position.y * AI::AI::number) * 4];
			//quad[0].position = sf::Vector2f(Player_SetPoints.x + info.position.x * AI::SquareSize.x, Player_SetPoints.y + info.position.y  * AI::SquareSize.y);
			//quad[1].position = sf::Vector2f((Player_SetPoints.x + info.position.x + 1) * AI::SquareSize.x, Player_SetPoints.y + info.position.y  * AI::SquareSize.y);
			//quad[2].position = sf::Vector2f((Player_SetPoints.x + info.position.x + 1) * AI::SquareSize.x, Player_SetPoints.y + (info.position.y + 1) * AI::SquareSize.y);
			//quad[3].position = sf::Vector2f(Player_SetPoints.x + info.position.x * AI::SquareSize.x, Player_SetPoints.y + (info.position.y + 1) * AI::SquareSize.y);

			//quad[0].color = sf::Color::Green;
			//quad[1].color = sf::Color::Green;
			//quad[2].color = sf::Color::Green;
			//quad[3].color = sf::Color::Green;

			modified_player_ships[info.position.x][info.position.y] = -2;
		}
		break;
	case hit_2:
		if (count == 0)
			modified_set_minus1();
		++count;
		state = no_hit_yet;
		if (count == 2)
		{
			ai_ships_destroyed++;
			count = 0;
			copy_player_ships();
		}
		else
			set_modified_value(last.position, 0, 2);
		AI_moves();
		break;
	case hit_3:
		if (count == 0)
			modified_set_minus1();
		++count;
		state = no_hit_yet;
		if (count == 3)
		{
			ai_ships_destroyed++;
			count = 0;
			copy_player_ships();
		}
		else
			set_modified_value(last.position, 0, 3);
		AI_moves();

		break;
	case hit_4:
		if (count == 0)
			modified_set_minus1();
		++count;
		state = no_hit_yet;
		if (count == 4)
		{
			ai_ships_destroyed++;
			count = 0;
			copy_player_ships();
		}
		else
			set_modified_value(last.position, 0, 4);
		AI_moves();

		break;
	case hit_5:
		if (count == 0)
			modified_set_minus1();
		++count;
		state = no_hit_yet;
		if (count == 5)
		{
			ai_ships_destroyed++;
			count = 0;
			copy_player_ships();
		}
		else
			set_modified_value(last.position, 0, 5);
		AI_moves();

		break;
	case hit_irregular2:
		if (count == 0)
			modified_set_minus1();
		++count;
		state = no_hit_yet;
		if (count == 3)
		{
			ai_ships_destroyed++;
			count = 0;
			copy_player_ships();
		}
		else
			set_modified_value(last.position, 0, 10);
		AI_moves();

		break;
	case hit_irregular3:
		if (count == 0)
			modified_set_minus1();
		++count;
		state = no_hit_yet;
		if (count == 6)
		{
			ai_ships_destroyed++;
			count = 0;
			copy_player_ships();
		}
		else
			set_modified_value(last.position, 0, 11);
		AI_moves();

		break;	
	}
}*/

bool Game::AI_moves_level_easy()
{
	static Info last;
	static int count = 0;
	Info info;
	bool shoot_with_bounds = false;

	if (first)
	{
		for (int i = 0; i < AI::number; i++)
		{
			for (int j = 0; j < AI::number; j++)
				modified_player_ships[i][j] = player_ships[i][j];
		}
		first = false;
	}

	switch (state)
	{
	case no_hit_yet:
			info = AI::attack(modified_player_ships);

		if (info.what_hit)
		{
			square_tab[info.position.x][info.position.y] = trafienie;
			square_tab[info.position.x][info.position.y].setPosition(sf::Vector2f(info.position.x*AI::SquareSize.x + Player_SetPoints.x, info.position.y*AI::SquareSize.y + Player_SetPoints.y));

			modified_player_ships[info.position.x][info.position.y] = -2;
			last = info;
			
			++count;
			if (count == 23)
				ai_ships_destroyed = ShipNumber;

			return false;
		}
		else
		{
			square_tab[info.position.x][info.position.y] = pudlo;
			square_tab[info.position.x][info.position.y].setPosition(sf::Vector2f(info.position.x*AI::SquareSize.x + Player_SetPoints.x, info.position.y*AI::SquareSize.y + Player_SetPoints.y));

			modified_player_ships[info.position.x][info.position.y] = -2;

			return true;
		}
		break;
	}
}

bool Game::AI_moves_level_medium()
{
	static Info last;
	static int count;
	Info info;
	static bool shoot_with_bounds = false;

	if (first)
	{
		for (int i = 0; i < AI::number; i++)
		{
			for (int j = 0; j < AI::number; j++)
				modified_player_ships[i][j] = player_ships[i][j];
		}
		first = false;
	}

	switch (state)
	{
	case no_hit_yet:
		if (!shoot_with_bounds)
			info = AI::attack(modified_player_ships);
		else
			info = AI::attack_with_bounds(modified_player_ships, giveBounds(last.position).boundsX, giveBounds(last.position).boundsY);

		if (info.what_hit)
		{
			square_tab[info.position.x][info.position.y] = trafienie;
			square_tab[info.position.x][info.position.y].setPosition(
				sf::Vector2f(info.position.x*AI::SquareSize.x + Player_SetPoints.x, info.position.y*AI::SquareSize.y + Player_SetPoints.y));
			modified_player_ships[info.position.x][info.position.y] = -2;
			last = info;

			switch (info.what_hit)
			{
			case 2: state = hit_2; break;
			case 3: state = hit_3; break;
			case 4: state = hit_4; break;
			case 5: state = hit_5; break;
			case 10: state = hit_irregular2; break;
			case 11: state = hit_irregular3; break;
			}
			shoot_with_bounds = true;
			return false;
		}
		else
		{
			square_tab[info.position.x][info.position.y] = pudlo;
			square_tab[info.position.x][info.position.y].setPosition(
				sf::Vector2f(info.position.x*AI::SquareSize.x + Player_SetPoints.x, info.position.y*AI::SquareSize.y + Player_SetPoints.y));
			modified_player_ships[info.position.x][info.position.y] = -2;
			return true;
		}
		break;
	case hit_2:
		if (count == 0)
			modified_set_minus1();
		++count;
		state = no_hit_yet;
		if (count == 2)
		{
			ai_ships_destroyed++;
			count = 0;
			copy_player_ships();
			shoot_with_bounds = false;
		}
		else
		{
			set_modified_value(last.position, 0, 2);
			shoot_with_bounds = true;
		}
		return false;
		break;
	case hit_3:
		if (count == 0)
			modified_set_minus1();
		++count;
		state = no_hit_yet;
		if (count == 3)
		{
			ai_ships_destroyed++;
			count = 0;
			copy_player_ships();
			shoot_with_bounds = false;
		}
		else
		{
			set_modified_value(last.position, 0, 3);
			shoot_with_bounds = true;
		}
		return false;

		break;
	case hit_4:
		if (count == 0)
			modified_set_minus1();
		++count;
		state = no_hit_yet;
		if (count == 4)
		{
			ai_ships_destroyed++;
			count = 0;
			copy_player_ships();
			shoot_with_bounds = false;
		}
		else
		{
			set_modified_value(last.position, 0, 4);
			shoot_with_bounds = true;
		}
		return false;

		break;
	case hit_5:
		if (count == 0)
			modified_set_minus1();
		++count;
		state = no_hit_yet;
		if (count == 5)
		{
			ai_ships_destroyed++;
			count = 0;
			copy_player_ships();
			shoot_with_bounds = false;
		}
		else
		{
			set_modified_value(last.position, 0, 5);
			shoot_with_bounds = true;
		}
		return false;

		break;
	case hit_irregular2:
		if (count == 0)
			modified_set_minus1();
		++count;
		state = no_hit_yet;
		if (count == 3)
		{
			ai_ships_destroyed++;
			count = 0;
			copy_player_ships();
			shoot_with_bounds = false;
		}
		else
		{
			set_modified_value(last.position, 0, 10);
			shoot_with_bounds = true;
		}
		return false;

		break;
	case hit_irregular3:
		if (count == 0)
			modified_set_minus1();
		++count;
		state = no_hit_yet;
		if (count == 6)
		{
			ai_ships_destroyed++;
			count = 0;
			copy_player_ships();
			shoot_with_bounds = false;
		}
		else
		{
			set_modified_value(last.position, 0, 11);
			shoot_with_bounds = true;
		}
		return false;
		break;
	}
}

bool Game::AI_moves_level_hard()
{
	return false;
}

void Game::Draw(sf::RenderWindow & window) const
{
	player.Draw(window);
}

void Game::play(const sf::Time& dt, sf::Vector2i& position, const sf::Vector2f& mousepos)
{
	static sf::Time time;
	time += dt;
	const double reset_time = 0.25;

	//player.Player_input(dt);
	player.PlayerMouseInput(dt, mousepos);

	if (gamestate == AI_move)
	{
		if (time.asSeconds() > reset_time)
		{
			switch (level)
			{
			case EASY:
			{
				if (AI_moves_level_easy())
					gamestate = Player_move;
			}
			break;

			case MEDIUM:
			{
				if (AI_moves_level_medium())
					gamestate = Player_move;
			}
			break;

			case HARD:
			{

			}
			break;
			}

		}
	}
	else if (gamestate == Player_move)
	{
		if (player.Player_moves(position))
			gamestate = AI_move;
	}
	
	if (ai_ships_destroyed == ShipNumber)
		gamestate = AI_win;
	if (!player.HP.chceckhp())
		gamestate = Player_win;
	
	if (time.asSeconds() > reset_time)
	{
		time = sf::Time();
	}
}

DVector2i Game::giveBounds(const sf::Vector2i& pos) const
{
	sf::Vector2i outX, outY;

	outX.x = (pos.x - 4) > 0 ? (pos.x - 4) : 0;
	outX.y = (pos.x + 4) < AI::number ? (pos.x + 4) : (AI::number - 1);
	outY.x = (pos.y - 4) > 0 ? (pos.y - 4) : 0;
	outY.y = (pos.y + 4) < AI::number ? (pos.y + 4) : (AI::number - 1);
	return DVector2i(outX, outY);
}

Game::~Game()
{
	for (int i = 0; i < AI::number; i++)
		delete[] modified_player_ships[i];
	delete[] modified_player_ships;
}




