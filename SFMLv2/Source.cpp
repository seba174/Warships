#include <vld.h>
#include <iostream>
#include <memory>
#include <vector>
#include <cstring>
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
#include "Options.h"


int main()
{
	INI_Reader reader("Config/config.ini");
	Options options(reader);

	int map_size = 0;
	const int barSize = 50;
	const int line_thicknessSize = 10;

	float interfaceScale = options.getResolution().x / 1920.0f;
	int bar = barSize * interfaceScale;            
	int line_thickness = line_thicknessSize * interfaceScale;  

	FontHandler& fonthandler = FontHandler::getInstance();
	TextureHandler& textures = TextureHandler::getInstance();

	sf::RectangleShape bImage, bImage2;
	bImage.setTexture(&textures.texture_handler["nowefalev5"]);
	bImage2.setTexture(&textures.texture_handler["nowefalev5"]);

	std::vector<Board*> vect_ship_to_draw;

	sf::Vector2i screenDimensions;
	sf::Vector2i StandardWindowDimensions;

	sf::RenderWindow Window;
	Window.create(sf::VideoMode(0,0), "",  sf::Style::None);

	sf::View view;

	// PASEK MIEDZY PLANSZAMI
	sf::ConvexShape line(4);
	sf::Vector2f square_size;

	sf::RectangleShape **square_tab = nullptr, **square_tab_2 = nullptr;	// tablice kwadratow do rysowania
	sf::RectangleShape rect, trafienie, pudlo;     // kwadraty pudla, trafienia, i kwadratu do przesuwania

	sf::Clock clock;	// czas klatki

	Input input;
	std::unique_ptr<Mouse_S> mouse;

	// TABLICA STATKOW DO STAWIANIA PRZEZ GRACZA

	int count_of_ships = 6;
	Board** AI_set_ships = nullptr;
	bool AI_set = false;

	LevelsDifficulty level = LevelsDifficulty::EASY;
	Gamestates Gamestate = RELOAD_GRAPHICS, drawnGamestate = MENU;
	AdditionalVisualInformations additional_vs_info = NONE;
	
	std::unique_ptr<Game> game;

	std::unique_ptr<Menu> MainMenu = nullptr;
	std::unique_ptr<AdditionalMenu> Additionalmenu = nullptr;

	bool menureset = false;

	sf::Event Event;
	while (Window.isOpen())
	{
		sf::Time dt = clock.restart();		// czas klatki
		input.ResetKeys();
		static bool first = true, reloaded = false;

		while (Window.pollEvent(Event))
		{
			if (Event.type == sf::Event::Closed)
				additional_vs_info = EXIT_INFO;
			else if (Event.type == sf::Event::KeyPressed && Event.key.code == sf::Keyboard::Escape)
			{
				input.setKeyboardEscapeKeyPressed();
				//additional_vs_info = EXIT_INFO;
			}
			else if (Event.type == sf::Event::MouseButtonPressed && Event.key.code == sf::Mouse::Left)
				input.setMouseLeftButtonPressed();
			else if (Event.type == sf::Event::MouseButtonPressed && Event.key.code == sf::Mouse::Right)
				input.setMouseRightButtonPressed();
			else if (Event.type == sf::Event::KeyPressed && Event.key.code == sf::Keyboard::Return)
				input.setKeyboardReturnKeyPressed();
		}
		if (Additionalmenu)
		{
			Additionalmenu->runMenu(Window.mapPixelToCoords(sf::Mouse::getPosition(Window)), input.isMouseLeftButtonPressed(), input, options);
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

			if (input.isKeyboardReturnKeyPressed() && AI_set)
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
				game->play(dt, tmp_vec);
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
			bImage.setSize(sf::Vector2f(screenDimensions.x, screenDimensions.y));
			bImage2.setSize(sf::Vector2f(screenDimensions.x, screenDimensions.y));

			square_size = sf::Vector2f(static_cast<float>(screenDimensions.x) / map_size, static_cast<float>(screenDimensions.y) / map_size); // rozmiar 1 kwadratu mapy)

			rect.setSize(square_size);
			trafienie.setSize(square_size);
			pudlo.setSize(square_size);

			rect.setFillColor(sf::Color::Black);
			rect.setPosition(sf::Vector2f(0, static_cast<float>(bar)));
			trafienie.setFillColor(sf::Color::Red);
			pudlo.setFillColor(sf::Color(128, 128, 128));

			line.setPoint(0, sf::Vector2f(screenDimensions.x, 0));
			line.setPoint(1, sf::Vector2f(screenDimensions.x, screenDimensions.y + bar));
			line.setPoint(2, sf::Vector2f(screenDimensions.x + line_thickness, screenDimensions.y + bar));
			line.setPoint(3, sf::Vector2f(screenDimensions.x + line_thickness, 0));
			line.setOutlineColor(sf::Color::Red);

			bImage.setPosition(sf::Vector2f(0, static_cast<float>(bar)));
			bImage2.setPosition(sf::Vector2f(screenDimensions.x + line_thickness, static_cast<float>(bar)));

			mouse = std::make_unique<Mouse_S>(sf::Vector2f(screenDimensions.x + line_thickness, 2 * screenDimensions.x + line_thickness),
				sf::Vector2f(bar, screenDimensions.y + bar), &Window);

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
			AI_set_ships[0] = new Ships(5, square_size, screenDimensions, sf::Vector2f(0, bar), &textures.texture_handler["big_body_final"]);
			AI_set_ships[1] = new Ships(4, square_size, screenDimensions, sf::Vector2f(0, bar), &textures.texture_handler["big_body_final"]);
			AI_set_ships[2] = new Ships(3, square_size, screenDimensions, sf::Vector2f(0, bar), &textures.texture_handler["big_body_final"]);
			AI_set_ships[3] = new Ships(2, square_size, screenDimensions, sf::Vector2f(0, bar), &textures.texture_handler["big_body_final"]);
			AI_set_ships[4] = new IrregularShip2(square_size, screenDimensions, sf::Vector2f(0, bar), &textures.texture_handler["irregular2"]);
			AI_set_ships[5] = new IrregularShip3(square_size, screenDimensions, sf::Vector2f(0, bar), &textures.texture_handler["irregular3"]);

			game = std::make_unique<Game>(screenDimensions, square_size, sf::Vector2f(0, bar), sf::Vector2f(screenDimensions.x + line_thickness, bar),
				pudlo, trafienie, square_tab, square_tab_2, bar, rect, level);

			additional_vs_info = AdditionalVisualInformations::NONE;
			Gamestate = PlvsAI;
			drawnGamestate = Gamestates::NOTHING;
		}
		break;

		case loadPlvsPl:
		{
			additional_vs_info = AdditionalVisualInformations::NONE;
			drawnGamestate = Gamestates::NOTHING;
		}
		break;

		case MENU:
		{
			MainMenu->runMenu(Window.mapPixelToCoords(sf::Mouse::getPosition(Window)), map_size, level, input.isMouseLeftButtonPressed(), options);
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
			bool wasResolutionChanged = options.wasResolutionChanged();
			bool wasFullScreenChanged = options.wasFullScreenChanged();

			if ((wasFullScreenChanged && options.isFullScreenEnabled()) || (options.isFullScreenEnabled() && first))
			{
				sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
				interfaceScale = desktop.width / 1920.0f;
				screenDimensions = sf::Vector2i(desktop.width / 2 - line_thickness / 2, desktop.height - bar);
				StandardWindowDimensions = sf::Vector2i(desktop.width, desktop.height);
				Window.create(desktop, "Warships", sf::Style::Fullscreen);
			}
			else if ((wasResolutionChanged || first || wasFullScreenChanged) && !options.isFullScreenEnabled())
			{
				interfaceScale = options.getResolution().x / 1920.0f;
				screenDimensions = sf::Vector2i(options.getResolution().x / 2 - line_thickness / 2, options.getResolution().y - bar);
				StandardWindowDimensions = sf::Vector2i(options.getResolution());
				Window.create(sf::VideoMode(StandardWindowDimensions.x, StandardWindowDimensions.y), "Warships", sf::Style::Close);
			}

			bar = barSize * interfaceScale;
			line_thickness = line_thicknessSize * interfaceScale;

			Window.setVerticalSyncEnabled(options.isVerticalSyncEnabled());

			view = Window.getDefaultView();
			view.zoom(100.0f / options.getResolutionScale());
			Window.setView(view);

			if (wasFullScreenChanged || (wasResolutionChanged && !options.isFullScreenEnabled()) || first)
			{
				MainMenu = std::make_unique<Menu>("Warships", sf::Vector2f(StandardWindowDimensions.x / 2, 20 * interfaceScale),
					sf::Vector2f(StandardWindowDimensions.x / 2, 290 * interfaceScale), 130 * interfaceScale, interfaceScale, options);
				Additionalmenu = std::make_unique<AdditionalMenu>(sf::Vector2f(200 * interfaceScale, 0), 80 * interfaceScale,
					sf::Vector2f(StandardWindowDimensions.x, StandardWindowDimensions.y),
					sf::Vector2f(StandardWindowDimensions.x / 2, StandardWindowDimensions.y / 2), additional_vs_info, interfaceScale);
			}
			if (!first || reloaded)
			{
				MainMenu->setMenustate(Menustates::OPT_GRAPHICS);
				reloaded = false;
			}

			Gamestate = MENU;
			if (!first)
				additional_vs_info = AdditionalVisualInformations::APPLY_CHANGES;
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

		case MENU:
		{
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
}


/*switch (additional_vs_info)
{
case EXIT_INFO:
{
std::cout << "EXIT_INFO" << endl;
sf::Vector2i exp = sf::Mouse::getPosition(Window);
sf::Vector2f mouse2 = (Window).mapPixelToCoords(exp);

sf::RectangleShape background(sf::Vector2f(StandardWindowDimensions.x, StandardWindowDimensions.y)),
background_for_text(sf::Vector2f(StandardWindowDimensions.x / 3, StandardWindowDimensions.y / 3));
background.setFillColor(sf::Color(0, 0, 0, 200));
background_for_text.setPosition(StandardWindowDimensions.x / 2 - background_for_text.getSize().x / 2, StandardWindowDimensions.y / 2 - background_for_text.getSize().y / 2);
background_for_text.setFillColor(sf::Color::Red);

sf::Text title("What do you want to do?", mecha, 50);
title.setStyle(sf::Text::Bold);
title.setPosition(StandardWindowDimensions.x / 2 - title.getGlobalBounds().width / 2, background_for_text.getPosition().y);

const int ile = 3;

sf::Text tekst[ile];

string str[] = { "Return to Main Menu","Quit a game", "Resume" };

for (int i = 0; i<ile; i++)
{
tekst[i].setFont(font);
tekst[i].setCharacterSize(35);

tekst[i].setString(str[i]);
tekst[i].setPosition(StandardWindowDimensions.x / 2- tekst[i].getGlobalBounds().width/2, title.getPosition().y+title.getGlobalBounds().height+50 + i * 50);
}


//kliknięcie Return to Main Menu
if (tekst[0].getGlobalBounds().contains(mouse2) &&
MouseLeftButtonPressed)
{
state = BREAK_AND_GO_TO_MENU;
menureset = true;
additional_vs_info = NONE;
}

//kliknięcie Quit a game
else if (tekst[1].getGlobalBounds().contains(mouse2) &&
MouseLeftButtonPressed)
{
state = EXIT;
additional_vs_info = NONE;
}

// kliknięcie Resume
else if (tekst[2].getGlobalBounds().contains(mouse2) &&
MouseLeftButtonPressed)
{
additional_vs_info = NONE;
}



for (int i = 0; i < ile; i++)
if (tekst[i].getGlobalBounds().contains(Window.mapPixelToCoords(sf::Mouse::getPosition(Window))))
tekst[i].setFillColor(sf::Color::Cyan);
else tekst[i].setFillColor(sf::Color::White);

Window.draw(background);
Window.draw(background_for_text);
Window.draw(title);
for (int i = 0; i < ile; ++i)
Window.draw(tekst[i]);
}
break;
}*/


/*
case MENU:
{
std::cout << "MENU" << endl;
enum menuGamestate{DEFAULT, CHOOSE_GAMETYPE, CHOOSE_MAPSIZE, CHOOSE_AILEVEL, LOADING_GAME_VARIABLES, OPTIONS};
static menuGamestate menustate = DEFAULT;
static Gamestate tmpgamestate = Gamestate::MENU;

if (menureset)
{
menustate = DEFAULT;
menureset = false;
}

sf::Vector2i exp = sf::Mouse::getPosition(Window);
sf::Vector2f mouse2 = (Window).mapPixelToCoords(exp);

sf::Text title("Warships", mecha, 100);
title.setStyle(sf::Text::Bold);
title.setPosition(StandardWindowDimensions.x/2 - title.getGlobalBounds().width / 2, 20);



// Zarzadzanie Menu
switch (menustate)
{
case DEFAULT:
{
std::cout << "DEFAULT" << endl;
const int ile = 3;

sf::Text tekst[ile];

string str[] = { "Play","Options","Exit" };
for (int i = 0; i<ile; i++)
{
tekst[i].setFont(font);
tekst[i].setCharacterSize(65);

tekst[i].setString(str[i]);
tekst[i].setPosition(StandardWindowDimensions.x / 2 - tekst[i].getGlobalBounds().width / 2, 250 + i * 120);
}

if(additional_vs_info == NONE)
while (Window.pollEvent(Event))
{
//Wciśnięcie ESC lub przycisk X
if (Event.type == sf::Event::Closed || Event.type == sf::Event::KeyPressed &&
Event.key.code == sf::Keyboard::Escape)
additional_vs_info = EXIT_INFO;

//kliknięcie PLAY
else if (tekst[0].getGlobalBounds().contains(mouse2) &&
Event.type == sf::Event::MouseButtonPressed && Event.key.code == sf::Mouse::Left)
{
menustate = CHOOSE_GAMETYPE;
}

else if (tekst[1].getGlobalBounds().contains(mouse2) &&
Event.type == sf::Event::MouseButtonPressed && Event.key.code == sf::Mouse::Left)
{
menustate = OPTIONS;
}

//kliknięcie EXIT
else if (tekst[ile-1].getGlobalBounds().contains(mouse2) &&
Event.type == sf::Event::MouseButtonPressed && Event.key.code == sf::Mouse::Left)
{
state = EXIT;
}
}

for (int i = 0; i < ile; i++)
if (tekst[i].getGlobalBounds().contains(mouse2))
tekst[i].setFillColor(sf::Color::Cyan);
else tekst[i].setFillColor(sf::Color::White);

Window.draw(title);
for (int i = 0; i < ile; ++i)
Window.draw(tekst[i]);
}
break;

case CHOOSE_GAMETYPE:
{
std::cout << "CHOOSE_GAMETYPE"<<endl;
const int ile = 3;

sf::Text tekst[ile];

string str[] = { "Solo Game","Player vs Player", "Back" };
for (int i = 0; i<ile; i++)
{
tekst[i].setFont(font);
tekst[i].setCharacterSize(65);

tekst[i].setString(str[i]);
tekst[i].setPosition(StandardWindowDimensions.x / 2 - tekst[i].getGlobalBounds().width / 2, 250 + i * 120);
}
if (additional_vs_info == NONE)
while (Window.pollEvent(Event))
{
//Wciśnięcie ESC lub przycisk X
if (Event.type == sf::Event::Closed || Event.type == sf::Event::KeyPressed &&
Event.key.code == sf::Keyboard::Escape)
additional_vs_info = EXIT_INFO;

//kliknięcie SOLO GAME
else if (tekst[0].getGlobalBounds().contains(mouse2) &&
Event.type == sf::Event::MouseButtonPressed && Event.key.code == sf::Mouse::Left)
{
menustate = menuGamestate::CHOOSE_MAPSIZE;
tmpgamestate = Gamestate::PlvsAI;
}

//kliknięcie PLAYER VS PLAYER
else if (tekst[1].getGlobalBounds().contains(mouse2) &&
Event.type == sf::Event::MouseButtonPressed && Event.key.code == sf::Mouse::Left)
{
menustate = menuGamestate::CHOOSE_MAPSIZE;
tmpgamestate = Gamestate::PlvsPl;
}

//kliknięcie Back
else if (tekst[ile-1].getGlobalBounds().contains(mouse2) &&
Event.type == sf::Event::MouseButtonPressed && Event.key.code == sf::Mouse::Left)
{
menustate = DEFAULT;
tmpgamestate = Gamestate::MENU;
}
}

for (int i = 0; i < ile; i++)
if (tekst[i].getGlobalBounds().contains(mouse2))
tekst[i].setFillColor(sf::Color::Cyan);
else tekst[i].setFillColor(sf::Color::White);

Window.draw(title);
for (int i = 0; i < ile; ++i)
Window.draw(tekst[i]);
}
break;

case CHOOSE_MAPSIZE:
{
std::cout << "CHOOSE_MAPSIZE"<<endl;
const int ile = 4;

sf::Text tekst[ile];

string str[] = { "10 x 10","20 x 20", "40 x 40", "Back" };
for (int i = 0; i<ile; i++)
{
tekst[i].setFont(font);
tekst[i].setCharacterSize(65);

tekst[i].setString(str[i]);
tekst[i].setPosition(StandardWindowDimensions.x / 2 - tekst[i].getGlobalBounds().width / 2, 250 + i * 120);
}

if (additional_vs_info == NONE)
while (Window.pollEvent(Event))
{
//Wciśnięcie ESC lub przycisk X
if (Event.type == sf::Event::Closed || Event.type == sf::Event::KeyPressed &&
Event.key.code == sf::Keyboard::Escape)
additional_vs_info = EXIT_INFO;

//kliknięcie 10 x 10
else if (tekst[0].getGlobalBounds().contains(mouse2) &&
Event.type == sf::Event::MouseButtonPressed && Event.key.code == sf::Mouse::Left)
{
map_size = 10;
if (tmpgamestate == PlvsAI)
menustate = menuGamestate::CHOOSE_AILEVEL;
else
{
menustate = menuGamestate::LOADING_GAME_VARIABLES;
state = Gamestate::loadGameVariables;
}
}

//kliknięcie 20 x 20
else if (tekst[1].getGlobalBounds().contains(mouse2) &&
Event.type == sf::Event::MouseButtonPressed && Event.key.code == sf::Mouse::Left)
{
map_size = 20;
if (tmpgamestate == PlvsAI)
menustate = menuGamestate::CHOOSE_AILEVEL;
else
{
menustate = menuGamestate::LOADING_GAME_VARIABLES;
state = Gamestate::loadGameVariables;
}
}

//kliknięcie 40 x 40
else if (tekst[2].getGlobalBounds().contains(mouse2) &&
Event.type == sf::Event::MouseButtonPressed && Event.key.code == sf::Mouse::Left)
{
map_size = 40;
if (tmpgamestate == PlvsAI)
menustate = menuGamestate::CHOOSE_AILEVEL;
else
{
menustate = menuGamestate::LOADING_GAME_VARIABLES;
state = Gamestate::loadGameVariables;
}
}

else if (tekst[ile - 1].getGlobalBounds().contains(mouse2) &&
Event.type == sf::Event::MouseButtonPressed && Event.key.code == sf::Mouse::Left)
{
menustate = CHOOSE_GAMETYPE;
tmpgamestate = Gamestate::MENU;
}
}

for (int i = 0; i < ile; i++)
if (tekst[i].getGlobalBounds().contains(mouse2))
tekst[i].setFillColor(sf::Color::Cyan);
else tekst[i].setFillColor(sf::Color::White);

Window.draw(title);
for (int i = 0; i < ile; ++i)
Window.draw(tekst[i]);
}
break;

case LOADING_GAME_VARIABLES:
{
std::cout << "LOADING_GAME_VARIABLES"<<endl;
if (tmpgamestate == PlvsPl)
{
menustate = DEFAULT;
state = loadPlvsPl;
}
else if (tmpgamestate == PlvsAI)
{
menustate = DEFAULT;
state = loadPlvsAI;
}
}
break;

case CHOOSE_AILEVEL:
{
std::cout << "CHOOSE_AILEVEL" << endl;
const int ile = 4;

sf::Text tekst[ile];

string str[] = { "Easy","Medium", "Hard", "Back" };

for (int i = 0; i < ile; i++)
{
tekst[i].setFont(font);
tekst[i].setCharacterSize(65);

tekst[i].setString(str[i]);
tekst[i].setPosition(StandardWindowDimensions.x / 2 - tekst[i].getGlobalBounds().width / 2, 250 + i * 120);
}

if (additional_vs_info == NONE)
while (Window.pollEvent(Event))
{
//Wciśnięcie ESC lub przycisk X
if (Event.type == sf::Event::Closed || Event.type == sf::Event::KeyPressed &&
Event.key.code == sf::Keyboard::Escape)
additional_vs_info = EXIT_INFO;

//kliknięcie EASY
else if (tekst[0].getGlobalBounds().contains(mouse2) &&
Event.type == sf::Event::MouseButtonPressed && Event.key.code == sf::Mouse::Left)
{
menustate = menuGamestate::LOADING_GAME_VARIABLES;
state = Gamestate::loadGameVariables;
level = EASY;
}

//kliknięcie MEDIUM
else if (tekst[1].getGlobalBounds().contains(mouse2) &&
Event.type == sf::Event::MouseButtonPressed && Event.key.code == sf::Mouse::Left)
{
menustate = menuGamestate::LOADING_GAME_VARIABLES;
state = Gamestate::loadGameVariables;
level = MEDIUM;
}

//kliknięcie HARD
else if (tekst[2].getGlobalBounds().contains(mouse2) &&
Event.type == sf::Event::MouseButtonPressed && Event.key.code == sf::Mouse::Left)
{
menustate = menuGamestate::LOADING_GAME_VARIABLES;
state = Gamestate::loadGameVariables;
level = HARD;
}

else if (tekst[ile - 1].getGlobalBounds().contains(mouse2) &&
Event.type == sf::Event::MouseButtonPressed && Event.key.code == sf::Mouse::Left)
{
menustate = CHOOSE_MAPSIZE;
}
}

for (int i = 0; i < ile; i++)
if (tekst[i].getGlobalBounds().contains(mouse2))
tekst[i].setFillColor(sf::Color::Cyan);
else tekst[i].setFillColor(sf::Color::White);

Window.draw(title);
for (int i = 0; i < ile; ++i)
Window.draw(tekst[i]);
}
break;

case OPTIONS:
{

std::cout << "DEFAULT" << endl;
const int ile = 3;

sf::Text tekst[ile];

string str[] = { "Play","Optioaaans","Exit" };
for (int i = 0; i<ile; i++)
{
tekst[i].setFont(font);
tekst[i].setCharacterSize(65);

tekst[i].setString(str[i]);
tekst[i].setPosition(StandardWindowDimensions.x / 2 - tekst[i].getGlobalBounds().width / 2, 250 + i * 120);
}

if (additional_vs_info == NONE)
while (Window.pollEvent(Event))
{
//Wciśnięcie ESC lub przycisk X
if (Event.type == sf::Event::Closed || Event.type == sf::Event::KeyPressed &&
Event.key.code == sf::Keyboard::Escape)
additional_vs_info = EXIT_INFO;

//kliknięcie PLAY
else if (tekst[0].getGlobalBounds().contains(mouse2) &&
Event.type == sf::Event::MouseButtonPressed && Event.key.code == sf::Mouse::Left)
{
menustate = CHOOSE_GAMETYPE;
}

else if (tekst[1].getGlobalBounds().contains(mouse2) &&
Event.type == sf::Event::MouseButtonPressed && Event.key.code == sf::Mouse::Left)
{
menustate = OPTIONS;
}

//kliknięcie EXIT
else if (tekst[ile - 1].getGlobalBounds().contains(mouse2) &&
Event.type == sf::Event::MouseButtonPressed && Event.key.code == sf::Mouse::Left)
{
state = EXIT;
}
}

for (int i = 0; i < ile; i++)
if (tekst[i].getGlobalBounds().contains(mouse2))
tekst[i].setFillColor(sf::Color::Cyan);
else tekst[i].setFillColor(sf::Color::White);

Window.draw(title);
for (int i = 0; i < ile; ++i)
Window.draw(tekst[i]);
}
break;

}
}
break;

*/