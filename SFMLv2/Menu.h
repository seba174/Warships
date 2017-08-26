#pragma once
#include "SubMenu.h"
#include "OptionsSubMenu.h"
#include "enumMenustate.h"
#include "enumGamestate.h"
#include "enumAdditionalVisualInformation.h"
#include "enumLevelsDifficulty.h"

class LanguageManager;
class Options;
class GeneralOptions;

class Menu :
	public sf::Drawable
{
	sf::Text MainTitle;
	
	Menustates menustate, previousMenustate;
	Gamestates newGamestate, choosedGamemode;
	AdditionalVisualInformations newVSinfo;
	
	// SubMenus which Standard Menu contains
	SubMenu SubHome, SubChooseGametype, SubChooseMapSize, SubChooseAILevel, SubOptions;
	OptionsSubMenu SubGeneral, SubGraphics, SubAudio;

		// FUNCTIONS

	// You need to use updateMenu() function before drawing
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	bool hasVisibleOptionChanged(const Options& options);

	bool hasVisibleGeneralOptionChanged(const GeneralOptions& options);


public:
	Menu(const std::wstring& main_title, const sf::Vector2f& main_title_position, const sf::Vector2f& title_or1st_button_position, int space_between_buttons,
		float interfaceScale, const Options& opt, LanguageManager& languageManager, const GeneralOptions& genOpt);

	// function deals with running menu 
	// check if user clicks on buttons and does appropriate acctions
	// in order to updateGamestates, use updateGamestate() function
	void runMenu(const sf::Vector2f& mousepos, int& mapsize, LevelsDifficulty& level, bool leftButtonPressed, Options& opt, GeneralOptions& generalOpt);

	// updates information about OutlineColor for every SubMenu
	void updateMenu();

	// updates and animates every SubMenu
	void updateMenuWithAnimates(const sf::Time& time, const sf::Vector2f& mousepos);

	// resets Menu to the Home screen
	void Reset();

	// gets current menustate
	Menustates getMenustate() const { return menustate; }

	// sets new menustate
	void setMenustate(Menustates newState) { menustate = newState; }

	// returns Gamestate choosed by user
	Gamestates getChoosedGamemode();

	// updates Gamestate and AdditionalVisualInformation
	void updateGamestate(Gamestates& gamestate, AdditionalVisualInformations& additionalvsinfo);
};

