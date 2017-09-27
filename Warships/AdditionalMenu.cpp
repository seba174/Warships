#include "stdafx.h"
#include "AdditionalMenu.h"
#include "Input.h"
#include "GraphicsOptions.h"
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
	int title_size_1 = static_cast<int>(45 * interfaceScale);
	int title_size_2 = static_cast<int>(42 * interfaceScale);


	// SubMenu character size
	int submenu_size = static_cast<int>(28 * interfaceScale);

	// Background for SubMenu Exit size
	sf::Vector2f backgroundForSubmenuExitSize(690 * interfaceScale, 380 * interfaceScale);

	// Background for SubMenu Exit size
	sf::Vector2f backgroundForSubmenuApplyChangesSize(800 * interfaceScale, 320 * interfaceScale);

	// Background for SubMenu Color
	sf::Color backgroundForSubMenuColor = sf::Color::Red;

	// Background Color for Exit
	sf::Color backgroundExitColor = sf::Color(0, 0, 0, 200);

	sf::Color buttonInteriorColor = sf::Color(0, 0, 0, 150);

	// Button size
	sf::Vector2f button_size(400 * interfaceScale, 70 * interfaceScale);

	//Outline thickenss for background
	float outlineThickness = 5 * interfaceScale;

	//Outline color for background
	sf::Color outlineColor = sf::Color::White;

	// Bounds color
	sf::Color bounds_color = sf::Color::White;

	FontHandler& handler = FontHandler::getInstance();

	state = AdditionalVisualInformations::NONE;
	newGamestate = GameStates::nothing;

	// Position of title and button is based on backgroundForSubMenuPosition!

	Exit.construct(backgroundSize, backgroundForSubmenuExitSize, backgroundForSubMenuPosition, backgroundForSubMenuColor, backgroundExitColor, sf::Vector2f(0, 0),
		langMan.getText("What do you want to do") + L'?', langMan.getText("Resume") + L',' + langMan.getText("Return to Main Menu") + L',' + langMan.getText("Quit the game"),
		title_size_1, submenu_size, title_or1st_button_position, sf::Vector2f(title_or1st_button_position.x, title_or1st_button_position.y + space_between_buttons),
		button_size, space_between_buttons, bounds_color, handler.font_handler["Mecha"], interfaceScale);
	Exit.setInteriorColorAllButtons(buttonInteriorColor);
	Exit.setBackgroundOutlineThickness(outlineThickness);
	Exit.setBackgorundOutlineColor(outlineColor);

	Loading.construct(backgroundSize, backgroundForSubmenuExitSize, sf::Vector2f(backgroundForSubMenuPosition.x, backgroundForSubMenuPosition.y + title_size_1),
		sf::Color::Transparent, sf::Color::Black, sf::Vector2f(0, 0), langMan.getText("Loading") + L"...", L"", title_size_1, submenu_size,
		title_or1st_button_position, title_or1st_button_position, button_size, space_between_buttons, bounds_color, handler.font_handler["Mecha"], interfaceScale);

	ApplyChanges.construct(backgroundSize, backgroundForSubmenuApplyChangesSize, backgroundForSubMenuPosition, backgroundForSubMenuColor, backgroundExitColor, sf::Vector2f(0, 0),
		langMan.getText("Do you wish to save changes") + L'?', langMan.getText("Yes") + L',' + langMan.getText("No"), title_size_2, submenu_size, title_or1st_button_position,
		sf::Vector2f(title_or1st_button_position.x, title_or1st_button_position.y + space_between_buttons), button_size, space_between_buttons,
		bounds_color, handler.font_handler["Mecha"], interfaceScale);
	ApplyChanges.setInteriorColorAllButtons(buttonInteriorColor);
	ApplyChanges.setBackgroundOutlineThickness(outlineThickness);
	ApplyChanges.setBackgorundOutlineColor(outlineColor);

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

void AdditionalMenu::runMenu(const sf::Vector2f & mousepos, Input& input, GraphicsOptions& options, GeneralOptions& genOptions)
{
	if (state == AdditionalVisualInformations::NONE && input.isKeyboardEscapeKeyPressed())
		state = AdditionalVisualInformations::EXIT_INFO;
	else if (state == AdditionalVisualInformations::EXIT_INFO && input.isKeyboardEscapeKeyPressed())
		state = AdditionalVisualInformations::NONE;
	
	switch (state)
	{
	case EXIT_INFO: {
		newGamestate = paused;
		if (input.isMouseLeftButtonPressed())
		{
			if (Exit.contains(0, mousepos)) // Resume button
				state = AdditionalVisualInformations::NONE;
			else if (Exit.contains(1, mousepos)) // Return to main menu button
			{
				newGamestate = GameStates::breakAndGoToMenu;
				state = AdditionalVisualInformations::NONE;
			}
			else if (Exit.contains(2, mousepos)) // Quit the game button
			{
				newGamestate = GameStates::Exit;
				state = AdditionalVisualInformations::NONE;
			}
		}
	} break;
	
	case LOADING: {} break;

	case APPLY_CHANGES_GRAPHICS:
	{
		newGamestate = paused;
		if (input.isMouseLeftButtonPressed())
		{
			if (ApplyChanges.contains(0, mousepos)) // Yes button
			{
				state = AdditionalVisualInformations::NONE;
				newGamestate = GameStates::menu;
				options.saveToPreviousOptions();
			}
			else if (ApplyChanges.contains(1, mousepos)) // No button
			{
				state = AdditionalVisualInformations::NONE;
				newGamestate = GameStates::restoreGraphicsOptions;
				options.restorePreviousOptions();
			}
		}
	} break;

	case APPLY_CHANGES_GENERAL:
	{
		newGamestate = paused;
		if (input.isMouseLeftButtonPressed())
		{
			if (ApplyChanges.contains(0, mousepos)) // Yes button
			{
				state = AdditionalVisualInformations::NONE;
				newGamestate = GameStates::menu;
				genOptions.saveToPreviousOptions();
			}
			else if (ApplyChanges.contains(1, mousepos)) // No button
			{
				state = AdditionalVisualInformations::NONE;
				newGamestate = GameStates::restoreGeneralOptions;
				genOptions.restorePreviousOptions();
			}
		}
	} break;

	}

	// Additional menu has highest priority in managing input
	if (state != AdditionalVisualInformations::NONE)
		input.ResetKeys();
}

void AdditionalMenu::updateGamestate(GameStates & gamestate)
{
	if (newGamestate != GameStates::nothing)
		gamestate = newGamestate;
	newGamestate = GameStates::nothing;
}
