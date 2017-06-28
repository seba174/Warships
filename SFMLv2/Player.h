#pragma once
#include "Ships_HP.h"
#include "Ships.h"
#include "IrregularShip2.h"
#include "IrregularShip3.h"
#include "TextureHandler.h"

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
	Player(const sf::Vector2i dim, const sf::Vector2f SquareSize, const sf::Vector2f enemy_setpoints, int** enemy_ships, const sf::Vector2f player_setpoints,
		const sf::RectangleShape pudlo, const sf::RectangleShape trafienie, sf::RectangleShape** square_tab_2,const int bar, sf::RectangleShape& rect);
	
	bool Player_moves(sf::Vector2i& position);
	void Player_input(const sf::Time& dt);
	void Player_Set_ships(sf::Vector2f & position, std::vector<Board*>& vect_ship_to_draw);
	
	void Draw(sf::RenderWindow& Window);
	
	void setplaceship();
	int** getplayerships() { return player_ships; }
	void setenemyships(int ** ships) { enemy_ships = ships; }
	bool get_ships_set_up() const { return ships_set_up; }
	bool& getplmoved();
	void rotate();
	
	virtual ~Player();
};

