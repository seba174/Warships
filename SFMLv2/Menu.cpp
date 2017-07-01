#include "Menu.h"


void Menu::draw(sf::RenderTarget & target, sf::RenderStates states) const 
{
	target.draw(MainTitle, states);
	switch (menustate)
	{
	case DEFAULT:
		target.draw(Home, states); break;
	case CHOOSE_GAMETYPE:
		target.draw(ChooseGametype, states); break;
	case CHOOSE_MAPSIZE:
		target.draw(ChooseMapSize, states); break;
	case CHOOSE_AILEVEL:
		target.draw(ChooseAILevel, states); break;
	case OPTIONS:
		target.draw(Options, states); break;
	case OPT_GENERAL:
		target.draw(General, states); break;
	case OPT_GRAPHICS:
		target.draw(Graphics, states); break;
	case OPT_AUDIO:
		target.draw(Audio, states); break;
	}
}

Menu::Menu(const std::string & main_title, const sf::Vector2f & main_title_position, const sf::Vector2f & title_or1st_button_position, int space_between_buttons)
{
	// MainTitle character size
	const int titleCharacterSize = 100;

	// SubMenu titles and character size
	const int submenuCharacterSize = 65;

	// Button size
	//sf::Vector2f button_size(480, 110);
	sf::Vector2f button_size(550, 110);

	// Bounds color
	sf::Color bounds_color = sf::Color::White;

	FontHandler& handler = FontHandler::getInstance();

	menustate = DEFAULT;
	previousMenustate = DEFAULT;
	newVSinfo = AdditionalVisualInformations::NONE;
	newGamestate = MENU;
	newVSinfo = NONE;

	MainTitle.setFont(handler.font_handler["Mecha"]);
	MainTitle.setString(main_title);
	MainTitle.setCharacterSize(titleCharacterSize);
	MainTitle.setPosition(main_title_position.x - MainTitle.getGlobalBounds().width / 2, main_title_position.y);

	Home.construct("", "Play,Options,Credits,Exit", submenuCharacterSize, submenuCharacterSize, title_or1st_button_position, title_or1st_button_position, button_size, 
		space_between_buttons, bounds_color, handler.font_handler["Mecha"]);

	ChooseGametype.construct("", "Solo Game,Player vs Player,Back", submenuCharacterSize, submenuCharacterSize, title_or1st_button_position, title_or1st_button_position,
		button_size, space_between_buttons, bounds_color, handler.font_handler["Mecha"]);

	Options.construct("", "General,Graphics,Sound,Back", submenuCharacterSize, submenuCharacterSize, title_or1st_button_position, title_or1st_button_position,
		button_size, space_between_buttons, bounds_color, handler.font_handler["Mecha"]);

	ChooseMapSize.construct("Choose map size", "10 x 10,20 x 20,40 x 40,Back", submenuCharacterSize, submenuCharacterSize,
		sf::Vector2f(title_or1st_button_position.x, title_or1st_button_position.y - 1.8f*submenuCharacterSize),
		sf::Vector2f(title_or1st_button_position.x, title_or1st_button_position.y + space_between_buttons / 1.5f - submenuCharacterSize),
		button_size, space_between_buttons, bounds_color, handler.font_handler["Mecha"]);

	ChooseAILevel.construct("Choose difficulty level", "Easy,Medium,Hard,Back", submenuCharacterSize, submenuCharacterSize,
		sf::Vector2f(title_or1st_button_position.x, title_or1st_button_position.y - 1.8f*submenuCharacterSize),
		sf::Vector2f(title_or1st_button_position.x, title_or1st_button_position.y + space_between_buttons / 1.5f - submenuCharacterSize),
		button_size, space_between_buttons, bounds_color, handler.font_handler["Mecha"]);

	Graphics.Construct(title_or1st_button_position, space_between_buttons);
	Graphics.addOptionNameWithButton("Resolution", handler.font_handler["Mecha"], 35, sf::Vector2f(800, 100), "1920x1080,1600x900", handler.font_handler["Mecha"], 35);
	Graphics.addOptionNameWithButton("Vertical Sync", handler.font_handler["Mecha"], 35, sf::Vector2f(800, 100), "On,Off", handler.font_handler["Mecha"], 35);
	Graphics.addPushButton("Back", 24, handler.font_handler["Mecha"], sf::Vector2f(200, 45));
	Graphics.addPushButton("Apply changes", 24, handler.font_handler["Mecha"], sf::Vector2f(200, 45));
	Graphics.addPushButton("Load defaults", 24, handler.font_handler["Mecha"], sf::Vector2f(200, 45));
}

