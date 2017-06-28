#include "Player.h"



Player::Player(const sf::Vector2i dim, const sf::Vector2f SquareSize, const sf::Vector2f enemy_setpoints, int ** enemy_ships,
	const sf::Vector2f player_setpoints, const sf::RectangleShape pudlo, const sf::RectangleShape trafienie, sf::RectangleShape ** square_tab_2, 
	const int bar,  sf::RectangleShape& rect)
	: BoardDimensions(dim), SquareSize(SquareSize), Enemy_SetPoints(enemy_setpoints),Player_setPoints(player_setpoints), enemy_ships(enemy_ships),
	pudlo(pudlo), trafienie(trafienie), square_tab_2(square_tab_2), bar(bar), rect(rect)
{
	number = BoardDimensions.x / SquareSize.x;
	switch (number)
	{
	case 10:
		speed_ratio = 4;
		break;
	case 20:
		speed_ratio = 2;
		break;
	case 40:
		speed_ratio = 1.5;
	}

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

bool Player::Player_moves(sf::Vector2i & position)
{
	if (enemy_ships[position.x][position.y] == -2)
	{
	}
	else if (enemy_ships[position.x][position.y] == 0)
	{
		square_tab_2[position.x][position.y] = pudlo;
		square_tab_2[position.x][position.y].setPosition(sf::Vector2f(Enemy_SetPoints.x + SquareSize.x*position.x, Enemy_SetPoints.y + SquareSize.y*position.y));
		enemy_ships[position.x][position.y] = -2;
		plmoved = false;
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
	}
	plmoved = false;
	return false;
}

void Player::Player_input(const sf::Time& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (rect.getPosition().x + 1.99*SquareSize.x < BoardDimensions.x)		//sprawdzanie czy nie opuszczamy ekranu
		{
			position[pos::Right].key_pressed = true; where_move = pos::Right;
		}
		else if (position[pos::Right].towards == true)		// ustawienie predkosci przy dosuwaniu kwadratu do odpowiedniego miejsca
			if (position[pos::Right].move_speed < allign_speed * speed_ratio)
				position[pos::Right].move_speed = allign_speed * speed_ratio;	// minimalna szybkosc 
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (rect.getPosition().x - 0.99*SquareSize.x > 0)
		{
			position[pos::Left].key_pressed = true; where_move = pos::Left;
		}
		else if (position[pos::Left].towards == true)
			if (position[pos::Left].move_speed < allign_speed * speed_ratio)
				position[pos::Left].move_speed = allign_speed * speed_ratio;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (rect.getPosition().y - 0.99*SquareSize.y > bar)
		{
			position[pos::Up].key_pressed = true; where_move = pos::Up;
		}
		else if (position[pos::Up].towards == true)
			if (position[pos::Up].move_speed < allign_speed * speed_ratio)
				position[pos::Up].move_speed = allign_speed * speed_ratio;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (rect.getPosition().y + 1.99*SquareSize.y < BoardDimensions.y + bar)
		{
			position[pos::Down].key_pressed = true; where_move = pos::Down;

		}
		else if (position[pos::Down].towards == true)
			if (position[pos::Down].move_speed < allign_speed * speed_ratio)
				position[pos::Down].move_speed = allign_speed * speed_ratio;
	}


	if (position[pos::Right].key_pressed)
	{
		position[pos::Right].time += dt;
		position[pos::Right].move_speed = position[pos::Right].time.asMilliseconds() * speed_ratio;		// aktualizacja aktualnej predkosci (wzrost liniowy)

		if (position[pos::Right].move_speed > max_speed*speed_ratio)	// maksymalna predkosc
			position[pos::Right].move_speed = max_speed*speed_ratio;
		else if (position[pos::Right].move_speed < min_speed*speed_ratio)	// minimalna predkosc
			position[pos::Right].move_speed = min_speed*speed_ratio;
	}
	else
	{
		position[pos::Right].time = sf::Time();		// zerowanie predkosci gdy odpuscimy klawisz

		if (position[pos::Left].key_pressed)
		{
			position[pos::Left].time += dt;
			position[pos::Left].move_speed = position[pos::Left].time.asMilliseconds() * speed_ratio;

			if (position[pos::Left].move_speed > max_speed*speed_ratio)
				position[pos::Left].move_speed = max_speed*speed_ratio;
			else if (position[pos::Left].move_speed < min_speed*speed_ratio)
				position[pos::Left].move_speed = min_speed*speed_ratio;
		}
		else
		{
			position[pos::Left].time = sf::Time();

			if (position[pos::Up].key_pressed)
			{
				position[pos::Up].time += dt;
				position[pos::Up].move_speed = position[pos::Up].time.asMilliseconds() * speed_ratio;

				if (position[pos::Up].move_speed > max_speed*speed_ratio)
					position[pos::Up].move_speed = max_speed*speed_ratio;
				else if (position[pos::Up].move_speed < min_speed*speed_ratio)
					position[pos::Up].move_speed = min_speed*speed_ratio;
			}
			else
			{
				position[pos::Up].time = sf::Time();

				if (position[pos::Down].key_pressed)
				{
					position[pos::Down].time += dt;
					position[pos::Down].move_speed = position[pos::Down].time.asMilliseconds() * speed_ratio;

					if (position[pos::Down].move_speed > max_speed*speed_ratio)
						position[pos::Down].move_speed = max_speed*speed_ratio;
					else if (position[pos::Down].move_speed < min_speed*speed_ratio)
						position[pos::Down].move_speed = min_speed*speed_ratio;
				}
				else
					position[pos::Down].time = sf::Time();
			}
		}
	}

	if (position[pos::Right].towards)	// jesli dosuwamy sie do krawedzi, to blokujemy mozliwosc uzycia innych klawiszy
	{
		where_move = pos::Right;
		position[pos::Left].key_pressed = false;
		position[pos::Up].key_pressed = false;
		position[pos::Down].key_pressed = false;
	}
	if (position[pos::Left].towards)
	{
		where_move = pos::Left;
		position[pos::Right].key_pressed = false;
		position[pos::Up].key_pressed = false;
		position[pos::Down].key_pressed = false;
	}
	if (position[pos::Up].towards)
	{
		where_move = pos::Up;
		position[pos::Left].key_pressed = false;
		position[pos::Right].key_pressed = false;
		position[pos::Down].key_pressed = false;
	}
	if (position[pos::Down].towards)
	{
		where_move = pos::Down;
		position[pos::Left].key_pressed = false;
		position[pos::Up].key_pressed = false;
		position[pos::Right].key_pressed = false;
	}

	// ruch w zaleznosci od wybranego kierunku
	switch (where_move)
	{
	case pos::Right:
		//if (!position[pos::Left].towards && !position[pos::Up].towards && !position[pos::Down].towards)

		if (position[pos::Right].key_pressed)    // jesli klawisz jest wcisniety to ruszamy sie i zapisujemy pozycje do ktorej sie dosuniemy
		{
			rect.move(sf::Vector2f(position[pos::Right].move_speed * dt.asSeconds(), 0));
			position[pos::Right].allign = floor(rect.getPosition().x / SquareSize.x) + 1;
			position[pos::Right].key_pressed = false;
			position[pos::Right].towards = true;
		}
		else  // dosuniecie do odpowiedniego miejsca
		{
			position[pos::Up].time = sf::Time();
			position[pos::Left].time = sf::Time();
			position[pos::Down].time = sf::Time();

			if (rect.getPosition().x / SquareSize.x < position[pos::Right].allign)		// jesli ciagle mozna sie poruszyc to sie ruszamy
				for (int j = 0; j < check_rate; j++)
				{
					if (rect.getPosition().x / SquareSize.x < position[pos::Right].allign)
						rect.move(sf::Vector2f(position[pos::Right].move_speed / check_rate * dt.asSeconds(), 0));
					position[pos::Right].towards = true;
				}

			else if (rect.getPosition().x / SquareSize.x >= position[pos::Right].allign)	// ustawiamy kwadrat w odpowiedniej pozycji
			{
				rect.setPosition(SquareSize.x*position[pos::Right].allign, rect.getPosition().y);
				where_move = pos::Hold;
				position[pos::Right].towards = false;
			}
		}
		break;
	case pos::Left:
		if (position[pos::Left].key_pressed)
		{
			rect.move(sf::Vector2f(-position[pos::Left].move_speed * dt.asSeconds(), 0));
			position[pos::Left].allign = floor(rect.getPosition().x / SquareSize.x);
			position[pos::Left].key_pressed = false;
			position[pos::Left].towards = true;
		}
		else
		{
			position[pos::Up].time = sf::Time();
			position[pos::Right].time = sf::Time();
			position[pos::Down].time = sf::Time();
			if (rect.getPosition().x / SquareSize.x <= position[pos::Left].allign)
			{
				rect.setPosition(SquareSize.x*position[pos::Left].allign, rect.getPosition().y);
				where_move = pos::Hold;
				position[pos::Left].towards = false;
			}
			else if (rect.getPosition().x / SquareSize.x > position[pos::Left].allign)
			{
				for (int j = 0; j < check_rate; j++)
				{
					if (rect.getPosition().x / SquareSize.x > position[pos::Left].allign)
						rect.move(sf::Vector2f(-position[pos::Left].move_speed / check_rate * dt.asSeconds(), 0));
					position[pos::Left].towards = true;
				}
			}
		}
		break;
	case pos::Up:
		if (position[pos::Up].key_pressed)
		{
			rect.move(sf::Vector2f(0, -position[pos::Up].move_speed * dt.asSeconds()));
			position[pos::Up].allign = floor((rect.getPosition().y - bar) / SquareSize.y);
			position[pos::Up].key_pressed = false;
			position[pos::Up].towards = true;
		}
		else
		{
			position[pos::Left].time = sf::Time();
			position[pos::Right].time = sf::Time();
			position[pos::Down].time = sf::Time();

			if ((rect.getPosition().y - bar) / SquareSize.y <= position[pos::Up].allign)
			{
				rect.setPosition(rect.getPosition().x, SquareSize.y*position[pos::Up].allign + bar);
				where_move = pos::Hold;
				position[pos::Up].towards = false;
			}
			else if ((rect.getPosition().y - bar) / SquareSize.y > position[pos::Up].allign)
			{
				for (int j = 0; j < check_rate; j++)
				{
					if ((rect.getPosition().y - bar) / SquareSize.y > position[pos::Up].allign)
						rect.move(sf::Vector2f(0, -position[pos::Up].move_speed / check_rate * dt.asSeconds()));
					position[pos::Up].towards = true;
				}
			}
		}
		break;
	case pos::Down:
		if (position[pos::Down].key_pressed)
		{
			rect.move(sf::Vector2f(0, position[pos::Down].move_speed * dt.asSeconds()));
			position[pos::Down].allign = floor((rect.getPosition().y - bar) / SquareSize.y) + 1;
			position[pos::Down].key_pressed = false;
			position[pos::Down].towards = true;
		}
		else
		{
			position[pos::Left].time = sf::Time();
			position[pos::Right].time = sf::Time();
			position[pos::Up].time = sf::Time();

			if ((rect.getPosition().y - bar) / SquareSize.y < position[pos::Down].allign)
			{
				for (int j = 0; j < check_rate; j++)
				{
					if ((rect.getPosition().y - bar) / SquareSize.y < position[pos::Down].allign)
						rect.move(sf::Vector2f(0, position[pos::Down].move_speed / check_rate* dt.asSeconds()));
					position[pos::Down].towards = true;
				}
			}
			else if ((rect.getPosition().y - bar) / SquareSize.y >= position[pos::Down].allign)
			{
				rect.setPosition(rect.getPosition().x, SquareSize.y*position[pos::Down].allign + bar);
				where_move = pos::Hold;
				position[pos::Down].towards = false;
			}
		}
	}
}

void Player::Player_Set_ships(sf::Vector2f & position, std::vector<Board*>& vect_ship_to_draw)
{
	if (!ships_set_up)
	{
		static bool counter_to_set = false;
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

void Player::setplaceship()
{
	set_ships[counter]->setplaceShip(true);
}

void Player::Draw(sf::RenderWindow & Window)
{
	Window.draw(rect);
	if (!ships_set_up)
		Window.draw(set_ships[counter]->return_ship());
}

bool & Player::getplmoved()
{
	return plmoved;
}

void Player::rotate()
{
	set_ships[counter]->rotate_ship();
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








