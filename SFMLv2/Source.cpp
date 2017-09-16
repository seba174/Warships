#include <vld.h>
#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>

#include "FontHandler.h"
#include "TextureHandler.h"
#include "INI_Reader.h"
#include "GraphicsOptions.h"
#include "GeneralOptions.h"
#include "Input.h"
#include "LanguageManager.h"
#include "GamePlayerVsAI.h"
#include "GamePlayers.h"
#include "Menu.h"
#include "AdditionalMenu.h"
#include "Mouse_S.h"
#include "SimpleLogger.h"
#include "enumLevelsDifficulty.h"
#include "enumGamestate.h"
#include "enumAdditionalVisualInformation.h"

#define WARSHIPS_VERSION std::string("0.9")
#define LOGS_FILE_PATH std::string("Logs/logs.ini")
#define CONFIG_FILE_PATH std::string("Config/config.ini")

int main()
{
	FontHandler& fonthandler = FontHandler::getInstance();
	TextureHandler& textures = TextureHandler::getInstance();
	INI_Reader reader(CONFIG_FILE_PATH);
	GraphicsOptions graphicsOpt(reader);
	graphicsOpt.setDesktopResolution(sf::Vector2i(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height));
	GeneralOptions generalOpt(reader);
	Input input;

	int mapSize = 0;
	int barSize = 0;
	int countOfShips = 6;
	float interfaceScale = graphicsOpt.getResolution().x / 1920.0f;
	int bar = static_cast<int>(barSize * interfaceScale);
	bool fullyLoad = true, shouldReloadGraphicsOptions = false, shouldReloadGeneralOptions = false, shouldRestoreGeneralOptions = false, menuReset = false;

	std::unique_ptr<LanguageManager> languageManager = nullptr;
	std::unique_ptr<GamePlayerVsAI> gamePlayerVsAI;
	std::unique_ptr<GamePlayers> gamePlayers;
	std::unique_ptr<Menu> mainMenu = nullptr;
	std::unique_ptr<AdditionalMenu> additionalmenu = nullptr;
	std::unique_ptr<Mouse_S> mousePlayer1, mousePlayer2;
	std::shared_ptr<SimpleLogger> logger = std::make_shared<SimpleLogger>(LOGS_FILE_PATH, WARSHIPS_VERSION);

	sf::Vector2i screenDimensions;
	sf::Vector2i StandardWindowDimensions;

	sf::View view;
	sf::RenderWindow Window;
	Window.create(sf::VideoMode(0, 0), "", sf::Style::None);

	sf::Vector2f squareSize;
	std::vector<std::vector<sf::RectangleShape>> squareTabv2, squareTab2v2;
	sf::RectangleShape **squareTab = nullptr, **squareTab2 = nullptr;	
	sf::RectangleShape rect, rect2, hit, missedShot;   
	sf::RectangleShape boardForPlayer1, boardForPlayer2, menuTexture;

	LevelsDifficulty level = LevelsDifficulty::EASY;
	Gamestates Gamestate = Gamestates::reloadOptions, drawnGamestate = Gamestates::menu;
	AdditionalVisualInformations additionalVisualInfo = NONE;


	sf::Clock clock;
	sf::Event Event;
	while (Window.isOpen())
	{
		// Frame time
		sf::Time dt = clock.restart();
		input.ResetKeys();
		
		while (Window.pollEvent(Event))
		{
			if (Event.type == sf::Event::Closed)
				additionalVisualInfo = EXIT_INFO;
			if (Event.type == sf::Event::KeyPressed && Event.key.code == sf::Keyboard::Escape)
				input.setKeyboardEscapeKeyPressed();
			if (Event.type == sf::Event::MouseButtonPressed && Event.key.code == sf::Mouse::Left)
				input.setMouseLeftButtonPressed();
			if (Event.type == sf::Event::MouseButtonPressed && Event.key.code == sf::Mouse::Right)
				input.setMouseRightButtonPressed();
			if (Event.type == sf::Event::KeyPressed && Event.key.code == sf::Keyboard::BackSpace)
				input.setKeyboardBackspaceKeyPressed();
			if (Event.type == sf::Event::KeyPressed && Event.key.code == sf::Keyboard::Return)
				input.setKeyboardReturnKeyPressed();
			if (Event.type == sf::Event::TextEntered)
				// only specific ASCII characters
				if (Event.text.unicode < 127 && Event.text.unicode > 32)
					input.setInputText(static_cast<char>(Event.text.unicode));
		}
		if (additionalmenu)
		{
			additionalmenu->runMenu(Window.mapPixelToCoords(sf::Mouse::getPosition(Window)), input, graphicsOpt, generalOpt);
			additionalmenu->updateAdditionalMenuWithAnimations(dt, Window.mapPixelToCoords(sf::Mouse::getPosition(Window)));
			additionalmenu->updateGamestate(Gamestate);
		}

		switch (Gamestate)
		{
		case Gamestates::playerVsAI:
		{
			gamePlayerVsAI->play(dt, Window.mapPixelToCoords(sf::Mouse::getPosition(Window)), input, *languageManager, Gamestate);
			drawnGamestate = Gamestates::playerVsAI;
		}
		break;

		case Gamestates::playerVsPlayer:
		{
			gamePlayers->play(dt, Window.mapPixelToCoords(sf::Mouse::getPosition(Window)), input, *languageManager, Gamestate);
			drawnGamestate = Gamestates::playerVsPlayer;
		}
		break;

		case Gamestates::loadGameVariables:
		{
			missedShot.setTexture(&textures.texture_handler["X"]);
			hit.setTexture(&textures.texture_handler["fire5"]);
			boardForPlayer1.setTexture(&textures.texture_handler["nowefalev5"]);
			boardForPlayer2.setTexture(&textures.texture_handler["nowefalev5"]);
			rect.setTexture(&textures.texture_handler["crosshair"]);
			rect2.setTexture(&textures.texture_handler["crosshair"]);

			squareSize = sf::Vector2f(static_cast<float>(screenDimensions.x) / mapSize, static_cast<float>(screenDimensions.y) / mapSize);
			boardForPlayer1.setSize(sf::Vector2f(static_cast<float>(screenDimensions.x), static_cast<float>(screenDimensions.y)));
			boardForPlayer2.setSize(sf::Vector2f(static_cast<float>(screenDimensions.x), static_cast<float>(screenDimensions.y)));
			rect.setSize(squareSize);
			rect2.setSize(squareSize);
			hit.setSize(squareSize);
			missedShot.setSize(squareSize);
		
			rect.setPosition(sf::Vector2f(0, static_cast<float>(bar)));
			rect2.setPosition(sf::Vector2f(static_cast<float>(screenDimensions.x), static_cast<float>(bar)));
			boardForPlayer1.setPosition(sf::Vector2f(0, static_cast<float>(bar)));
			boardForPlayer2.setPosition(sf::Vector2f(static_cast<float>(screenDimensions.x), static_cast<float>(bar)));
			
			missedShot.setFillColor(sf::Color(255, 255, 255, 170));

			mousePlayer1 = std::make_unique<Mouse_S>(sf::Vector2f(static_cast<float>(screenDimensions.x), static_cast<float>(2 * screenDimensions.x)),
				sf::Vector2f(static_cast<float>(bar), static_cast<float>(screenDimensions.y + bar)), &Window);
			mousePlayer2 = std::make_unique<Mouse_S>(sf::Vector2f(0, static_cast<float>(screenDimensions.x)),
				sf::Vector2f(static_cast<float>(bar), static_cast<float>(screenDimensions.y + bar)), &Window);

			squareTab = new sf::RectangleShape*[mapSize];
			squareTab2 = new sf::RectangleShape*[mapSize];
			for (int i = 0; i < mapSize; ++i)
			{
				squareTab[i] = new sf::RectangleShape[mapSize];
				squareTab2[i] = new sf::RectangleShape[mapSize];
			}

			squareTabv2 = std::vector<std::vector<sf::RectangleShape>>(mapSize, std::vector<sf::RectangleShape>(mapSize, sf::RectangleShape()));
			squareTab2v2 = std::vector<std::vector<sf::RectangleShape>>(mapSize, std::vector<sf::RectangleShape>(mapSize, sf::RectangleShape()));

			switch (mainMenu->getChoosedGamemode())
			{
			case playerVsAI:
				Gamestate = Gamestates::loadPlayerVsAI; break;
			case playerVsPlayer:
				Gamestate = Gamestates::loadPlayerVsPlayer; break;
			}

			drawnGamestate = Gamestates::nothing;
		}
		break;

		case Gamestates::loadPlayerVsAI:
		{
			gamePlayerVsAI = std::make_unique<GamePlayerVsAI>(screenDimensions, squareSize, sf::Vector2f(0, static_cast<float>(bar)),
				sf::Vector2f(static_cast<float>(screenDimensions.x), static_cast<float>(bar)),
				missedShot, hit, squareTab, squareTab2, rect, rect2, *mousePlayer2, *mousePlayer1, sf::Vector2f(200 * interfaceScale, 0), 80 * interfaceScale,
				sf::Vector2f(static_cast<float>(StandardWindowDimensions.x), static_cast<float>(StandardWindowDimensions.y)),
				sf::Vector2f(static_cast<float>(StandardWindowDimensions.x / 2), static_cast<float>(StandardWindowDimensions.y / 2)),
				interfaceScale, *languageManager, sf::Vector2f(static_cast<float>(StandardWindowDimensions.x), static_cast<float>(StandardWindowDimensions.y)), generalOpt, level);
			gamePlayerVsAI->attachLogger(logger);

			additionalVisualInfo = AdditionalVisualInformations::NONE;
			Gamestate = Gamestates::playerVsAI;
			drawnGamestate = Gamestates::nothing;
		}
		break;

		case Gamestates::loadPlayerVsPlayer:
		{
			gamePlayers = std::make_unique<GamePlayers>(screenDimensions, squareSize, sf::Vector2f(0, static_cast<float>(bar)),
				sf::Vector2f(static_cast<float>(screenDimensions.x), static_cast<float>(bar)),
				missedShot, hit, squareTab, squareTab2, rect, rect2, *mousePlayer2, *mousePlayer1, sf::Vector2f(200 * interfaceScale, 0), 80 * interfaceScale,
				sf::Vector2f(static_cast<float>(StandardWindowDimensions.x), static_cast<float>(StandardWindowDimensions.y)),
				sf::Vector2f(static_cast<float>(StandardWindowDimensions.x / 2), static_cast<float>(StandardWindowDimensions.y / 2)),
				interfaceScale, *languageManager, sf::Vector2f(static_cast<float>(StandardWindowDimensions.x), static_cast<float>(StandardWindowDimensions.y)), generalOpt);
			gamePlayers->attachLogger(logger);

			additionalVisualInfo = AdditionalVisualInformations::NONE;
			Gamestate = Gamestates::playerVsPlayer;
			drawnGamestate = Gamestates::nothing;
		}
		break;

		case Gamestates::menu:
		{
			mainMenu->runMenu(Window.mapPixelToCoords(sf::Mouse::getPosition(Window)), mapSize, level, input, graphicsOpt, generalOpt);
			mainMenu->updateGamestate(Gamestate, additionalVisualInfo);
			mainMenu->updateMenuWithAnimates(dt, Window.mapPixelToCoords(sf::Mouse::getPosition(Window)));
			drawnGamestate = Gamestates::menu;
		}
		break;

		case Gamestates::breakAndGoToMenu:
		{
			if (squareTab && squareTab2)
				for (int i = 0; i < mapSize; i++)
				{
					delete[]squareTab[i];
					delete[]squareTab2[i];
				}
			delete[]squareTab;
			delete[]squareTab2;
			squareTab = nullptr;
			squareTab2 = nullptr;

			mainMenu->Reset();
			Gamestate = Gamestates::menu;
			drawnGamestate = Gamestates::nothing;
		}
		break;

		case Gamestates::reloadOptions:
		{
			if (fullyLoad || shouldReloadGeneralOptions)
				languageManager = std::make_unique<LanguageManager>(generalOpt.getLanguage());

			bool wasResolutionChanged = graphicsOpt.wasResolutionChanged();
			bool wasFullScreenChanged = graphicsOpt.wasFullScreenChanged();

			TextureHandler::setSmooth(graphicsOpt.isAntialiasingEnabled());

			sf::Vector2f temporaryMenuSize = menuTexture.getSize();
			menuTexture = sf::RectangleShape();
			menuTexture.setSize(temporaryMenuSize);
			switch (generalOpt.getMenuTextureNumber())
			{
			case 0:
				menuTexture.setTexture(&textures.texture_handler["menuTexture0"]); break;
			case 1:
				menuTexture.setTexture(&textures.texture_handler["menuTexture1"]); break;
			case 2:
				menuTexture.setTexture(&textures.texture_handler["menuTexture2"]); break;
			}

			if ((wasFullScreenChanged && graphicsOpt.isFullScreenEnabled()) || (graphicsOpt.isFullScreenEnabled() && fullyLoad))
			{
				sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
				graphicsOpt.setDesktopResolution(sf::Vector2i(desktop.width, desktop.height));
				interfaceScale = desktop.width / 1920.0f;
				screenDimensions = sf::Vector2i(desktop.width / 2, desktop.height - bar);
				StandardWindowDimensions = sf::Vector2i(desktop.width, desktop.height);
				Window.create(desktop, L"Warships", sf::Style::Fullscreen);
				menuTexture.setSize(sf::Vector2f(static_cast<float>(StandardWindowDimensions.x), static_cast<float>(StandardWindowDimensions.y)));
				Window.setPosition(sf::Vector2i(Window.getPosition().x, 0));
			}
			else if ((wasResolutionChanged || fullyLoad || wasFullScreenChanged) && !graphicsOpt.isFullScreenEnabled())
			{
				interfaceScale = graphicsOpt.getResolution().x / 1920.0f;
				screenDimensions = sf::Vector2i(graphicsOpt.getResolution().x / 2 , graphicsOpt.getResolution().y - bar);
				StandardWindowDimensions = sf::Vector2i(graphicsOpt.getResolution());
				Window.create(sf::VideoMode(StandardWindowDimensions.x, StandardWindowDimensions.y), L"Warships", sf::Style::Close);
				menuTexture.setSize(sf::Vector2f(static_cast<float>(StandardWindowDimensions.x), static_cast<float>(StandardWindowDimensions.y)));
				Window.setPosition(sf::Vector2i(Window.getPosition().x, 0));
			}

			bar = static_cast<int>(barSize * interfaceScale);
			Window.setVerticalSyncEnabled(graphicsOpt.isVerticalSyncEnabled());
			view = Window.getDefaultView();
			view.zoom(100.0f / graphicsOpt.getResolutionScale());
			Window.setView(view);

			if (wasFullScreenChanged || (wasResolutionChanged && !graphicsOpt.isFullScreenEnabled()) || fullyLoad)
			{
				mainMenu = std::make_unique<Menu>(L"Warships", sf::Vector2f(static_cast<float>(StandardWindowDimensions.x / 2), 20 * interfaceScale),
					sf::Vector2f(static_cast<float>(StandardWindowDimensions.x / 2), 300 * interfaceScale), 130 * interfaceScale, interfaceScale, graphicsOpt, *languageManager, generalOpt);
				additionalmenu = std::make_unique<AdditionalMenu>(sf::Vector2f(200 * interfaceScale, 0), 80 * interfaceScale,
					sf::Vector2f(static_cast<float>(StandardWindowDimensions.x), static_cast<float>(StandardWindowDimensions.y)),
					sf::Vector2f(static_cast<float>(StandardWindowDimensions.x / 2), static_cast<float>(StandardWindowDimensions.y / 2)),
					additionalVisualInfo, interfaceScale, *languageManager);
			}
			if (!fullyLoad || shouldReloadGraphicsOptions)
			{
				mainMenu->setMenustate(Menustates::OPT_GRAPHICS);
				shouldReloadGraphicsOptions = false;
			}
			if (shouldReloadGeneralOptions)
				mainMenu->setMenustate(Menustates::OPT_GENERAL);
			if (!fullyLoad)
				additionalVisualInfo = AdditionalVisualInformations::APPLY_CHANGES_GRAPHICS;
			if (shouldReloadGeneralOptions && !shouldRestoreGeneralOptions)
				additionalVisualInfo = AdditionalVisualInformations::APPLY_CHANGES_GENERAL;

			shouldRestoreGeneralOptions = false;
			shouldReloadGeneralOptions = false;
			fullyLoad = false;

			Gamestate = Gamestates::menu;
		}
		break;

		case Gamestates::restoreGraphicsOptions:
		{
			fullyLoad = true;
			shouldReloadGraphicsOptions = true;
			Gamestate = Gamestates::reloadOptions;
		}
		break;

		case Gamestates::reloadGeneralOptions:
		{
			shouldReloadGeneralOptions = true;
			Gamestate = Gamestates::restoreGraphicsOptions;
		} break;

		case Gamestates::restoreGeneralOptions:
		{
			shouldRestoreGeneralOptions = true;
			Gamestate = Gamestates::reloadGeneralOptions;
		} break;

		case Gamestates::Exit:
		{
			if (squareTab && squareTab2)
				for (int i = 0; i < mapSize; i++)
				{
					delete[]squareTab[i];
					delete[]squareTab2[i];
				}
			delete[]squareTab;
			delete[]squareTab2;

			drawnGamestate = Gamestates::nothing;
			Window.close();
		}
		break;

		case Gamestates::paused:
		{
			Gamestate = drawnGamestate;
		}
		break;
		}

		// DRAWING
		switch (drawnGamestate)
		{
		case Gamestates::playerVsAI:
		{
			Window.draw(boardForPlayer2);
			Window.draw(boardForPlayer1);

			for (int i = 0; i < mapSize; i++)
				for (int j = 0; j < mapSize; j++)
				{
					Window.draw(squareTab[i][j]);
					Window.draw(squareTab2[i][j]);
				}
			Window.draw(*gamePlayerVsAI);
		}
		break;

		case Gamestates::playerVsPlayer:
		{
			Window.draw(boardForPlayer2);
			Window.draw(boardForPlayer1);

			for (int i = 0; i < mapSize; i++)
				for (int j = 0; j < mapSize; j++)
				{
					Window.draw(squareTab[i][j]);
					Window.draw(squareTab2[i][j]);
				}
			Window.draw(*gamePlayers);
		}
		break;

		case Gamestates::menu:
		{
			Window.draw(menuTexture);
			if (mainMenu)
				Window.draw(*mainMenu);
		}
		break;
		}

		if (additionalmenu)
			Window.draw(*additionalmenu);

		Window.display();
		Window.clear();
	}

	graphicsOpt.saveToFile();
	generalOpt.saveToFile();
	logger->saveToFile();
}
