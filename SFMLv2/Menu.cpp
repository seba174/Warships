#include "Menu.h"


void Menu::draw(sf::RenderTarget & target, sf::RenderStates states) const 
{
	target.draw(MainTitle, states);
	switch (menustate)
	{
	case DEFAULT:
		target.draw(SubHome, states); break;
	case CHOOSE_GAMETYPE:
		target.draw(SubChooseGametype, states); break;
	case CHOOSE_MAPSIZE:
		target.draw(SubChooseMapSize, states); break;
	case CHOOSE_AILEVEL:
		target.draw(SubChooseAILevel, states); break;
	case OPTIONS:
		target.draw(SubOptions, states); break;
	case OPT_GENERAL:
		target.draw(SubGeneral, states); break;
	case OPT_GRAPHICS:
		target.draw(SubGraphics, states); break;
	case OPT_AUDIO:
		target.draw(SubAudio, states); break;
	}
}

Menu::Menu(const std::string & main_title, const sf::Vector2f & main_title_position, const sf::Vector2f & title_or1st_button_position, 
	int space_between_buttons, float interfaceScale)
{
	// MainTitle character size
	const int titleCharacterSize = 100*interfaceScale;

	// SubMenu titles and character size
	const int submenuCharacterSize = 65*interfaceScale;

	// Button size
	//sf::Vector2f button_size(480, 110);
	sf::Vector2f button_size(550*interfaceScale, 110*interfaceScale);

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

	SubHome.construct("", "Play,Options,Credits,Exit", submenuCharacterSize, submenuCharacterSize, title_or1st_button_position, title_or1st_button_position, button_size, 
		space_between_buttons, bounds_color, handler.font_handler["Mecha"]);

	SubChooseGametype.construct("", "Solo Game,Player vs Player,Back", submenuCharacterSize, submenuCharacterSize, title_or1st_button_position, title_or1st_button_position,
		button_size, space_between_buttons, bounds_color, handler.font_handler["Mecha"]);

	SubOptions.construct("", "General,Graphics,Sound,Back", submenuCharacterSize, submenuCharacterSize, title_or1st_button_position, title_or1st_button_position,
		button_size, space_between_buttons, bounds_color, handler.font_handler["Mecha"]);

	SubChooseMapSize.construct("Choose map size", "10 x 10,20 x 20,40 x 40,Back", submenuCharacterSize, submenuCharacterSize,
		sf::Vector2f(title_or1st_button_position.x, title_or1st_button_position.y - 1.8f*submenuCharacterSize),
		sf::Vector2f(title_or1st_button_position.x, title_or1st_button_position.y + space_between_buttons / 1.5f - submenuCharacterSize),
		button_size, space_between_buttons, bounds_color, handler.font_handler["Mecha"]);

	SubChooseAILevel.construct("Choose difficulty level", "Easy,Medium,Hard,Back", submenuCharacterSize, submenuCharacterSize,
		sf::Vector2f(title_or1st_button_position.x, title_or1st_button_position.y - 1.8f*submenuCharacterSize),
		sf::Vector2f(title_or1st_button_position.x, title_or1st_button_position.y + space_between_buttons / 1.5f - submenuCharacterSize),
		button_size, space_between_buttons, bounds_color, handler.font_handler["Mecha"]);

	//!!!!!!!
	//!!!!!!!
	// zmienic zeby dzialalo z interfacescale
	SubGraphics.Construct(title_or1st_button_position, space_between_buttons);

	std::string res;
	for (auto it = AvaliableResolutions::avaliableRes.begin(); it != AvaliableResolutions::avaliableRes.end(); ++it)
	{
		res += it->resolution_text;
		if ((++it) == AvaliableResolutions::avaliableRes.end());
		else
		{
			res += ',';
		}
		--it;
	}
	SubGraphics.addOptionNameWithButton("Resolution", handler.font_handler["Mecha"], 35, sf::Vector2f(800, 100), res, handler.font_handler["Mecha"], 35);
	SubGraphics.addOptionNameWithButton("Vertical Sync", handler.font_handler["Mecha"], 35, sf::Vector2f(800, 100), "On,Off", handler.font_handler["Mecha"], 35);
	SubGraphics.addPushButton("Back", 24, handler.font_handler["Mecha"], sf::Vector2f(200, 45));
	SubGraphics.addPushButton("Apply changes", 24, handler.font_handler["Mecha"], sf::Vector2f(200, 45));
	SubGraphics.addPushButton("Load defaults", 24, handler.font_handler["Mecha"], sf::Vector2f(200, 45));
}