void Menu::runMenu(const sf::Vector2f & mousepos, int& mapsize, LevelsDifficulty& level, bool leftButtonPressed)
{
	switch (menustate)
	{
	case DEFAULT: {
		//Home.highlightButtonContaining(mousepos);

		if (leftButtonPressed)
		{
			if (Home.contains(0, mousepos)) // Play button
				menustate = menustates::CHOOSE_GAMETYPE;
			else if (Home.contains(1, mousepos)) // Options button
				menustate = menustates::OPTIONS;
			else if (Home.contains(2, mousepos)) // Credits
				;
			else if (Home.contains(3, mousepos)) // Exit button
				newGamestate = EXIT;
		}
	} break;

	case OPTIONS: {
		previousMenustate = menustates::DEFAULT;
		if (leftButtonPressed)
		{
			if (Home.contains(0, mousepos)) // General button
				menustate = OPT_GENERAL;
			else if (Home.contains(1, mousepos)) // Graphics button
				menustate = OPT_GRAPHICS;
			else if (Home.contains(2, mousepos)) // Sounds button
				menustate = OPT_AUDIO;
			else if (Home.contains(3, mousepos)) // Back button
				menustate = previousMenustate;
		}
	} break;

	case OPT_GRAPHICS: {
		previousMenustate = menustates::OPTIONS;
		if (leftButtonPressed)
		{
			Graphics.clickArrowContaining(mousepos);
			if (Graphics.PushButtonContains(0, mousepos))
				menustate = previousMenustate; // Back button
			if (Graphics.PushButtonContains(1, mousepos))
				; // Apply Changes
			if (Graphics.PushButtonContains(2, mousepos))
				; // Reset Defaults
		}

	} break;
	
	case CHOOSE_GAMETYPE: {
	//	ChooseGametype.highlightButtonContaining(mousepos);
		previousMenustate = menustates::DEFAULT;

		if (leftButtonPressed)
		{
			if (ChooseGametype.contains(0, mousepos)) // Solo Game button
			{
				menustate = menustates::CHOOSE_MAPSIZE;
				previousMenustate = menustates::CHOOSE_GAMETYPE;
				choosedGamemode = Gamestates::PlvsAI;
			}
			else if (ChooseGametype.contains(1, mousepos)) // Player vs Player button
			{
				menustate = menustates::CHOOSE_MAPSIZE;
				previousMenustate = menustates::CHOOSE_GAMETYPE;
				choosedGamemode = Gamestates::PlvsPl;
			}
			else if (ChooseGametype.contains(2, mousepos)) // Back button
				menustate = previousMenustate;
		}
	} break;
	
	case CHOOSE_MAPSIZE: {
	//	ChooseMapSize.highlightButtonContaining(mousepos);
		previousMenustate = menustates::CHOOSE_GAMETYPE;

		if (leftButtonPressed)
		{
			if (ChooseMapSize.contains(0, mousepos)) // 10 x 10 button
			{
				mapsize = 10;
				if (choosedGamemode == Gamestates::PlvsPl)
				{
					newGamestate = Gamestates::loadGameVariables;
					newVSinfo = AdditionalVisualInformations::LOADING;
					menustate = menustates::LOADING_GAME_VARIABLES;
				}
				else
				{
					menustate = menustates::CHOOSE_AILEVEL;
					previousMenustate = menustates::CHOOSE_MAPSIZE;
				}
			}
			else if (ChooseMapSize.contains(1, mousepos)) // 20 x 20 button
			{
				mapsize = 20;

				if (choosedGamemode == Gamestates::PlvsPl)
				{
					newGamestate = Gamestates::loadGameVariables;
					newVSinfo = AdditionalVisualInformations::LOADING;
					menustate = menustates::LOADING_GAME_VARIABLES;
				}
				else
				{
					menustate = menustates::CHOOSE_AILEVEL;
					previousMenustate = menustates::CHOOSE_MAPSIZE;
				}
			}
			else if (ChooseMapSize.contains(2, mousepos)) // 40 x 40 button
			{
				mapsize = 40;

				if (choosedGamemode == Gamestates::PlvsPl)
				{
					newGamestate = Gamestates::loadGameVariables;
					newVSinfo = AdditionalVisualInformations::LOADING;
					menustate = menustates::LOADING_GAME_VARIABLES;
				}
				else
				{
					menustate = menustates::CHOOSE_AILEVEL;
					previousMenustate = menustates::CHOOSE_MAPSIZE;
				}
			}
			else if (ChooseMapSize.contains(3, mousepos)) // Back button
				menustate = previousMenustate;
		}
	} break;

	case CHOOSE_AILEVEL: {
	//	ChooseAILevel.highlightButtonContaining(mousepos);

		if (leftButtonPressed)
		{
			if (ChooseAILevel.contains(0, mousepos)) // Easy button
			{
				level = LevelsDifficulty::EASY;
				newGamestate = Gamestates::loadGameVariables;
				newVSinfo = AdditionalVisualInformations::LOADING;
				menustate = menustates::DEFAULT;
			}
			else if (ChooseAILevel.contains(1, mousepos)) // Medium button
			{
				level = LevelsDifficulty::MEDIUM;
				newGamestate = Gamestates::loadGameVariables;
				newVSinfo = AdditionalVisualInformations::LOADING;
				menustate = menustates::DEFAULT;
			}
			else if (ChooseAILevel.contains(2, mousepos)) // Hard button
			{
				level = LevelsDifficulty::HARD;
				newGamestate = Gamestates::loadGameVariables;
				newVSinfo = AdditionalVisualInformations::LOADING;
				menustate = menustates::DEFAULT;
			}
			else if (ChooseAILevel.contains(3, mousepos)) // Back button
				menustate = previousMenustate;
		}
	} break;

	}
}

