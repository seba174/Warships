#include "AdditionalMenu.h"

void AdditionalMenu::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	switch (state)
	{
	case NONE:
		break;
	case EXIT_INFO:
		target.draw(Exit, states); break;
	case LOADING:
		target.draw(Loading, states); break;
	}
}

AdditionalMenu::AdditionalMenu(const sf::Vector2f & title_or1st_button_position, int space_between_buttons, const sf::Vector2f& backgroundSize,
	const sf::Vector2f& backgroundForSubMenuPosition, AdditionalVisualInformations& additionalvsinfo)
	: state(additionalvsinfo)
{
	// SubMenu title character size
	const int title_size = 55;

	// SubMenu character size
	const int submenu_size = 38;

	// Background for SubMenu size
	sf::Vector2f backgroundForSubmenuSize(550, 360);

	// Background for SubMenu Color
	sf::Color backgroundForSubMenuColor = sf::Color::Red;

	// Background Color for Exit
	sf::Color backgroundExitColor = sf::Color(0, 0, 0, 200);

	// Button size
	sf::Vector2f button_size(330, 70);

	// Bounds color
	sf::Color bounds_color = sf::Color::White;

	FontHandler& handler = FontHandler::getInstance();

	state = AdditionalVisualInformations::NONE;
	newGamestate = Gamestates::NOTHING;

	// Position of title and button is based on backgroundForSubMenuPosition!

	Exit.construct(backgroundSize,backgroundForSubmenuSize,backgroundForSubMenuPosition,backgroundForSubMenuColor,backgroundExitColor,sf::Vector2f(0,0),
		"What do you want to do?", "Resume,Return to Main Menu,Quit the game",title_size, submenu_size, title_or1st_button_position,
		sf::Vector2f(title_or1st_button_position.x, title_or1st_button_position.y + space_between_buttons), button_size, space_between_buttons,
		bounds_color, handler.font_handler["Mecha"]);

	Loading.construct(backgroundSize, backgroundForSubmenuSize, sf::Vector2f(backgroundForSubMenuPosition.x, backgroundForSubMenuPosition.y + title_size),
		sf::Color::Transparent, sf::Color::Black, sf::Vector2f(0, 0), "Loading...", "", title_size, submenu_size,
		title_or1st_button_position, title_or1st_button_position, button_size, space_between_buttons, bounds_color, handler.font_handler["Mecha"]);
	
}

void AdditionalMenu::updateAdditionalMenu()
{
	Exit.updateButtons();
	Loading.updateButtons();
}

void AdditionalMenu::updateAdditionalMenuWithAnimations(const sf::Time & time, const sf::Vector2f& mousepos)
{
	Exit.highlightButtonContaining(mousepos);

	Exit.updateButtonsWithAnimations(time);
	Loading.updateButtonsWithAnimations(time);
}

void AdditionalMenu::runMenu(const sf::Vector2f & mousepos, bool leftButtonPressed, Input& input)
{
	// Additional menu has highest priority in managing input
	if (state != AdditionalVisualInformations::NONE)
		input.ResetKeys();

	switch (state)
	{
	case EXIT_INFO: {
		//Exit.highlightButtonContaining(mousepos);
		newGamestate = PAUSED;
		if (leftButtonPressed)
		{
			if (Exit.contains(0, mousepos)) // Resume button
				state = AdditionalVisualInformations::NONE;
			else if (Exit.contains(1, mousepos)) // Return to main menu button
			{
				newGamestate = Gamestates::BREAK_AND_GO_TO_MENU;
				state = AdditionalVisualInformations::NONE;
			}
			else if (Exit.contains(2, mousepos)) // Quit the game button
			{
				newGamestate = EXIT;
				state = AdditionalVisualInformations::NONE;
			}
		}
	} break;
	
	case LOADING: {
		
	} break;

	}
}

void AdditionalMenu::updateGamestate(Gamestates & gamestate)
{
	if (newGamestate != Gamestates::NOTHING)
		gamestate = newGamestate;
	newGamestate = Gamestates::NOTHING;
}