void Menu::runMenu(const sf::Vector2f & mousepos, int& mapsize, LevelsDifficulty& level, bool leftButtonPressed, Options& opt)
{
	switch (menustate)
	{
	case DEFAULT: {
		//Home.highlightButtonContaining(mousepos);

		if (leftButtonPressed)
		{
			if (SubHome.contains(0, mousepos)) // Play button
				menustate = Menustates::CHOOSE_GAMETYPE;
			else if (SubHome.contains(1, mousepos)) // Options button
				menustate = Menustates::OPTIONS;
			else if (SubHome.contains(2, mousepos)) // Credits
				;
			else if (SubHome.contains(3, mousepos)) // Exit button
				newGamestate = EXIT;
		}
	} break;

	case OPTIONS: {
		previousMenustate = Menustates::DEFAULT;
		if (leftButtonPressed)
		{
			if (SubHome.contains(0, mousepos)) // General button
				menustate = OPT_GENERAL;
			else if (SubHome.contains(1, mousepos)) // Graphics button
				menustate = OPT_GRAPHICS;
			else if (SubHome.contains(2, mousepos)) // Sounds button
				menustate = OPT_AUDIO;
			else if (SubHome.contains(3, mousepos)) // Back button
				menustate = previousMenustate;
		}
	} break;

	case OPT_GRAPHICS: {
		previousMenustate = Menustates::OPTIONS;
		if (leftButtonPressed)
		{
			SubGraphics.clickArrowContaining(mousepos);
			if (SubGraphics.PushButtonContains(0, mousepos))
				menustate = previousMenustate; // Back button
			
			// 0- Resolution, 1- VerticalSync, 2-Fullscreen, 3-ResolutionScale
			if (SubGraphics.PushButtonContains(1, mousepos))
			{
				opt.setResolution(SubGraphics.getDisplayedOption(0));
				opt.setVerticalSyncEnabled(SubGraphics.getDisplayedOption(1));
				opt.setFullScreen(SubGraphics.getDisplayedOption(2));
				opt.setResolutionScale(SubGraphics.getDisplayedOption(3));

				newGamestate = RELOAD_GRAPHICS;
			} // Apply Changes

			if (SubGraphics.PushButtonContains(2, mousepos))
				; // Reset Defaults
		}

	} break;
	
	case CHOOSE_GAMETYPE: {
	//	ChooseGametype.highlightButtonContaining(mousepos);
		previousMenustate = Menustates::DEFAULT;

		if (leftButtonPressed)
		{
			if (SubChooseGametype.contains(0, mousepos)) // Solo Game button
			{
				menustate = Menustates::CHOOSE_MAPSIZE;
				previousMenustate = Menustates::CHOOSE_GAMETYPE;
				choosedGamemode = Gamestates::PlvsAI;
			}
			else if (SubChooseGametype.contains(1, mousepos)) // Player vs Player button
			{
				menustate = Menustates::CHOOSE_MAPSIZE;
				previousMenustate = Menustates::CHOOSE_GAMETYPE;
				choosedGamemode = Gamestates::PlvsPl;
			}
			else if (SubChooseGametype.contains(2, mousepos)) // Back button
				menustate = previousMenustate;
		}
	} break;
	
	case CHOOSE_MAPSIZE: {
	//	ChooseMapSize.highlightButtonContaining(mousepos);
		previousMenustate = Menustates::CHOOSE_GAMETYPE;

		if (leftButtonPressed)
		{
			if (SubChooseMapSize.contains(0, mousepos)) // 10 x 10 button
			{
				mapsize = 10;
				if (choosedGamemode == Gamestates::PlvsPl)
				{
					newGamestate = Gamestates::loadGameVariables;
					newVSinfo = AdditionalVisualInformations::LOADING;
					menustate = Menustates::LOADING_GAME_VARIABLES;
				}
				else
				{
					menustate = Menustates::CHOOSE_AILEVEL;
					previousMenustate = Menustates::CHOOSE_MAPSIZE;
				}
			}
			else if (SubChooseMapSize.contains(1, mousepos)) // 20 x 20 button
			{
				mapsize = 20;

				if (choosedGamemode == Gamestates::PlvsPl)
				{
					newGamestate = Gamestates::loadGameVariables;
					newVSinfo = AdditionalVisualInformations::LOADING;
					menustate = Menustates::LOADING_GAME_VARIABLES;
				}
				else
				{
					menustate = Menustates::CHOOSE_AILEVEL;
					previousMenustate = Menustates::CHOOSE_MAPSIZE;
				}
			}
			else if (SubChooseMapSize.contains(2, mousepos)) // 40 x 40 button
			{
				mapsize = 40;

				if (choosedGamemode == Gamestates::PlvsPl)
				{
					newGamestate = Gamestates::loadGameVariables;
					newVSinfo = AdditionalVisualInformations::LOADING;
					menustate = Menustates::LOADING_GAME_VARIABLES;
				}
				else
				{
					menustate = Menustates::CHOOSE_AILEVEL;
					previousMenustate = Menustates::CHOOSE_MAPSIZE;
				}
			}
			else if (SubChooseMapSize.contains(3, mousepos)) // Back button
				menustate = previousMenustate;
		}
	} break;

	case CHOOSE_AILEVEL: {
	//	ChooseAILevel.highlightButtonContaining(mousepos);

		if (leftButtonPressed)
		{
			if (SubChooseAILevel.contains(0, mousepos)) // Easy button
			{
				level = LevelsDifficulty::EASY;
				newGamestate = Gamestates::loadGameVariables;
				newVSinfo = AdditionalVisualInformations::LOADING;
				menustate = Menustates::DEFAULT;
			}
			else if (SubChooseAILevel.contains(1, mousepos)) // Medium button
			{
				level = LevelsDifficulty::MEDIUM;
				newGamestate = Gamestates::loadGameVariables;
				newVSinfo = AdditionalVisualInformations::LOADING;
				menustate = Menustates::DEFAULT;
			}
			else if (SubChooseAILevel.contains(2, mousepos)) // Hard button
			{
				level = LevelsDifficulty::HARD;
				newGamestate = Gamestates::loadGameVariables;
				newVSinfo = AdditionalVisualInformations::LOADING;
				menustate = Menustates::DEFAULT;
			}
			else if (SubChooseAILevel.contains(3, mousepos)) // Back button
				menustate = previousMenustate;
		}
	} break;

	}
}

void Menu::updateMenu()
{
	SubHome.updateButtons();
	SubChooseAILevel.updateButtons();
	SubChooseMapSize.updateButtons();
	SubChooseGametype.updateButtons();
	SubOptions.updateButtons();
}

void Menu::updateMenuWithAnimates(const sf::Time & time, const sf::Vector2f& mousepos)
{
	SubHome.highlightButtonContaining(mousepos);
	SubChooseAILevel.highlightButtonContaining(mousepos);
	SubChooseMapSize.highlightButtonContaining(mousepos);
	SubChooseGametype.highlightButtonContaining(mousepos);
	SubOptions.highlightButtonContaining(mousepos);

	SubHome.updateButtonsWithAnimations(time);
	SubChooseAILevel.updateButtonsWithAnimations(time);
	SubChooseMapSize.updateButtonsWithAnimations(time);
	SubChooseGametype.updateButtonsWithAnimations(time);
	SubOptions.updateButtonsWithAnimations(time);

	SubGraphics.highlightButtonContaining(mousepos);
	SubGraphics.updateWithAnimations(time);
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