void Menu::updateMenu()
{
	Home.updateButtons();
	ChooseAILevel.updateButtons();
	ChooseMapSize.updateButtons();
	ChooseGametype.updateButtons();
	Options.updateButtons();
}

void Menu::updateMenuWithAnimates(const sf::Time & time, const sf::Vector2f& mousepos)
{
	Home.highlightButtonContaining(mousepos);
	ChooseAILevel.highlightButtonContaining(mousepos);
	ChooseMapSize.highlightButtonContaining(mousepos);
	ChooseGametype.highlightButtonContaining(mousepos);
	Options.highlightButtonContaining(mousepos);

	Home.updateButtonsWithAnimations(time);
	ChooseAILevel.updateButtonsWithAnimations(time);
	ChooseMapSize.updateButtonsWithAnimations(time);
	ChooseGametype.updateButtonsWithAnimations(time);
	Options.updateButtonsWithAnimations(time);

	Graphics.highlightButtonContaining(mousepos);
	Graphics.updateWithAnimations(time);
}

void Menu::Reset()
{
	menustate = DEFAULT;
	previousMenustate = DEFAULT;
	newVSinfo = AdditionalVisualInformations::NONE;
	newGamestate = MENU;
	newVSinfo = NONE;
}

Gamestates Menu::getChoosedGamemode()
{
	return choosedGamemode;
}

void Menu::updateGamestate(Gamestates & gamestate, AdditionalVisualInformations & additionalvsinfo)
{
	gamestate = newGamestate;
	if (newVSinfo != AdditionalVisualInformations::NONE)
		additionalvsinfo = newVSinfo;
}
