#pragma once
#include "SubMenu.h"
#include "OptionsSubMenu.h"
#include "enumGamestate.h"
#include "enumAdditionalVisualInformation.h"
#include "enumLevelsDifficulty.h"


class Menu :
	public sf::Drawable
{
	enum menustates { DEFAULT, CHOOSE_GAMETYPE, CHOOSE_MAPSIZE, CHOOSE_AILEVEL, LOADING_GAME_VARIABLES, OPTIONS, OPT_GENERAL, OPT_GRAPHICS, OPT_AUDIO };

	sf::Text MainTitle;
	
	menustates menustate, previousMenustate;
	Gamestates newGamestate, choosedGamemode;
	AdditionalVisualInformations newVSinfo;
	
	// SubMenus which Standard Menu contains
	SubMenu Home, ChooseGametype, ChooseMapSize, ChooseAILevel, Options;
	OptionsSubMenu General, Graphics, Audio;

		// FUNCTIONS

	// You need to use updateMenu() function before drawing
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	Menu(const std::string& main_title, const sf::Vector2f& main_title_position, const sf::Vector2f& title_or1st_button_position, int space_between_buttons);

	// function deals with running menu 
	// check if user clicks on buttons and does appropriate acctions
	// in order to updateGamestates, use updateGamestate() function
	void runMenu(const sf::Vector2f& mousepos, int& mapsize, LevelsDifficulty& level, bool leftButtonPressed);

	// updates information about OutlineColor for every SubMenu
	void updateMenu();

	// updates and animates every SubMenu
	void updateMenuWithAnimates(const sf::Time& time, const sf::Vector2f& mousepos);

	// resets Menu to the Home screen
	void Reset();

	// returns Gamestate choosed by user
	Gamestates getChoosedGamemode();

	// updates Gamestate and AdditionalVisualInformation
	void updateGamestate(Gamestates& gamestate, AdditionalVisualInformations& additionalvsinfo);
};

