#pragma once
#include "Ships_HP.h"
#include "Ships.h"


class Player
{
public:
	Ships_HP HP;
	static const int maximumPlayerNameSize = 10;

protected:
	sf::Vector2i BoardDimensions;
	sf::Vector2f SquareSize;
	sf::Vector2f Enemy_SetPoints;
	sf::Vector2f Player_setPoints;
	unsigned int totalShots, totalHits;
	bool counter_to_set = false;
	unsigned int maximumHitsTemp, maximumHits, maximumMissesTemp, maximumMisses;

	Board** set_ships; 
	bool ships_set_up;
	int counter = 0;

	//number of ships in game
	const int count_of_ships = 6; 

	int** player_ships;
	int **enemy_ships;
	sf::RectangleShape** square_tab_2;
	sf::RectangleShape pudlo;
	sf::RectangleShape trafienie;
	bool plmoved = false;
	int number;
	sf::Vector2i cursorPosition;
	std::wstring name;
	sf::RectangleShape& rect;

	void updateMaximumHits();
	void updateMaximumMisses();

public:
	Player(const sf::Vector2i& dim, const sf::Vector2f& SquareSize, const sf::Vector2f& enemy_setpoints, int** enemy_ships, const sf::Vector2f& player_setpoints,
		const sf::RectangleShape& pudlo, const sf::RectangleShape& trafienie, sf::RectangleShape** square_tab_2, sf::RectangleShape& rect);
	
	bool Player_moves(const sf::Vector2i& position);

	void PlayerMouseInput(const sf::Time& dt, const sf::Vector2f& mousepos);

	void Player_Set_ships(const sf::Vector2f & position, std::vector<Board*>& vect_ship_to_draw);
	
	void Draw(sf::RenderTarget& Window) const;
	
	void setPlayersCursorPositon(const sf::Vector2i& newPos) { cursorPosition = newPos; }

	sf::Vector2i getPlayersCursorPosition() const { return cursorPosition; }

	bool isMouseInEnemyBounds(const sf::Vector2f& mousepos) const;

	void resetSquareTab(int num, sf::RectangleShape** newSquareTab);

	float returnAccuracy() const;

	~Player();


	sf::Vector2i getRectPositionInGame() const
	{
		return sf::Vector2i(static_cast<int>(round((rect.getPosition().x - Enemy_SetPoints.x) / SquareSize.x)),
			static_cast<int>(round((rect.getPosition().y - Enemy_SetPoints.y) / SquareSize.y)));
	}

	void setplaceship() { set_ships[counter]->setplaceShip(true); }

	int** getplayerships() { return player_ships; }

	void setenemyships(int ** ships) { enemy_ships = ships; }

	bool get_ships_set_up() const { return ships_set_up; }

	bool& getplmoved() { return plmoved; }

	void rotateShip() { set_ships[counter]->rotate_ship(); }
	
	sf::RectangleShape** returnSquareTab() { return square_tab_2; }

	void setPlayerName(const std::wstring& newName) { name = newName; }

	std::wstring getPlayerName() const { return name; }

	unsigned int returnTotalShotsNumber()const { return totalShots; }

	unsigned int returnTotalHitsNumber() const { return totalHits; }

	unsigned int retrunMaximumHits() { updateMaximumHits(); return maximumHits; }

	unsigned int returnMaximumMisses() { updateMaximumMisses(); return maximumMisses; }
};

