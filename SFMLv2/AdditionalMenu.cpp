#include "AdditionalMenu.h"
#include "Input.h"
#include "Options.h"
#include "LanguageManager.h"
#include "GeneralOptions.h"

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
	case APPLY_CHANGES_GRAPHICS:
		target.draw(ApplyChanges, states); break;
	case APPLY_CHANGES_GENERAL:
		target.draw(ApplyChanges, states); break;
	}
}

AdditionalMenu::AdditionalMenu(const sf::Vector2f & title_or1st_button_position, int space_between_buttons, const sf::Vector2f& backgroundSize,
	const sf::Vector2f& backgroundForSubMenuPosition, AdditionalVisualInformations& additionalvsinfo, float interfaceScale, LanguageManager& langMan)
	: state(additionalvsinfo)
{
	// SubMenu title character size
	int title_size_1 = 50 * interfaceScale;
	int title_size_2 = 50 * interfaceScale;


	// SubMenu character size
	int submenu_size = 32 * interfaceScale;

	// Background for SubMenu Exit size
	sf::Vector2f backgroundForSubmenuExitSize(600 * interfaceScale, 380 * interfaceScale);

	// Background for SubMenu Exit size
	sf::Vector2f backgroundForSubmenuApplyChangesSize(700 * interfaceScale, 320 * interfaceScale);

	// Background for SubMenu Color
	sf::Color backgroundForSubMenuColor = sf::Color::Red;

	// Background Color for Exit
	sf::Color backgroundExitColor = sf::Color(0, 0, 0, 200);

	sf::Color buttonInteriorColor = sf::Color(0, 0, 0, 150);

	// Button size
	sf::Vector2f button_size(360 * interfaceScale, 70 * interfaceScale);

	// Bounds color
	sf::Color bounds_color = sf::Color::White;

	FontHandler& handler = FontHandler::getInstance();

	state = AdditionalVisualInformations::NONE;
	newGamestate = Gamestates::NOTHING;

	// Position of title and button is based on backgroundForSubMenuPosition!

	Exit.construct(backgroundSize, backgroundForSubmenuExitSize, backgroundForSubMenuPosition, backgroundForSubMenuColor, backgroundExitColor, sf::Vector2f(0, 0),
		langMan.getText("What do you want to do") + L'?', langMan.getText("Resume") + L',' + langMan.getText("Return to Main Menu") + L',' + langMan.getText("Quit the game"),
		title_size_1, submenu_size, title_or1st_button_position, sf::Vector2f(title_or1st_button_position.x, title_or1st_button_position.y + space_between_buttons),
		button_size, space_between_buttons, bounds_color, handler.font_handler["Mecha"], interfaceScale);
	Exit.setInteriorColorAllButtons(buttonInteriorColor);

	Loading.construct(backgroundSize, backgroundForSubmenuExitSize, sf::Vector2f(backgroundForSubMenuPosition.x, backgroundForSubMenuPosition.y + title_size_1),
		sf::Color::Transparent, sf::Color::Black, sf::Vector2f(0, 0), langMan.getText("Loading") + L"...", L"", title_size_1, submenu_size,
		title_or1st_button_position, title_or1st_button_position, button_size, space_between_buttons, bounds_color, handler.font_handler["Mecha"], interfaceScale);

	ApplyChanges.construct(backgroundSize, backgroundForSubmenuApplyChangesSize, backgroundForSubMenuPosition, backgroundForSubMenuColor, backgroundExitColor, sf::Vector2f(0, 0),
		langMan.getText("Do you wish to save changes") + L'?', langMan.getText("Yes") + L',' + langMan.getText("No"), title_size_2, submenu_size, title_or1st_button_position,
		sf::Vector2f(title_or1st_button_position.x, title_or1st_button_position.y + space_between_buttons), button_size, space_between_buttons,
		bounds_color, handler.font_handler["Mecha"], interfaceScale);
	ApplyChanges.setInteriorColorAllButtons(buttonInteriorColor);

}

void AdditionalMenu::updateAdditionalMenu()
{
	Exit.updateButtons();
	Loading.updateButtons();
}

void AdditionalMenu::updateAdditionalMenuWithAnimations(const sf::Time & time, const sf::Vector2f& mousepos)
{
	Exit.highlightButtonContaining(mousepos);
	ApplyChanges.highlightButtonContaining(mousepos);

	Exit.updateButtonsWithAnimations(time);
	ApplyChanges.updateButtonsWithAnimations(time);

	Loading.updateButtonsWithAnimations(time);
}

void AdditionalMenu::runMenu(const sf::Vector2f & mousepos, bool leftButtonPressed, Input& input, Options& options, GeneralOptions& genOptions)
{
	if (state == AdditionalVisualInformations::NONE && input.isKeyboardEscapeKeyPressed())
		state = AdditionalVisualInformations::EXIT_INFO;
	else if (state == AdditionalVisualInformations::EXIT_INFO && input.isKeyboardEscapeKeyPressed())
		state = AdditionalVisualInformations::NONE;

	switch (state)
	{
	case EXIT_INFO: {
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
	
	case LOADING: {} break;

	case APPLY_CHANGES_GRAPHICS:
	{
		newGamestate = PAUSED;
		if (leftButtonPressed)
		{
			if (ApplyChanges.contains(0, mousepos)) // Yes button
			{
				state = AdditionalVisualInformations::NONE;
				newGamestate = Gamestates::MENU;
				options.saveToPreviousOptions();
			}
			else if (ApplyChanges.contains(1, mousepos)) // No button
			{
				state = AdditionalVisualInformations::NONE;
				newGamestate = Gamestates::RESTORE_GRAPHICS;
				options.restorePreviousOptions();
			}
		}
	} break;

	case APPLY_CHANGES_GENERAL:
	{
		newGamestate = PAUSED;
		if (leftButtonPressed)
		{
			if (ApplyChanges.contains(0, mousepos)) // Yes button
			{
				state = AdditionalVisualInformations::NONE;
				newGamestate = Gamestates::MENU;
				genOptions.saveToPreviousOptions();
			}
			else if (ApplyChanges.contains(1, mousepos)) // No button
			{
				state = AdditionalVisualInformations::NONE;
				newGamestate = Gamestates::RESTORE_GENERAL;
				genOptions.restorePreviousOptions();
			}
		}
	} break;

	}

	// Additional menu has highest priority in managing input
	if (state != AdditionalVisualInformations::NONE)
		input.ResetKeys();
}

void AdditionalMenu::updateGamestate(Gamestates & gamestate)
{
	if (newGamestate != Gamestates::NOTHING)
		gamestate = newGamestate;
	newGamestate = Gamestates::NOTHING;
}
