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
#include "enumGameState.h"
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
	float interfaceScale = graphicsOpt.getResolution().x / 1920.0f;
	int bar = static_cast<int>(barSize * interfaceScale);
	bool fullyLoad = true, shouldReloadGraphicsOptions = false, shouldReloadGeneralOptions = false, shouldRestoreGeneralOptions = false, menuReset = false;

	std::unique_ptr<LanguageManager> languageManager = nullptr;
	std::unique_ptr<GamePlayerVsAI> gamePlayerVsAI;
	std::unique_ptr<GamePlayers> gamePlayers;
	std::unique_ptr<Menu> mainMenu = nullptr;
	std::unique_ptr<AdditionalMenu> additionalMenu = nullptr;
	std::unique_ptr<Mouse_S> mousePlayer1, mousePlayer2;
	std::shared_ptr<SimpleLogger> logger = std::make_shared<SimpleLogger>(LOGS_FILE_PATH, WARSHIPS_VERSION);

	sf::Vector2i screenDimensions;
	sf::Vector2i standardWindowDimensions;

	sf::View view;
	sf::RenderWindow window;
	window.create(sf::VideoMode(0, 0), "", sf::Style::None);

	sf::Vector2f squareSize;
	sf::RectangleShape rect, rect2, hit, missedShot;
	sf::RectangleShape boardForPlayer1, boardForPlayer2, menuTexture;

	LevelsDifficulty level = LevelsDifficulty::EASY;
	GameStates gameState = GameStates::reloadOptions, drawnGameState = GameStates::menu;
	AdditionalVisualInformations additionalVisualInfo = NONE;


	sf::Clock clock;
	sf::Event event;
	while (window.isOpen())
	{
		// Frame time
		sf::Time dt = clock.restart();
		input.ResetKeys();

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				additionalVisualInfo = EXIT_INFO;
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				input.setKeyboardEscapeKeyPressed();
			if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
				input.setMouseLeftButtonPressed();
			if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Right)
				input.setMouseRightButtonPressed();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::BackSpace)
				input.setKeyboardBackspaceKeyPressed();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return)
				input.setKeyboardReturnKeyPressed();
			if (event.type == sf::Event::TextEntered)
				// only specific ASCII characters
				if (event.text.unicode > 32 && event.text.unicode < 127)
					input.setInputText(static_cast<char>(event.text.unicode));
		}
		if (additionalMenu)
		{
			additionalMenu->runMenu(window.mapPixelToCoords(sf::Mouse::getPosition(window)), input, graphicsOpt, generalOpt);
			additionalMenu->updateAdditionalMenuWithAnimations(dt, window.mapPixelToCoords(sf::Mouse::getPosition(window)));
			additionalMenu->updateGamestate(gameState);
		}

		switch (gameState)
		{
		case GameStates::playerVsAI:
		{
			gamePlayerVsAI->play(dt, window.mapPixelToCoords(sf::Mouse::getPosition(window)), input, *languageManager, gameState);
			drawnGameState = GameStates::playerVsAI;
		}
		break;

		case GameStates::playerVsPlayer:
		{
			gamePlayers->play(dt, window.mapPixelToCoords(sf::Mouse::getPosition(window)), input, *languageManager, gameState);
			drawnGameState = GameStates::playerVsPlayer;
		}
		break;

		case GameStates::loadGameVariables:
		{
			missedShot.setTexture(&textures.texture_handler["X"]);
			hit.setTexture(&textures.texture_handler["fire5"]);
			switch (mapSize)
			{
			case 8:
			{
				boardForPlayer1.setTexture(&textures.texture_handler["mapTexture8x8"]);
				boardForPlayer2.setTexture(&textures.texture_handler["mapTexture8x8"]);
			} break;
			case 10:
			{
				boardForPlayer1.setTexture(&textures.texture_handler["mapTexture10x10"]);
				boardForPlayer2.setTexture(&textures.texture_handler["mapTexture10x10"]);
			} break;
			case 12:
			{
				boardForPlayer1.setTexture(&textures.texture_handler["mapTexture12x12"]);
				boardForPlayer2.setTexture(&textures.texture_handler["mapTexture12x12"]);
			}break;
			}

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
				sf::Vector2f(static_cast<float>(bar), static_cast<float>(screenDimensions.y + bar)), &window);
			mousePlayer2 = std::make_unique<Mouse_S>(sf::Vector2f(0, static_cast<float>(screenDimensions.x)),
				sf::Vector2f(static_cast<float>(bar), static_cast<float>(screenDimensions.y + bar)), &window);

			switch (mainMenu->getChoosedGamemode())
			{
			case playerVsAI:
				gameState = GameStates::loadPlayerVsAI; break;
			case playerVsPlayer:
				gameState = GameStates::loadPlayerVsPlayer; break;
			}

			drawnGameState = GameStates::nothing;
		}
		break;

		case GameStates::loadPlayerVsAI:
		{
			gamePlayerVsAI = std::make_unique<GamePlayerVsAI>(screenDimensions, squareSize, sf::Vector2f(0, static_cast<float>(bar)),
				sf::Vector2f(static_cast<float>(screenDimensions.x), static_cast<float>(bar)),
				missedShot, hit, rect, rect2, *mousePlayer2, *mousePlayer1, sf::Vector2f(200 * interfaceScale, 0), 80 * interfaceScale,
				sf::Vector2f(static_cast<float>(standardWindowDimensions.x), static_cast<float>(standardWindowDimensions.y)),
				sf::Vector2f(static_cast<float>(standardWindowDimensions.x / 2), static_cast<float>(standardWindowDimensions.y / 2)),
				interfaceScale, *languageManager, sf::Vector2f(static_cast<float>(standardWindowDimensions.x), static_cast<float>(standardWindowDimensions.y)), generalOpt, level);
			gamePlayerVsAI->attachLogger(logger);

			additionalVisualInfo = AdditionalVisualInformations::NONE;
			gameState = GameStates::playerVsAI;
			drawnGameState = GameStates::nothing;
		}
		break;

		case GameStates::loadPlayerVsPlayer:
		{
			gamePlayers = std::make_unique<GamePlayers>(screenDimensions, squareSize, sf::Vector2f(0, static_cast<float>(bar)),
				sf::Vector2f(static_cast<float>(screenDimensions.x), static_cast<float>(bar)),
				missedShot, hit, rect, rect2, *mousePlayer2, *mousePlayer1, sf::Vector2f(200 * interfaceScale, 0), 80 * interfaceScale,
				sf::Vector2f(static_cast<float>(standardWindowDimensions.x), static_cast<float>(standardWindowDimensions.y)),
				sf::Vector2f(static_cast<float>(standardWindowDimensions.x / 2), static_cast<float>(standardWindowDimensions.y / 2)),
				interfaceScale, *languageManager, sf::Vector2f(static_cast<float>(standardWindowDimensions.x), static_cast<float>(standardWindowDimensions.y)), generalOpt);
			gamePlayers->attachLogger(logger);

			additionalVisualInfo = AdditionalVisualInformations::NONE;
			gameState = GameStates::playerVsPlayer;
			drawnGameState = GameStates::nothing;
		}
		break;

		case GameStates::menu:
		{
			mainMenu->runMenu(window.mapPixelToCoords(sf::Mouse::getPosition(window)), mapSize, level, input, graphicsOpt, generalOpt);
			mainMenu->updateGamestate(gameState, additionalVisualInfo);
			mainMenu->updateMenuWithAnimates(dt, window.mapPixelToCoords(sf::Mouse::getPosition(window)));
			drawnGameState = GameStates::menu;
		}
		break;

		case GameStates::breakAndGoToMenu:
		{
			mainMenu->Reset();
			gameState = GameStates::menu;
			drawnGameState = GameStates::nothing;
		}
		break;

		case GameStates::reloadOptions:
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
				standardWindowDimensions = sf::Vector2i(desktop.width, desktop.height);
				window.create(desktop, L"Warships", sf::Style::Fullscreen);
				menuTexture.setSize(sf::Vector2f(static_cast<float>(standardWindowDimensions.x), static_cast<float>(standardWindowDimensions.y)));
				window.setPosition(sf::Vector2i(window.getPosition().x, 0));
			}
			else if ((wasResolutionChanged || fullyLoad || wasFullScreenChanged) && !graphicsOpt.isFullScreenEnabled())
			{
				interfaceScale = graphicsOpt.getResolution().x / 1920.0f;
				screenDimensions = sf::Vector2i(graphicsOpt.getResolution().x / 2, graphicsOpt.getResolution().y - bar);
				standardWindowDimensions = sf::Vector2i(graphicsOpt.getResolution());
				window.create(sf::VideoMode(standardWindowDimensions.x, standardWindowDimensions.y), L"Warships", sf::Style::Close);
				menuTexture.setSize(sf::Vector2f(static_cast<float>(standardWindowDimensions.x), static_cast<float>(standardWindowDimensions.y)));
				window.setPosition(sf::Vector2i(window.getPosition().x, 0));
			}

			bar = static_cast<int>(barSize * interfaceScale);
			window.setVerticalSyncEnabled(graphicsOpt.isVerticalSyncEnabled());
			view = window.getDefaultView();
			view.zoom(100.0f / graphicsOpt.getResolutionScale());
			window.setView(view);

			if (wasFullScreenChanged || (wasResolutionChanged && !graphicsOpt.isFullScreenEnabled()) || fullyLoad)
			{
				mainMenu = std::make_unique<Menu>(L"Warships", sf::Vector2f(static_cast<float>(standardWindowDimensions.x / 2), 20 * interfaceScale),
					sf::Vector2f(static_cast<float>(standardWindowDimensions.x / 2), 300 * interfaceScale), 130 * interfaceScale, interfaceScale, graphicsOpt, *languageManager, generalOpt);
				additionalMenu = std::make_unique<AdditionalMenu>(sf::Vector2f(200 * interfaceScale, 0), 80 * interfaceScale,
					sf::Vector2f(static_cast<float>(standardWindowDimensions.x), static_cast<float>(standardWindowDimensions.y)),
					sf::Vector2f(static_cast<float>(standardWindowDimensions.x / 2), static_cast<float>(standardWindowDimensions.y / 2)),
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

			gameState = GameStates::menu;
		}
		break;

		case GameStates::restoreGraphicsOptions:
		{
			fullyLoad = true;
			shouldReloadGraphicsOptions = true;
			gameState = GameStates::reloadOptions;
		}
		break;

		case GameStates::reloadGeneralOptions:
		{
			shouldReloadGeneralOptions = true;
			gameState = GameStates::restoreGraphicsOptions;
		} break;

		case GameStates::restoreGeneralOptions:
		{
			shouldRestoreGeneralOptions = true;
			gameState = GameStates::reloadGeneralOptions;
		} break;

		case GameStates::Exit:
		{
			drawnGameState = GameStates::nothing;
			window.close();
		}
		break;

		case GameStates::paused:
		{
			gameState = drawnGameState;
		}
		break;
		}

		// DRAWING
		switch (drawnGameState)
		{
		case GameStates::playerVsAI:
		{
			window.draw(boardForPlayer2);
			window.draw(boardForPlayer1);

			window.draw(*gamePlayerVsAI);
		}
		break;

		case GameStates::playerVsPlayer:
		{
			window.draw(boardForPlayer2);
			window.draw(boardForPlayer1);

			window.draw(*gamePlayers);
		}
		break;

		case GameStates::menu:
		{
			window.draw(menuTexture);
			if (mainMenu)
				window.draw(*mainMenu);
		}
		break;
		}

		if (additionalMenu)
			window.draw(*additionalMenu);

		window.display();
		window.clear();
	}

	graphicsOpt.saveToFile();
	generalOpt.saveToFile();
	logger->saveToFile();
}
