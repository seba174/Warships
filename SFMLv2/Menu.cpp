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

bool Menu::hasVisibleOptionChanged(const Options & options)
{
	// Numbers of buttons represents current menu and have to be changed when the order of button changes
	return
		((std::to_string(options.getResolution().x) + Options::s_x + std::to_string(options.getResolution().y)) != SubGraphics.getDisplayedOption(0)
			&& options.getResolution()!=options.getDesktopResolution())
		|| options.isVerticalSyncEnabled_string() != SubGraphics.getDisplayedOption(1)
		|| options.isFullScreenEnabled_string() != SubGraphics.getDisplayedOption(2)
		|| std::to_string(options.getResolutionScale()) != SubGraphics.getDisplayedOption(3);
}

Menu::Menu(const std::string & main_title, const sf::Vector2f & main_title_position, const sf::Vector2f & title_or1st_button_position, 
	int space_between_buttons, float interfaceScale, const Options& opt)
{
	// MainTitle character size
	const int titleCharacterSize = 100 * interfaceScale;

	// SubMenu titles and character size
	const int submenuCharacterSize = 65 * interfaceScale;

	// Standard Menu Button size
	sf::Vector2f button_size(550 * interfaceScale, 110 * interfaceScale);

	// Bounds color
	sf::Color bounds_color = sf::Color::White;

	// Whole Option Name with Button size
	sf::Vector2f opt_name_with_button(1000 * interfaceScale, 100 * interfaceScale);

	// Option button in Options size
	sf::Vector2f options_butt_size(312 * interfaceScale, 52 * interfaceScale);

	// PushButton in Options size
	sf::Vector2f push_in_opt_size(230 * interfaceScale, 55 * interfaceScale);

	// Size of character in Options in Option button
	const int options_name_with_button_char = 40 * interfaceScale;

	// Size of character in Options in PushButton
	const int options_push_button_char = 28 * interfaceScale;

	const int space_between_push_buttons = 20 * interfaceScale;

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


	SubGraphics.Construct(title_or1st_button_position, space_between_buttons);

	SubGraphics.addOptionNameWithButton("Resolution", handler.font_handler["Mecha"], options_name_with_button_char,
		opt_name_with_button, AvaliableResolutions::getResolutionString(), handler.font_handler["Mecha"],
		options_name_with_button_char, options_butt_size);
	SubGraphics.addOptionNameWithButton("Vertical Sync", handler.font_handler["Mecha"], options_name_with_button_char,
		opt_name_with_button, Options::s_yes + ',' + Options::s_no, handler.font_handler["Mecha"], 
		options_name_with_button_char, options_butt_size);
	SubGraphics.addOptionNameWithButton("Full Screen", handler.font_handler["Mecha"], options_name_with_button_char,
		opt_name_with_button, Options::s_yes + ',' + Options::s_no, handler.font_handler["Mecha"], 
		options_name_with_button_char, options_butt_size);
	SubGraphics.addOptionNameWithButton("Resolution Scale", handler.font_handler["Mecha"], options_name_with_button_char,
		opt_name_with_button, AvaliableResolutionScales::getScaleString(), handler.font_handler["Mecha"],
		options_name_with_button_char, options_butt_size);

	SubGraphics.addPushButton("Back", options_push_button_char, handler.font_handler["Mecha"], push_in_opt_size);
	SubGraphics.addPushButton("Apply changes", options_push_button_char, handler.font_handler["Mecha"], push_in_opt_size);
	SubGraphics.addPushButton("Load defaults", options_push_button_char, handler.font_handler["Mecha"], push_in_opt_size);
	SubGraphics.setSpaceBetweenPushButtons(space_between_push_buttons);
	
	if (!opt.isFullScreenEnabled())
		SubGraphics.setDisplayedOption(0, std::to_string(opt.getResolution().x) + Options::s_x + std::to_string(opt.getResolution().y));
	else
		SubGraphics.setArrowsBlockAndDisplayedString(0, true, opt.getDesktopResolution_string());

	SubGraphics.setDisplayedOption(1, opt.isVerticalSyncEnabled_string());
	SubGraphics.setDisplayedOption(2, opt.isFullScreenEnabled_string());
	SubGraphics.setDisplayedOption(3, std::to_string(opt.getResolutionScale()));
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

				if (opt.hasAnyOptionChanged())
				{
					newGamestate = RELOAD_GRAPHICS;
				}
			} // Apply Changes

			if (SubGraphics.PushButtonContains(2, mousepos))
			{
				opt.loadDefaults();
				newGamestate = RESTORE_GRAPHICS;
			} // Reset Defaults
		}

		SubGraphics.handleAdditionalRectangleColor(1, hasVisibleOptionChanged(opt), sf::Color(0,0,0,127));
		SubGraphics.setArrowsBlockAndDisplayedString(0, opt.isFullScreenEnabled(), opt.getDesktopResolution_string());

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
	newGamestate = MENU;
}
