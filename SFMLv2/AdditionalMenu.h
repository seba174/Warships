#pragma once
#include "AdditionalSubMenu.h"
#include "enumAdditionalVisualInformation.h"
#include "enumGamestate.h"
#include "Input.h"

class AdditionalMenu :
	public sf::Drawable
{
	AdditionalVisualInformations& state;
	AdditionalSubMenu Exit, Loading;

	Gamestates newGamestate;

		// FUNCTIONS

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	// title_or1st_button_position non used
	AdditionalMenu(const sf::Vector2f& title_or1st_button_position, int space_between_buttons, const sf::Vector2f& backgroundSize, 
		const sf::Vector2f& backgroundForSubMenuPosition, AdditionalVisualInformations& additionalvsinfo, float interfaceScale);

	// updates information about OutlineColor for every SubMenu
	void updateAdditionalMenu();

	// updated and animates every SubMenu
	void updateAdditionalMenuWithAnimations(const sf::Time& time, const sf::Vector2f& mousepos);

	// function deals with running AdditionalMenu 
	// check if user clicks on buttons and does appropriate actions
	// in order to updateGamestates, use updateGamestate() function
	void runMenu(const sf::Vector2f& mousepos, bool leftButtonPressed, Input& input);

	// updates Gamestate
	void updateGamestate(Gamestates& gamestate);
};

