#pragma once
#include <vector>
#include "Player.h"
#include "DestroyedShipsWithBackground.h"
#include "Mouse_S.h"


class Input;

class GamePlayers
	: public sf::Drawable
{
	enum gamestate { player1_moves, player2_moves, player1_setships, player2_setships, loadVariablesAndStart };

	Player player1, player2;
	Mouse_S mouse_player1, mouse_player2;
	std::vector<Board*> vect_ship_to_draw_player1, vect_ship_to_draw_player2;
	DestroyedShipsWithBackground player1Background, player2Background;

	gamestate currentState;

	sf::Time lastFrameTime;

		// FUNCTIONS
	int whoStarts() const;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	// returns true if all of the any players' ships has zero HP
	bool checkForFinish() const;

	void updateBackgroundInformation();

public:

	void play(const sf::Time& dt, const sf::Vector2f& mousepos, const Input& input);

	GamePlayers(const sf::Vector2i& dim, const sf::Vector2f& SquareSize, const sf::Vector2f& player1_setpoints, const sf::Vector2f& player2_setpoints,
		const sf::RectangleShape& pudlo, const sf::RectangleShape& trafienie, sf::RectangleShape** player1Square_tab_2, sf::RectangleShape** player2Square_tab_2,
		int bar, sf::RectangleShape& player1Rect, sf::RectangleShape& player2Rect, const Mouse_S& pl1Mouse, const Mouse_S& pl2Mouse);

};

