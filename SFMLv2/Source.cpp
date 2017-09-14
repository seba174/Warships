#include <vld.h>
#include <iostream>
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Ships.h"
#include "Mouse_S.h"
#include "IrregularShip2.h"
#include "IrregularShip3.h"
#include "AI.h"
#include "Game.h"
#include "Player.h"
#include "TextureHandler.h"
#include "FontHandler.h"
#include "enumGamestate.h"
#include "enumLevelsDifficulty.h"
#include "enumAdditionalVisualInformation.h"
#include "Menu.h"
#include "AdditionalMenu.h"
#include "OptionButton.h"
#include "Input.h"

#include "INI_Reader.h"
#include "OptionNameWithButton.h"
#include "OptionsSubMenu.h"
#include "GraphicsOptions.h"
#include "GamePlayers.h"
#include "DestroyedShips.h"
#include "DestroyedShipsWithBackground.h"
#include "LanguageManager.h"
#include "GeneralOptions.h"
#include "FinishStars.h"


int main()
{
	INI_Reader reader("Config/config.ini");
	GraphicsOptions graphicsOpt(reader);
	graphicsOpt.setDesktopResolution(sf::Vector2i(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height));
	GeneralOptions generalOpt(reader);
	std::unique_ptr<LanguageManager> languageManager = nullptr;

	int map_size = 0;
	int barSize = 3;
	const int line_thicknessSize = 10;
	float interfaceScale = graphicsOpt.getResolution().x / 1920.0f;

	int bar = static_cast<int>(barSize * interfaceScale);
	int line_thickness = static_cast<int>(line_thicknessSize * interfaceScale);

	FontHandler& fonthandler = FontHandler::getInstance();
	TextureHandler& textures = TextureHandler::getInstance();

	sf::RectangleShape bImage, bImage2, menuTexture;
	bImage.setTexture(&textures.texture_handler["nowefalev5"]);
	bImage2.setTexture(&textures.texture_handler["nowefalev5"]);

	std::vector<Board*> vect_ship_to_draw;

	sf::Vector2i screenDimensions;
	sf::Vector2i StandardWindowDimensions;

	sf::RenderWindow Window;
	Window.create(sf::VideoMode(0, 0), "", sf::Style::None);

	sf::View view;

	// PASEK MIEDZY PLANSZAMI
	sf::ConvexShape line(4);
	sf::Vector2f square_size;

	sf::RectangleShape **square_tab = nullptr, **square_tab_2 = nullptr;	// tablice kwadratow do rysowania
	sf::RectangleShape rect, rect2, trafienie, pudlo;     // kwadraty pudla, trafienia, i kwadratu do przesuwania

	pudlo.setTexture(&textures.texture_handler["X"]);
	trafienie.setTexture(&textures.texture_handler["fire5"]);

	sf::Clock clock;	// czas klatki

	Input input;
	std::unique_ptr<Mouse_S> mouse, mouse_pl;

	// TABLICA STATKOW DO STAWIANIA PRZEZ GRACZA

	int count_of_ships = 6;
	Board** AI_set_ships = nullptr;
	bool AI_set = false;

	LevelsDifficulty level = LevelsDifficulty::EASY;
	Gamestates Gamestate = RELOAD_GRAPHICS, drawnGamestate = MENU;
	AdditionalVisualInformations additional_vs_info = NONE;

	std::unique_ptr<Game> game;
	std::unique_ptr<GamePlayers> gamePlayers;

	std::unique_ptr<Menu> MainMenu = nullptr;
	std::unique_ptr<AdditionalMenu> Additionalmenu = nullptr;

	bool menureset = false;

	sf::Event Event;
	while (Window.isOpen())
	{
		sf::Time dt = clock.restart();		// czas klatki
		input.ResetKeys();
		static bool first = true, reloaded = false, reloadGeneral = false, restoredGeneral = false;

		while (Window.pollEvent(Event))
		{
			if (Event.type == sf::Event::Closed)
				additional_vs_info = EXIT_INFO;
			if (Event.type == sf::Event::KeyPressed && Event.key.code == sf::Keyboard::Escape)
			{
				input.setKeyboardEscapeKeyPressed();
				//additional_vs_info = EXIT_INFO;
			}
			if (Event.type == sf::Event::MouseButtonPressed && Event.key.code == sf::Mouse::Left)
				input.setMouseLeftButtonPressed();
			if (Event.type == sf::Event::MouseButtonPressed && Event.key.code == sf::Mouse::Right)
				input.setMouseRightButtonPressed();
			if (Event.type == sf::Event::KeyPressed && Event.key.code == sf::Keyboard::BackSpace)
				input.setKeyboardBackspaceKeyPressed();
			if (Event.type == sf::Event::KeyPressed && Event.key.code == sf::Keyboard::Return)
				input.setKeyboardReturnKeyPressed();
			if (Event.type == sf::Event::TextEntered)
				if (Event.text.unicode < 127 && Event.text.unicode > 32)
					input.setInputText(static_cast<char>(Event.text.unicode));
		}
		if (Additionalmenu)
		{
			Additionalmenu->runMenu(Window.mapPixelToCoords(sf::Mouse::getPosition(Window)), input, graphicsOpt, generalOpt);
			Additionalmenu->updateAdditionalMenuWithAnimations(dt, Window.mapPixelToCoords(sf::Mouse::getPosition(Window)));
			Additionalmenu->updateGamestate(Gamestate);
		}

		// Handling 
		switch (Gamestate)
		{
		case PlvsAI:
		{
			if (input.isMouseLeftButtonPressed() && mouse->isMouseWithinArea() && !game->get_ships_set_up())
				game->set_player_placeships();

			if (input.isMouseRightButtonPressed() && mouse->isMouseWithinArea() && !game->get_ships_set_up())
				game->rotate_player_ship();

			if (input.isMouseLeftButtonPressed() && AI_set)
				game->setplmoved() = true;

			if (!game->get_ships_set_up())
			{
				if (mouse->isMouseWithinArea())
					game->Player_set_ships(mouse->returnPositionInBounds(), vect_ship_to_draw);
			}
			else if (!AI_set)
			{
				game->place_ships(vect_ship_to_draw, AI_set_ships, count_of_ships);
				AI_set = true;
			}
			else
			{
				sf::Vector2i tmp_vec(static_cast<int>(round(rect.getPosition().x / square_size.x)), static_cast<int>(round((rect.getPosition().y - bar) / square_size.y)));
				game->play(dt, tmp_vec, mouse_pl->returnPositionInBounds());
				if (game->getGameState() == AI_win)
				{
					additional_vs_info = AdditionalVisualInformations::AI_WON;
				}
				else if (game->getGameState() == Player_win)
				{
					additional_vs_info = AdditionalVisualInformations::PLAYER_WON;
				}
			}
			drawnGamestate = PlvsAI;
		}
		break;

		case loadGameVariables:
		{
			bImage.setSize(sf::Vector2f(static_cast<float>(screenDimensions.x), static_cast<float>(screenDimensions.y)));
			bImage2.setSize(sf::Vector2f(static_cast<float>(screenDimensions.x), static_cast<float>(screenDimensions.y)));

			square_size = sf::Vector2f(static_cast<float>(screenDimensions.x) / map_size, static_cast<float>(screenDimensions.y) / map_size); // rozmiar 1 kwadratu mapy)

			rect.setSize(square_size);
			rect2.setSize(square_size);
			rect.setTexture(&textures.texture_handler["crosshair"]);
			rect2.setTexture(&textures.texture_handler["crosshair"]);

			trafienie.setSize(square_size);
			pudlo.setSize(square_size);

			rect.setPosition(sf::Vector2f(0, static_cast<float>(bar)));
			rect2.setPosition(sf::Vector2f(static_cast<float>(screenDimensions.x + line_thickness), static_cast<float>(bar)));
			pudlo.setFillColor(sf::Color(255, 255, 255, 170));

			line.setPoint(0, sf::Vector2f(static_cast<float>(screenDimensions.x), 0));
			line.setPoint(1, sf::Vector2f(static_cast<float>(screenDimensions.x), static_cast<float>(screenDimensions.y + bar)));
			line.setPoint(2, sf::Vector2f(static_cast<float>(screenDimensions.x + line_thickness), static_cast<float>(screenDimensions.y + bar)));
			line.setPoint(3, sf::Vector2f(static_cast<float>(screenDimensions.x + line_thickness), 0));
			line.setOutlineColor(sf::Color::Red);

			bImage.setPosition(sf::Vector2f(0, static_cast<float>(bar)));
			bImage2.setPosition(sf::Vector2f(static_cast<float>(screenDimensions.x + line_thickness), static_cast<float>(bar)));

			mouse = std::make_unique<Mouse_S>(sf::Vector2f(static_cast<float>(screenDimensions.x + line_thickness), static_cast<float>(2 * screenDimensions.x + line_thickness)),
				sf::Vector2f(static_cast<float>(bar), static_cast<float>(screenDimensions.y + bar)), &Window);
			mouse_pl = std::make_unique<Mouse_S>(sf::Vector2f(0, static_cast<float>(screenDimensions.x)),
				sf::Vector2f(static_cast<float>(bar), static_cast<float>(screenDimensions.y + bar)), &Window);

			square_tab = new sf::RectangleShape*[map_size];
			square_tab_2 = new sf::RectangleShape*[map_size];

			for (int i = 0; i < map_size; i++)
			{
				square_tab[i] = new sf::RectangleShape[map_size];
				square_tab_2[i] = new sf::RectangleShape[map_size];
			}

			drawnGamestate = Gamestates::NOTHING;

			switch (MainMenu->getChoosedGamemode())
			{
			case PlvsAI:
				Gamestate = loadPlvsAI; break;
			case PlvsPl:
				Gamestate = loadPlvsPl; break;
			}

		}
		break;

		case loadPlvsAI:
		{
			AI_set_ships = new Board*[count_of_ships];
			AI_set_ships[0] = new Ships(5, square_size, screenDimensions, sf::Vector2f(0, static_cast<float>(bar)), &textures.texture_handler["big_body_final"]);
			AI_set_ships[1] = new Ships(4, square_size, screenDimensions, sf::Vector2f(0, static_cast<float>(bar)), &textures.texture_handler["big_body_final"]);
			AI_set_ships[2] = new Ships(3, square_size, screenDimensions, sf::Vector2f(0, static_cast<float>(bar)), &textures.texture_handler["big_body_final"]);
			AI_set_ships[3] = new Ships(2, square_size, screenDimensions, sf::Vector2f(0, static_cast<float>(bar)), &textures.texture_handler["big_body_final"]);
			AI_set_ships[4] = new IrregularShip2(square_size, screenDimensions, sf::Vector2f(0, static_cast<float>(bar)), &textures.texture_handler["irregular2"]);
			AI_set_ships[5] = new IrregularShip3(square_size, screenDimensions, sf::Vector2f(0, static_cast<float>(bar)), &textures.texture_handler["irregular3"]);

			game = std::make_unique<Game>(screenDimensions, square_size, sf::Vector2f(0, static_cast<float>(bar)),
				sf::Vector2f(static_cast<float>(screenDimensions.x + line_thickness), static_cast<float>(bar)),
				pudlo, trafienie, square_tab, square_tab_2, rect, level);

			additional_vs_info = AdditionalVisualInformations::NONE;
			Gamestate = PlvsAI;
			drawnGamestate = Gamestates::NOTHING;
		}
		break;

		case loadPlvsPl:
		{
			gamePlayers = std::make_unique<GamePlayers>(screenDimensions, square_size, sf::Vector2f(0, static_cast<float>(bar)),
				sf::Vector2f(static_cast<float>(screenDimensions.x + line_thickness), static_cast<float>(bar)),
				pudlo, trafienie, square_tab, square_tab_2, rect, rect2, *mouse_pl, *mouse, sf::Vector2f(200 * interfaceScale, 0), 80 * interfaceScale,
				sf::Vector2f(static_cast<float>(StandardWindowDimensions.x), static_cast<float>(StandardWindowDimensions.y)),
				sf::Vector2f(static_cast<float>(StandardWindowDimensions.x / 2), static_cast<float>(StandardWindowDimensions.y / 2)),
				interfaceScale, *languageManager, sf::Vector2f(static_cast<float>(StandardWindowDimensions.x), static_cast<float>(StandardWindowDimensions.y)), generalOpt);

			additional_vs_info = AdditionalVisualInformations::NONE;
			Gamestate = PlvsPl;
			drawnGamestate = Gamestates::NOTHING;
		}
		break;

		case PlvsPl:
		{
			gamePlayers->play(dt, Window.mapPixelToCoords(sf::Mouse::getPosition(Window)), input, *languageManager, Gamestate);
			drawnGamestate = PlvsPl;
		}
		break;

		case MENU:
		{
			MainMenu->runMenu(Window.mapPixelToCoords(sf::Mouse::getPosition(Window)), map_size, level, input, graphicsOpt, generalOpt);
			MainMenu->updateGamestate(Gamestate, additional_vs_info);
			MainMenu->updateMenuWithAnimates(dt, Window.mapPixelToCoords(sf::Mouse::getPosition(Window)));
			drawnGamestate = MENU;
		}
		break;

		case BREAK_AND_GO_TO_MENU:
		{
			AI_set = false;
			vect_ship_to_draw.clear();

			if (AI_set_ships)
				for (int i = 0; i < count_of_ships; i++)
				{
					delete AI_set_ships[i];
				}
			delete[] AI_set_ships;
			AI_set_ships = nullptr;

			if (square_tab && square_tab_2)
				for (int i = 0; i < map_size; i++)
				{
					delete[]square_tab[i];
					delete[]square_tab_2[i];
				}
			delete[]square_tab;
			delete[]square_tab_2;
			square_tab = nullptr;
			square_tab_2 = nullptr;

			MainMenu->Reset();
			Gamestate = MENU;
			drawnGamestate = Gamestates::NOTHING;
		}
		break;

		case RELOAD_GRAPHICS:
		{
			if (first || reloadGeneral)
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

			if ((wasFullScreenChanged && graphicsOpt.isFullScreenEnabled()) || (graphicsOpt.isFullScreenEnabled() && first))
			{
				sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
				graphicsOpt.setDesktopResolution(sf::Vector2i(desktop.width, desktop.height));
				interfaceScale = desktop.width / 1920.0f;
				screenDimensions = sf::Vector2i(desktop.width / 2 - line_thickness / 2, desktop.height - bar);
				StandardWindowDimensions = sf::Vector2i(desktop.width, desktop.height);
				Window.create(desktop, L"Warships", sf::Style::Fullscreen);
				//test
				menuTexture.setSize(sf::Vector2f(static_cast<float>(StandardWindowDimensions.x), static_cast<float>(StandardWindowDimensions.y)));
				Window.setPosition(sf::Vector2i(Window.getPosition().x, 0));
			}
			else if ((wasResolutionChanged || first || wasFullScreenChanged) && !graphicsOpt.isFullScreenEnabled())
			{
				interfaceScale = graphicsOpt.getResolution().x / 1920.0f;
				screenDimensions = sf::Vector2i(graphicsOpt.getResolution().x / 2 - line_thickness / 2, graphicsOpt.getResolution().y - bar);
				StandardWindowDimensions = sf::Vector2i(graphicsOpt.getResolution());
				Window.create(sf::VideoMode(StandardWindowDimensions.x, StandardWindowDimensions.y), L"Warships", sf::Style::Close);
				//test
				menuTexture.setSize(sf::Vector2f(static_cast<float>(StandardWindowDimensions.x), static_cast<float>(StandardWindowDimensions.y)));
				Window.setPosition(sf::Vector2i(Window.getPosition().x, 0));
			}

			bar = static_cast<int>(barSize * interfaceScale);
			line_thickness = static_cast<int>(line_thicknessSize * interfaceScale);

			Window.setVerticalSyncEnabled(graphicsOpt.isVerticalSyncEnabled());

			view = Window.getDefaultView();
			view.zoom(100.0f / graphicsOpt.getResolutionScale());
			Window.setView(view);

			if (wasFullScreenChanged || (wasResolutionChanged && !graphicsOpt.isFullScreenEnabled()) || first)
			{
				MainMenu = std::make_unique<Menu>(L"Warships", sf::Vector2f(static_cast<float>(StandardWindowDimensions.x / 2), 20 * interfaceScale),
					sf::Vector2f(static_cast<float>(StandardWindowDimensions.x / 2), 300 * interfaceScale), 130 * interfaceScale, interfaceScale, graphicsOpt, *languageManager, generalOpt);
				Additionalmenu = std::make_unique<AdditionalMenu>(sf::Vector2f(200 * interfaceScale, 0), 80 * interfaceScale,
					sf::Vector2f(static_cast<float>(StandardWindowDimensions.x), static_cast<float>(StandardWindowDimensions.y)),
					sf::Vector2f(static_cast<float>(StandardWindowDimensions.x / 2), static_cast<float>(StandardWindowDimensions.y / 2)),
					additional_vs_info, interfaceScale, *languageManager);
			}
			if (!first || reloaded)
			{
				MainMenu->setMenustate(Menustates::OPT_GRAPHICS);
				reloaded = false;
			}
			if (reloadGeneral)
				MainMenu->setMenustate(Menustates::OPT_GENERAL);

			Gamestate = MENU;
			if (!first)
				additional_vs_info = AdditionalVisualInformations::APPLY_CHANGES_GRAPHICS;

			if (reloadGeneral && !restoredGeneral)
			{
				additional_vs_info = AdditionalVisualInformations::APPLY_CHANGES_GENERAL;
			}

			restoredGeneral = false;
			reloadGeneral = false;
			first = false;
		}
		break;

		case RESTORE_GRAPHICS:
		{
			first = true;
			reloaded = true;
			Gamestate = RELOAD_GRAPHICS;
		}
		break;

		case RELOAD_GENERAL:
		{
			reloadGeneral = true;
			Gamestate = RESTORE_GRAPHICS;
		} break;

		case RESTORE_GENERAL:
		{
			restoredGeneral = true;
			Gamestate = RELOAD_GENERAL;
		} break;

		case EXIT:
		{
			if (AI_set_ships)
				for (int i = 0; i < count_of_ships; i++)
				{
					delete[]AI_set_ships[i];
				}
			delete AI_set_ships;

			if (square_tab && square_tab_2)
				for (int i = 0; i < map_size; i++)
				{
					delete[]square_tab[i];
					delete[]square_tab_2[i];
				}
			delete[]square_tab;
			delete[]square_tab_2;

			drawnGamestate = Gamestates::NOTHING;
			Window.close();
		}
		break;

		case PAUSED:
		{
			Gamestate = drawnGamestate;
		}
		break;
		}

		// DRAWING
		switch (drawnGamestate)
		{
		case PlvsAI:
		{
			Window.draw(bImage2);
			Window.draw(line);
			Window.draw(bImage);

			if (!AI_set)
			{
				for (auto it = vect_ship_to_draw.begin(); it != vect_ship_to_draw.end(); it++)
				{
					(*it)->updateTexture(dt);
					Window.draw((*it)->return_ship());
				}
			}
			else
			{
				for (auto it = vect_ship_to_draw.begin(); it != vect_ship_to_draw.end() - 6; it++)
				{
					(*it)->updateTexture(dt);
					Window.draw((*it)->return_ship());
				}
			}

			for (int i = 0; i < map_size; i++)
				for (int j = 0; j < map_size; j++)
				{
					Window.draw(square_tab[i][j]);
					Window.draw(square_tab_2[i][j]);
				}
			game->Draw(Window);
		}
		break;

		case PlvsPl:
		{
			Window.draw(bImage2);
			Window.draw(line);
			Window.draw(bImage);

			for (int i = 0; i < map_size; i++)
				for (int j = 0; j < map_size; j++)
				{
					Window.draw(square_tab[i][j]);
					Window.draw(square_tab_2[i][j]);
				}

			Window.draw(*gamePlayers);
		}
		break;

		case MENU:
		{
			Window.draw(menuTexture);
			if (MainMenu)
				Window.draw(*MainMenu);
		}
		break;
		}

		if (Additionalmenu)
			Window.draw(*Additionalmenu);

		Window.display();
		Window.clear();
	}

	graphicsOpt.saveToFile();
	generalOpt.saveToFile();
}
