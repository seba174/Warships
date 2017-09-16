#pragma once
#include <vector>
#include "Player.h"
#include "DestroyedShipsWithBackground.h"
#include "AdditionalSubMenu.h"
#include "Mouse_S.h"
#include "SetShipsAd.h"
#include "GameTime.h"
#include "FinishMenu.h"
#include "StatisticsMenu.h"
#include "enumGamestate.h"
#include "rectangleWithTextAndFrames.h"
#include "enumLevelsDifficulty.h"
#include "AI.h"


class Input;
class LanguageManager;
class GeneralOptions;


class GamePlayerVsAI
	: public sf::Drawable
{
	enum gamePlayersState { player1Moves, AIMoves, player1SetShips, AISetShips, loadVariablesAndStart, finish, statistics };

	Player player1;
	AI player2;
	Mouse_S mousePlayer1, mousePlayer2;
	std::vector<Board*> vectShipsToDrawPlayer1, vectShipsToDrawPlayer2;
	DestroyedShipsWithBackground player1Background, player2Background;
	AdditionalSubMenu menuPlayer1SetShipsInfo, menuPlayer2SetShipsInfo, menuPlayer1TurnStarts, menuPlayer2TurnStarts;
	bool shoudlDrawMenuPlayer1SetShipsInfo, shoudlDrawMenuPlayer2SetShipsInfo, shoudlDrawMenuPlayer1TurnStarts, shoudlDrawMenuPlayer2TurnStarts;
	SetShipsAd advertPlayer1, advertPlayer2;
	bool player1Won, player2Won;
	bool aiFinishesMove = false, shouldAIWait = false;
	FinishMenu finishMenu;
	StatisticsMenu statisticsMenu;
	LevelsDifficulty level;

	std::vector<RectangleWithTextAndFrames> helpInformationPlayer1, helpInformationPlayer2;
	sf::RectangleShape helpButtonPlayer1, helpButtonPlayer2;
	bool shouldDisplayHelpPlayer1, shouldDisplayHelpPlayer2;

	gamePlayersState currentState;

	sf::Time lastFrameTime, utilityTime;
	GameTime gameTimer;

	sf::Time PausedSetShipsTime = sf::seconds(2.0f);
	sf::Time TurnInfoTime = sf::seconds(0.5f);
	sf::Time AIDelay = sf::seconds(0.7f);
	sf::Clock utilityClock, utilityClock2;

	// FUNCTIONS
	int whoStarts() const;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	// returns true if all of the any players' ships has zero HP
	bool checkForFinish() const;

	void updateBackgroundInformation();

	void updatePlayersFinishInformations(LanguageManager& langMan);

	std::wstring stringToWstringConversion(const std::string& s);

public:

	void play(const sf::Time& dt, const sf::Vector2f& mousepos, const Input& input, LanguageManager& langMan, Gamestates& gamestate);

	GamePlayerVsAI(const sf::Vector2i& dim, const sf::Vector2f& SquareSize, const sf::Vector2f& player1_setpoints, const sf::Vector2f& player2_setpoints,
		const sf::RectangleShape& pudlo, const sf::RectangleShape& trafienie, sf::RectangleShape** player1Square_tab_2, sf::RectangleShape** player2Square_tab_2,
		sf::RectangleShape& player1Rect, sf::RectangleShape& player2Rect, const Mouse_S& pl1Mouse, const Mouse_S& pl2Mouse,
		const sf::Vector2f & title_or1st_button_position, int space_between_buttons, const sf::Vector2f& backgroundSize,
		const sf::Vector2f& backgroundForSubMenuPosition, float interfaceScale, LanguageManager& langMan, const sf::Vector2f& screenDim, const GeneralOptions& genOpt,
		LevelsDifficulty level);

};

