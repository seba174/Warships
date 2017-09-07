#pragma once
#include "Ships_HP.h"
#include "Ships.h"



enum pos { Left, Up, Right, Down, Hold };

typedef struct Position
{
	bool key_pressed = false;
	float allign = 0;    // polozenie do ktorego ma sie dosunac kwadrat
	sf::Time time;
	bool towards = false;  // czy trzeba sie dosunac
	float move_speed = 0;
}Position;


class Player
{
public:
	Ships_HP HP;

protected:
	sf::Vector2i BoardDimensions;
	sf::Vector2f SquareSize;
	sf::Vector2f Enemy_SetPoints;
	sf::Vector2f Player_setPoints;
	unsigned int totalShots, totalHits;

	Board** set_ships; //tablica do rysowania
	bool ships_set_up;
	int counter = 0;

	const int count_of_ships = 6; //ilosc statkow w grze

	int** player_ships;
	int **enemy_ships;
	sf::RectangleShape** square_tab_2;
	sf::RectangleShape pudlo;
	sf::RectangleShape trafienie;
	bool plmoved = false;
	int number;
	sf::Vector2i cursorPosition;
	std::wstring name;

	float speed_ratio;	// mnoznik szybkosci ruchu w zaleznosci od mapy
	int where_move = pos::Hold;  // w ktora strone rusza sie kwadrat
	int check_rate = 20;   // czestotliwosc rysowania kwadratu (wiecej - mniejsze szarpanie ruchu)
	Position position[4];	// opcje dla poszczegolnych kierunkow ruchu
	int allign_speed = 100;		// minimalna szybkosc dosuwania kwadratu do krawedzi
	int max_speed = 700;
	int min_speed = 90;
	int bar;
	sf::RectangleShape& rect;

	
public:
	Player(const sf::Vector2i& dim, const sf::Vector2f& SquareSize, const sf::Vector2f& enemy_setpoints, int** enemy_ships, const sf::Vector2f& player_setpoints,
		const sf::RectangleShape& pudlo, const sf::RectangleShape& trafienie, sf::RectangleShape** square_tab_2, int bar, sf::RectangleShape& rect);
	
	bool Player_moves(const sf::Vector2i& position);
	void Player_input(const sf::Time& dt);

	void PlayerMouseInput(const sf::Time& dt, const sf::Vector2f& mousepos);
	void Player_Set_ships(const sf::Vector2f & position, std::vector<Board*>& vect_ship_to_draw);
	
	void Draw(sf::RenderTarget& Window) const;
	
	void setplaceship() { set_ships[counter]->setplaceShip(true); }

	int** getplayerships() { return player_ships; }

	void setenemyships(int ** ships) { enemy_ships = ships; }

	bool get_ships_set_up() const { return ships_set_up; }

	bool& getplmoved() { return plmoved; }

	void rotateShip() { set_ships[counter]->rotate_ship(); }

	sf::Vector2i getRectPositionInGame() const 
	{
		return sf::Vector2i(static_cast<int>(round((rect.getPosition().x - Enemy_SetPoints.x) / SquareSize.x)),
			static_cast<int>(round((rect.getPosition().y - Enemy_SetPoints.y) / SquareSize.y)));
	}

	void setPlayersCursorPositon(const sf::Vector2i& newPos) { cursorPosition = newPos; }

	sf::Vector2i getPlayersCursorPosition() const { return cursorPosition; }

	bool isMouseInEnemyBounds(const sf::Vector2f& mousepos) const;

	void resetSquareTab(int num, sf::RectangleShape** newSquareTab);
	
	sf::RectangleShape** returnSquareTab() { return square_tab_2; }

	void setPlayerName(const std::wstring& newName) { name = newName; }

	std::wstring getPlayerName() const { return name; }

	unsigned int returnTotalShotsNumber()const { return totalShots; }

	unsigned int returnTotalHitsNumber() const { return totalHits; }

	float returnAccuracy() const { if (totalShots != 0)return (static_cast<float>(totalHits) / static_cast<float>(totalShots)) * 100; else return 0; }

	// usunac
	void aaa() { totalHits = 50; totalShots = 70; }

	 ~Player();
};

