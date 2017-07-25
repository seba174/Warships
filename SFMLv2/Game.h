#pragma once
#include <cstring>
#include "AI.h"
#include "Ships_HP.h"
#include "Player.h"
#include "DVector2i.h"
#include "enumLevelsDifficulty.h"

using std::string;

const int ShipNumber = 6;
enum PlayervsAistates {None, Player_move, AI_move, Player_win, AI_win};

class Game :
	public AI
{
	enum states { no_hit_yet, hit_5, hit_4, hit_3, hit_2, hit_irregular2, hit_irregular3 };

	PlayervsAistates gamestate;
	states state;
	sf::RectangleShape pudlo;
	sf::RectangleShape trafienie;
	bool first = true;

	//AI
	int **player_ships;
	int **modified_player_ships;
	int **ai_ships;
	int ai_ships_destroyed = 0;
	sf::RectangleShape** square_tab;
	LevelsDifficulty level;

	//Player
	Player player;

public:
	Game(const sf::Vector2i& dim, const sf::Vector2f& SquareSize, const sf::Vector2f& ai_setpoints, const sf::Vector2f& player_setpoints,
		const sf::RectangleShape& pudlo, const sf::RectangleShape& trafienie, sf::RectangleShape** square_tab, sf::RectangleShape** square_tab_2,
		int bar, sf::RectangleShape&, LevelsDifficulty level );

	void modified_set_minus1();

	void copy_player_ships();

	bool is_on_map(const sf::Vector2i& pos) const;

	void set_modified_value(const sf::Vector2i& pos, int num, int ship_num);
	
	// returns true when AI misses
	bool AI_moves_level_easy();
	// returns true when AI misses
	bool AI_moves_level_medium(); 
	// returns true when AI misses
	bool AI_moves_level_hard();

	void Draw(sf::RenderWindow& window) const;

	void play(const sf::Time& dt, sf::Vector2i& position, const sf::Vector2f& mousepos);

	DVector2i giveBounds(const sf::Vector2i& pos) const;

	void Player_set_ships(const sf::Vector2f & position, std::vector<Board*>& vect_ship_to_draw) { player.Player_Set_ships(position, vect_ship_to_draw); }

	bool& setplmoved() { return player.getplmoved(); }

	void rotate_player_ship() { player.rotate(); }

	void set_player_placeships() { player.setplaceship(); }

	bool get_ships_set_up() const {  return player.get_ships_set_up(); }

	PlayervsAistates getGameState() const { return gamestate; }

	virtual ~Game();
};

