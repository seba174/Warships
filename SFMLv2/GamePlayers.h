#pragma once
#include <vector>
#include "Player.h"
#include "DestroyedShipsWithBackground.h"
#include "AdditionalSubMenu.h"
#include "Mouse_S.h"
#include "SetShipsAd.h"
#include "GameTime.h"
#include "FinishMenu.h"
#include "enumGamestate.h"


class Input;
class LanguageManager;


class GamePlayers
	: public sf::Drawable
{
	enum gamePlayersState { player1_moves, player2_moves, player1_setships, player2_setships, loadVariablesAndStart, finish, statistics };

	Player player1, player2;
	Mouse_S mouse_player1, mouse_player2;
	std::vector<Board*> vect_ship_to_draw_player1, vect_ship_to_draw_player2;
	DestroyedShipsWithBackground player1Background, player2Background;
	AdditionalSubMenu menuPlayer1SetShipsInfo, menuPlayer2SetShipsInfo, menuPlayer1TurnStarts, menuPlayer2TurnStarts;
	bool shoudlDrawMenuPlayer1SetShipsInfo, shoudlDrawMenuPlayer2SetShipsInfo, shoudlDrawMenuPlayer1TurnStarts, shoudlDrawMenuPlayer2TurnStarts;
	SetShipsAd advertPlayer1, advertPlayer2;
	bool player1Won, player2Won;
	FinishMenu finishMenu;

	gamePlayersState currentState;

	sf::Time lastFrameTime, utilityTime;
	GameTime gameTimer;

	sf::Time PausedSetShipsTime = sf::seconds(2.3);
	sf::Time TurnInfoTime = sf::seconds(0.6);

		// FUNCTIONS
	int whoStarts() const;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	// returns true if all of the any players' ships has zero HP
	bool checkForFinish() const;

	void updateBackgroundInformation();

	void updatePlayersFinishInformations();

public:

	void play(const sf::Time& dt, const sf::Vector2f& mousepos, const Input& input, LanguageManager& langMan, Gamestates& gamestate);

	GamePlayers(const sf::Vector2i& dim, const sf::Vector2f& SquareSize, const sf::Vector2f& player1_setpoints, const sf::Vector2f& player2_setpoints,
		const sf::RectangleShape& pudlo, const sf::RectangleShape& trafienie, sf::RectangleShape** player1Square_tab_2, sf::RectangleShape** player2Square_tab_2,
		int bar, sf::RectangleShape& player1Rect, sf::RectangleShape& player2Rect, const Mouse_S& pl1Mouse, const Mouse_S& pl2Mouse,
		const sf::Vector2f & title_or1st_button_position, int space_between_buttons, const sf::Vector2f& backgroundSize,
		const sf::Vector2f& backgroundForSubMenuPosition, float interfaceScale, LanguageManager& langMan,const sf::Vector2f& screenDim);

};

