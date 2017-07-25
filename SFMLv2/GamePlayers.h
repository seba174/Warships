#pragma once
#include <vector>
#include <random>
#include "Player.h"
#include "Input.h"
#include "Mouse_S.h"


class GamePlayers
	: public sf::Drawable
{
	enum gamestate { player1_moves, player2_moves, player1_setships, player2_setships, loadVariablesAndStart };


	Player player1, player2;
	Mouse_S mouse_player1, mouse_player2;
	std::vector<Board*> vect_ship_to_draw_player1, vect_ship_to_draw_player2;

	gamestate currentState;

		// FUNCTIONS
	int whoStarts() const;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	// returns true if all of the any players' ships has zero HP
	bool checkForFinish() const;

public:

	void play(const sf::Time& dt, sf::Vector2i& position, const sf::Vector2f& mousepos, const Input& input);

	GamePlayers();
	~GamePlayers();
};

