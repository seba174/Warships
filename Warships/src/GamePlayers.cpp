#include "stdafx.h"
#include "GamePlayers.h"
#include "Input.h"
#include "LanguageManager.h"
#include "TextureHandler.h"
#include "SoundManager.h"
#include "MusicHandler.h"
#include "GeneralOptions.h"
#include "UtilityFunctions.h"


int GamePlayers::whoStarts() const
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist_num(1, 2);

	return dist_num(mt);
}

void GamePlayers::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	gamePlayersState drawnState = currentState;
	if (currentState == gamePlayersState::finish)
		if (utilityClock.getElapsedTime() <= delayAtFinish)
		{
			if (player1Won)
				drawnState = gamePlayersState::player1Moves;
			else if (player2Won)
				drawnState = gamePlayersState::player2Moves;
		}

	switch (drawnState)
	{
	case gamePlayersState::player1Moves:
	{
		player1.drawSquareTab(target, states);
		player2.drawSquareTab(target, states);
		for (Board* ship : vectShipsToDrawPlayer1)
		{
			if (ship->shouldBeDrawed())
			{
				ship->updateTexture(lastFrameTime);
				target.draw(ship->returnShip(), states);
			}
		}
		for (Board* ship : vectShipsToDrawPlayer2)
		{
			if (ship->shouldBeDrawed())
			{
				ship->updateTexture(lastFrameTime);
				target.draw(ship->returnShip(), states);
			}
		}
		target.draw(player1Background, states);
		player1.draw(target);
		
		if (shoudlDrawMenuPlayer1TurnStarts)
			target.draw(menuPlayer1TurnStarts, states);
	} break;

	case gamePlayersState::player2Moves:
	{
		player1.drawSquareTab(target, states);
		player2.drawSquareTab(target, states);
		for (Board* ship : vectShipsToDrawPlayer1)
		{
			if (ship->shouldBeDrawed())
			{
				ship->updateTexture(lastFrameTime);
				target.draw(ship->returnShip(), states);
			}
		}
		for (Board* ship : vectShipsToDrawPlayer2)
		{
			if (ship->shouldBeDrawed())
			{
				ship->updateTexture(lastFrameTime);
				target.draw(ship->returnShip(), states);
			}
		}
		target.draw(player2Background, states);
		player2.draw(target);

		if (shoudlDrawMenuPlayer2TurnStarts)
			target.draw(menuPlayer2TurnStarts, states);
	} break;

	case gamePlayersState::player1SetShips:
	{
		for (Board* ship : vectShipsToDrawPlayer1)
		{
			ship->updateTexture(lastFrameTime);
			target.draw(ship->returnShip(), states);
		}
		player1.draw(target);
		target.draw(advertPlayer1, states);

		if (shouldDisplayHelpPlayer1)
			for (const RectangleWithTextAndFrames& rect : helpInformationPlayer1)
				target.draw(rect, states);
		target.draw(helpButtonPlayer1, states);
		target.draw(helpBubble, states);

		if (shoudlDrawMenuPlayer1SetShipsInfo)
			target.draw(menuPlayer1SetShipsInfo, states);

	} break;

	case gamePlayersState::player2SetShips:
	{
		for (Board* ship : vectShipsToDrawPlayer2)
		{
			ship->updateTexture(lastFrameTime);
			target.draw(ship->returnShip(), states);
		}
		player2.draw(target);
		target.draw(advertPlayer2, states);

		if (shouldDisplayHelpPlayer2)
			for (const RectangleWithTextAndFrames& rect : helpInformationPlayer2)
				target.draw(rect, states);
		target.draw(helpButtonPlayer2);

		if (shoudlDrawMenuPlayer2SetShipsInfo)
			target.draw(menuPlayer2SetShipsInfo, states);
	} break;

	case gamePlayersState::finish:
	{
		target.draw(finishMenu, states);
	} break;

	case gamePlayersState::statistics:
	{
		target.draw(statisticsMenu, states);
	} break;
	}
}

bool GamePlayers::checkForFinish() const
{
	return !(player1.HP.chceckhp() && player2.HP.chceckhp());
}

void GamePlayers::updateBackgroundInformation()
{
	if (player1.HP.size_5 == 0)
	{
		player1Background.markDestroyed(shipOrder::Ship5);
		if (!vectShipsToDrawPlayer2[0]->shouldBeDrawed())
		{
			vectShipsToDrawPlayer2[0]->setDestroyedTexture();
			vectShipsToDrawPlayer2[0]->setShouldDraw(true);
			player1.resetSquareTab(5);
		}
	}
	if (player1.HP.size_4 == 0)
	{
		player1Background.markDestroyed(shipOrder::Ship4);
		if (!vectShipsToDrawPlayer2[1]->shouldBeDrawed())
		{
			vectShipsToDrawPlayer2[1]->setDestroyedTexture();
			vectShipsToDrawPlayer2[1]->setShouldDraw(true);
			player1.resetSquareTab(4);
		}
	}
	if (player1.HP.size_3 == 0)
	{
		player1Background.markDestroyed(shipOrder::Ship3);
		if (!vectShipsToDrawPlayer2[2]->shouldBeDrawed())
		{
			vectShipsToDrawPlayer2[2]->setDestroyedTexture();
			vectShipsToDrawPlayer2[2]->setShouldDraw(true);
			player1.resetSquareTab(3);
		}
	}
	if (player1.HP.size_2 == 0)
	{
		player1Background.markDestroyed(shipOrder::Ship2);
		if (!vectShipsToDrawPlayer2[3]->shouldBeDrawed())
		{
			vectShipsToDrawPlayer2[3]->setDestroyedTexture();
			vectShipsToDrawPlayer2[3]->setShouldDraw(true);
			player1.resetSquareTab(2);
		}
	}
	if (player1.HP.size_ir2 == 0)
	{
		player1Background.markDestroyed(shipOrder::Ship2x2);
		if (!vectShipsToDrawPlayer2[4]->shouldBeDrawed())
		{
			vectShipsToDrawPlayer2[4]->setDestroyedTexture();
			vectShipsToDrawPlayer2[4]->setShouldDraw(true);
			player1.resetSquareTab(10);
		}
	}
	if (player1.HP.size_ir3 == 0)
	{
		player1Background.markDestroyed(shipOrder::Ship2x4);
		if (!vectShipsToDrawPlayer2[5]->shouldBeDrawed())
		{
			vectShipsToDrawPlayer2[5]->setDestroyedTexture();
			vectShipsToDrawPlayer2[5]->setShouldDraw(true);
			player1.resetSquareTab(11);
		}
	}

	if (player2.HP.size_5 == 0)
	{
		player2Background.markDestroyed(shipOrder::Ship5);
		if (!vectShipsToDrawPlayer1[0]->shouldBeDrawed())
		{
			vectShipsToDrawPlayer1[0]->setDestroyedTexture();
			vectShipsToDrawPlayer1[0]->setShouldDraw(true);
			player2.resetSquareTab(5);
		}
	}
	if (player2.HP.size_4 == 0)
	{
		player2Background.markDestroyed(shipOrder::Ship4);
		if (!vectShipsToDrawPlayer1[1]->shouldBeDrawed())
		{
			vectShipsToDrawPlayer1[1]->setDestroyedTexture();
			vectShipsToDrawPlayer1[1]->setShouldDraw(true);
			player2.resetSquareTab(4);
		}
	}
	if (player2.HP.size_3 == 0)
	{
		player2Background.markDestroyed(shipOrder::Ship3);
		if (!vectShipsToDrawPlayer1[2]->shouldBeDrawed())
		{
			vectShipsToDrawPlayer1[2]->setDestroyedTexture();
			vectShipsToDrawPlayer1[2]->setShouldDraw(true);
			player2.resetSquareTab(3);
		}
	}
	if (player2.HP.size_2 == 0)
	{
		player2Background.markDestroyed(shipOrder::Ship2);
		if (!vectShipsToDrawPlayer1[3]->shouldBeDrawed())
		{
			vectShipsToDrawPlayer1[3]->setDestroyedTexture();
			vectShipsToDrawPlayer1[3]->setShouldDraw(true);
			player2.resetSquareTab(2);
		}
	}
	if (player2.HP.size_ir2 == 0)
	{
		player2Background.markDestroyed(shipOrder::Ship2x2);
		if (!vectShipsToDrawPlayer1[4]->shouldBeDrawed())
		{
			vectShipsToDrawPlayer1[4]->setDestroyedTexture();
			vectShipsToDrawPlayer1[4]->setShouldDraw(true);
			player2.resetSquareTab(10);
		}
	}
	if (player2.HP.size_ir3 == 0)
	{
		player2Background.markDestroyed(shipOrder::Ship2x4);
		if (!vectShipsToDrawPlayer1[5]->shouldBeDrawed())
		{
			vectShipsToDrawPlayer1[5]->setDestroyedTexture();
			vectShipsToDrawPlayer1[5]->setShouldDraw(true);
			player2.resetSquareTab(11);
		}
	}
}

void GamePlayers::updatePlayersFinishInformations(LanguageManager& langMan)
{
	finishMenu.addPlayer(playersInformations(player1.getPlayerName(), player1Won, player1.returnAccuracy(), player1.returnTotalShotsNumber(), player1.returnTotalHitsNumber(),
		player1.retrunMaximumHits(), player1.returnMaximumMisses()));
	finishMenu.addPlayer(playersInformations(player2.getPlayerName(), player2Won, player2.returnAccuracy(), player2.returnTotalShotsNumber(), player2.returnTotalHitsNumber(),
		player2.retrunMaximumHits(), player2.returnMaximumMisses()));

	statisticsMenu.addPlayer(playersInformations(player1.getPlayerName(), player1Won, player1.returnAccuracy(), player1.returnTotalShotsNumber(), player1.returnTotalHitsNumber(),
		player1.retrunMaximumHits(), player1.returnMaximumMisses()));
	statisticsMenu.addPlayer(playersInformations(player2.getPlayerName(), player2Won, player2.returnAccuracy(), player2.returnTotalShotsNumber(), player2.returnTotalHitsNumber(),
		player2.retrunMaximumHits(), player2.returnMaximumMisses()));

	if (player1Won)
		finishMenu.setTitle(player1.getPlayerName() + L' ' + langMan.getText("has won the game") + L'!');
	else if (player2Won)
		finishMenu.setTitle(player2.getPlayerName() + L' ' + langMan.getText("has won the game") + L'!');
}

void GamePlayers::animateScalingHelpBubble(float endScale, float howMuchScaleInOneStep)
{
	float currentScale{ helpBubble.getScale() };

	if (currentScale > endScale)
	{
		helpBubble.setScale(
			currentScale - howMuchScaleInOneStep > endScale ? currentScale - howMuchScaleInOneStep : endScale);
	}
	else if (currentScale < endScale)
	{
		helpBubble.setScale(
			currentScale + howMuchScaleInOneStep < endScale ? currentScale + howMuchScaleInOneStep : endScale);
	}
}

void GamePlayers::animateDisappearingHelpBubble(const sf::Time & dt)
{
	if (utilityClock2.getElapsedTime() < helpBubbleDisplayTime)
	{
		helpBubble.setTextColor(sf::Color::Black);
	}
	else if (utilityClock2.getElapsedTime() < helpBubbleDisplayTime + helpBubbleAnimationTime)
	{
		sf::Color bubbleBubbleColor{ helpBubble.getBubbleColor() };
		sf::Color bubbleTextColor{ helpBubble.getTextColor() };
		bubbleBubbleColor.a =
			bubbleBubbleColor.a - (255 / helpBubbleAnimationTime.asSeconds())*dt.asSeconds() > 0
			? static_cast<int>(bubbleBubbleColor.a - (255 / helpBubbleAnimationTime.asSeconds())*dt.asSeconds())
			: 0;

		bubbleTextColor.a =
			bubbleTextColor.a - (255 / helpBubbleAnimationTime.asSeconds())*dt.asSeconds() > 0
			? static_cast<int>(bubbleTextColor.a - (255 / helpBubbleAnimationTime.asSeconds())*dt.asSeconds())
			: 0;

		helpBubble.setBubbleColor(bubbleBubbleColor);
		helpBubble.setTextColor(bubbleTextColor);
	}
	else
	{
		helpBubble.setBubbleColor(sf::Color::Transparent);
		helpBubble.setTextColor(sf::Color::Transparent);
	}
}

void GamePlayers::play(const sf::Time & dt, const sf::Vector2f & mousepos, const Input& input, LanguageManager& langMan, GameStates& gamestate,
	SoundManager& soundManager, MusicHandler& musicHandler)
{
	lastFrameTime = dt;
	player1Background.setTimeString(gameTimer.returnTimeAsString(), langMan);
	player2Background.setTimeString(gameTimer.returnTimeAsString(), langMan);

	switch (currentState)
	{
	case gamePlayersState::constructorState:
	{
		musicHandler.play(MusicName::GameTheme);
		currentState = gamePlayersState::player1SetShips;
		utilityClock.restart();
	} break;
	case gamePlayersState::player1SetShips:
	{
		utilityTime += dt;
		if (utilityTime <= pausedSetShipsTime)
			break;
		else
			shoudlDrawMenuPlayer1SetShipsInfo = false;

		if (utilityClock.getElapsedTime() < pausedSetShipsTime + helpBubbleAnimationTime)
		{
			helpBubble.setTextColor(sf::Color::Transparent);
			animateScalingHelpBubble(1, dt / helpBubbleAnimationTime);
			utilityClock2.restart();
		}
		else
			animateDisappearingHelpBubble(dt);

		if (mousePlayer1.isMouseWithinArea())
		{
			if (input.isMouseLeftButtonPressed() && !player1.getShipsSetUp())
				player1.setPlaceShip();
			else if (input.isMouseRightButtonPressed() && !player1.getShipsSetUp())
				player1.rotateShip();

			player1.playerSetShips(mousePlayer1.returnPositionInBounds(), vectShipsToDrawPlayer1, soundManager);
		}

		if (player1.getShipsSetUp())
		{
			currentState = gamePlayersState::player2SetShips;
			utilityTime = sf::Time();
			std::for_each(vectShipsToDrawPlayer1.begin(), vectShipsToDrawPlayer1.end(), [](Board* ship) {ship->setShouldDraw(false); });
		}

		if (helpButtonPlayer1.getGlobalBounds().contains(mousepos))
			shouldDisplayHelpPlayer1 = true;
		else
			shouldDisplayHelpPlayer1 = false;
	} break;

	case gamePlayersState::player2SetShips:
	{
		utilityTime += dt;
		if (utilityTime <= pausedSetShipsTime)
			break;
		else
			shoudlDrawMenuPlayer2SetShipsInfo = false;

		if (mousePlayer2.isMouseWithinArea())
		{
			if (input.isMouseLeftButtonPressed() && !player2.getShipsSetUp())
				player2.setPlaceShip();
			else if (input.isMouseRightButtonPressed() && !player2.getShipsSetUp())
				player2.rotateShip();

			player2.playerSetShips(mousePlayer2.returnPositionInBounds(), vectShipsToDrawPlayer2, soundManager);
		}

		if (player2.getShipsSetUp())
		{
			currentState = gamePlayersState::loadVariablesAndStart;
			std::for_each(vectShipsToDrawPlayer2.begin(), vectShipsToDrawPlayer2.end(), [](Board* ship) {ship->setShouldDraw(false); });
		}

		if (helpButtonPlayer2.getGlobalBounds().contains(mousepos))
			shouldDisplayHelpPlayer2 = true;
		else
			shouldDisplayHelpPlayer2 = false;
	} break;

	case gamePlayersState::loadVariablesAndStart:
	{
		int who = whoStarts();
		if (who == 1)
			currentState = gamePlayersState::player1Moves;
		else if (who == 2)
			currentState = gamePlayersState::player2Moves;
		utilityTime = sf::Time();
	} break;

	case gamePlayersState::player1Moves:
	{
		gameTimer.runGameTimer(dt);
		utilityTime += dt;
		if (utilityTime <= turnInfoTime)
		{
			shoudlDrawMenuPlayer1TurnStarts = true;
			break;
		}
		else
			shoudlDrawMenuPlayer1TurnStarts = false;

		player1.playerMouseInput(dt, mousepos);

		if (!playerFinishes)
		{
			if (input.isMouseLeftButtonPressed() && player1.isMouseInEnemyBounds(mousepos))
				player1.getPlayerMoved() = true;

			if (player1.playerMoves(player1.getRectPositionInGame(), soundManager))
			{
				playerFinishes = true;
				utilityClock.restart();
			}
			updateBackgroundInformation();
		}

		if (playerFinishes)
		{
			if (utilityClock.getElapsedTime() < playerDelay)
				return;

			player1.setPlayersCursorPositon(sf::Mouse::getPosition());
			if (player2.getPlayersCursorPosition() != sf::Vector2i())
				sf::Mouse::setPosition(player2.getPlayersCursorPosition());

			currentState = gamePlayersState::player2Moves;
			utilityTime = sf::Time();
			shoudlDrawMenuPlayer2TurnStarts = true;
			playerFinishes = false;
		}
	
		if (checkForFinish())
		{
			player1Won = true;
			updatePlayersFinishInformations(langMan);
			currentState = gamePlayersState::finish;
			utilityClock.restart();
		}
	} break;

	case gamePlayersState::player2Moves:
	{
		gameTimer.runGameTimer(dt);
		utilityTime += dt;
		if (utilityTime <= turnInfoTime)
		{
			shoudlDrawMenuPlayer2TurnStarts = true;
			break;
		}
		else
			shoudlDrawMenuPlayer2TurnStarts = false;

		player2.playerMouseInput(dt, mousepos);
		
		if (!playerFinishes)
		{
			if (input.isMouseLeftButtonPressed() && player2.isMouseInEnemyBounds(mousepos))
				player2.getPlayerMoved() = true;
			if (player2.playerMoves(player2.getRectPositionInGame(), soundManager))
			{
				playerFinishes = true;
				utilityClock.restart();
			}
			updateBackgroundInformation();
		}

		if (playerFinishes)
		{
			if (utilityClock.getElapsedTime() < playerDelay)
				return;

			player2.setPlayersCursorPositon(sf::Mouse::getPosition());
			if (player2.getPlayersCursorPosition() != sf::Vector2i())
				sf::Mouse::setPosition(player1.getPlayersCursorPosition());

			currentState = gamePlayersState::player1Moves;
			utilityTime = sf::Time();
			shoudlDrawMenuPlayer1TurnStarts = true;
			playerFinishes = false;
		}	

		if (checkForFinish())
		{
			player2Won = true;
			updatePlayersFinishInformations(langMan);
			currentState = gamePlayersState::finish;
			utilityClock.restart();
		}
	} break;

	case gamePlayersState::finish:
	{
		if (!wasGameLogged && logger)
		{
			logger->logPlayerVsPlayerGame(mapSize, player1.returnAccuracy(), finishMenu.giveStars(player1.returnAccuracy()),
				player2.returnAccuracy(), finishMenu.giveStars(player2.returnAccuracy()));
			wasGameLogged = true;
		}
		if (input.isMouseLeftButtonPressed())
		{
			if (finishMenu.menuButtons.PushButtonContains(0, mousepos))
			{
				currentState = gamePlayersState::statistics;
			} // Statistics button

			if (finishMenu.menuButtons.PushButtonContains(1, mousepos))
			{
				gamestate = GameStates::breakAndGoToMenu;
			} // Return to Main Menu

			if (finishMenu.menuButtons.PushButtonContains(2, mousepos))
			{
				gamestate = GameStates::Exit;
			} // Quit the game
		}

		finishMenu.updateStars(dt);
		finishMenu.updateButtons(dt, mousepos);

	} break;

	case gamePlayersState::statistics:
	{
		if (input.isMouseLeftButtonPressed())
		{
			if (statisticsMenu.menuButtons.PushButtonContains(0, mousepos))
			{
				currentState = gamePlayersState::finish;
			} // Back button

			if (statisticsMenu.menuButtons.PushButtonContains(1, mousepos))
			{
				gamestate = GameStates::breakAndGoToMenu;
			} // Return to Main Menu

			if (statisticsMenu.menuButtons.PushButtonContains(2, mousepos))
			{
				gamestate = GameStates::Exit;
			} // Quit the game
		}

		statisticsMenu.updateButtons(dt, mousepos);
	} break;
	}
}

GamePlayers::GamePlayers(const sf::Vector2i & dim, const sf::Vector2f & SquareSize,
	const sf::Vector2f & player1_setpoints, const sf::Vector2f & player2_setpoints, const sf::RectangleShape & pudlo, const sf::RectangleShape & trafienie,
	sf::RectangleShape & player1Rect, sf::RectangleShape & player2Rect, const Mouse_S& pl1Mouse, const Mouse_S& pl2Mouse,
	const sf::Vector2f & title_or1st_button_position, int space_between_buttons, const sf::Vector2f& backgroundSize, const sf::Vector2f& backgroundForSubMenuPosition,
	float interfaceScale, LanguageManager& langMan, const sf::Vector2f& screenDim, const GeneralOptions& genOpt)

	: player1(dim, SquareSize, player2_setpoints, nullptr, player1_setpoints, pudlo, trafienie, player1Rect),
	player2(dim, SquareSize, player1_setpoints, nullptr, player2_setpoints, pudlo, trafienie, player2Rect),
	mousePlayer1(pl1Mouse),
	mousePlayer2(pl2Mouse),
	player1Background(dim, SquareSize, player1_setpoints, interfaceScale, langMan),
	player2Background(dim, SquareSize, player2_setpoints, interfaceScale, langMan),
	shoudlDrawMenuPlayer1SetShipsInfo(true), shoudlDrawMenuPlayer2SetShipsInfo(true),
	shoudlDrawMenuPlayer1TurnStarts(true), shoudlDrawMenuPlayer2TurnStarts(true),
	player1Won(false), player2Won(false),
	advertPlayer1(dim, player2_setpoints, interfaceScale),
	advertPlayer2(dim, player1_setpoints, interfaceScale),
	finishMenu(screenDim, langMan, interfaceScale, static_cast<int>(dim.x / SquareSize.x)),
	statisticsMenu(screenDim, langMan, interfaceScale),
	helpInformationPlayer1(2),
	helpInformationPlayer2(2),
	wasGameLogged(false),
	mapSize(static_cast<int>(dim.x / SquareSize.x)),
	playerFinishes(false)
{
	player1.setPlayerName(stringToWstringConversion(genOpt.getPlayer1Name()));
	player2.setPlayerName(stringToWstringConversion(genOpt.getPlayer2Name()));

	std::wstring str = L",\n" + langMan.getText("you still have to destroy following ships") + L':';
	player1Background.setDisplayedString(player1.getPlayerName() + str);
	player2Background.setDisplayedString(player2.getPlayerName() + str);


	currentState = gamePlayersState::constructorState;
	int playersBackgroundOffset = static_cast<int>(70 * interfaceScale);

	player1.setEnemyShips(player2.getPlayerShips());
	player2.setEnemyShips(player1.getPlayerShips());
	player1Background.setPosition(playersBackgroundOffset);
	player2Background.setPosition(playersBackgroundOffset);


	// SubMenu title character size
	int title_size_1 = static_cast<int>(55 * interfaceScale);
	int title_size_2 = static_cast<int>(80 * interfaceScale);

	// SubMenu character size
	int submenu_size = static_cast<int>(35 * interfaceScale);

	// Background for SubMenu Exit size
	sf::Vector2f backgroundForSubmenuExitSize(550 * interfaceScale, 370 * interfaceScale);

	// Background for SubMenu Exit size
	sf::Vector2f backgroundForSubmenuApplyChangesSize(600 * interfaceScale, 320 * interfaceScale);

	// Background for SubMenu Color
	sf::Color backgroundForSubMenuColor = sf::Color::Red;

	// Background Color for Exit
	sf::Color backgroundExitColor = sf::Color(0, 0, 0, 200);

	// Button size
	sf::Vector2f button_size(340 * interfaceScale, 70 * interfaceScale);

	// Bounds color
	sf::Color bounds_color = sf::Color::White;

	sf::Vector2f logoSize(sf::Vector2f(120, 120)*interfaceScale);


	FontHandler& handler = FontHandler::getInstance();


	std::wstring tmp = player1.getPlayerName();
	menuPlayer1TurnStarts.construct(backgroundSize, backgroundForSubmenuExitSize, sf::Vector2f(backgroundForSubMenuPosition.x, backgroundForSubMenuPosition.y + title_size_2),
		sf::Color::Transparent, backgroundExitColor, sf::Vector2f(0, 0), tmp, L"", title_size_2, submenu_size,
		title_or1st_button_position, title_or1st_button_position, button_size, space_between_buttons, bounds_color, handler.font_handler["Mecha"], interfaceScale);
	tmp += L",\n" + langMan.getText("Please set up your ships");
	menuPlayer1SetShipsInfo.construct(backgroundSize, backgroundForSubmenuExitSize, sf::Vector2f(backgroundForSubMenuPosition.x, backgroundForSubMenuPosition.y + title_size_1),
		sf::Color::Transparent, backgroundExitColor, sf::Vector2f(0, 0), tmp, L"", title_size_1, submenu_size,
		title_or1st_button_position, title_or1st_button_position, button_size, space_between_buttons, bounds_color, handler.font_handler["Mecha"], interfaceScale);

	tmp = player2.getPlayerName();
	menuPlayer2TurnStarts.construct(backgroundSize, backgroundForSubmenuExitSize, sf::Vector2f(backgroundForSubMenuPosition.x, backgroundForSubMenuPosition.y + title_size_2),
		sf::Color::Transparent, backgroundExitColor, sf::Vector2f(0, 0), tmp, L"", title_size_2, submenu_size,
		title_or1st_button_position, title_or1st_button_position, button_size, space_between_buttons, bounds_color, handler.font_handler["Mecha"], interfaceScale);
	tmp += L",\n" + langMan.getText("Please set up your ships");
	menuPlayer2SetShipsInfo.construct(backgroundSize, backgroundForSubmenuExitSize, sf::Vector2f(backgroundForSubMenuPosition.x, backgroundForSubMenuPosition.y + title_size_1),
		sf::Color::Transparent, backgroundExitColor, sf::Vector2f(0, 0), tmp, L"", title_size_1, submenu_size,
		title_or1st_button_position, title_or1st_button_position, button_size, space_between_buttons, bounds_color, handler.font_handler["Mecha"], interfaceScale);

	advertPlayer1.setLogoSize(logoSize);
	advertPlayer1.setLogoPosition(sf::Vector2f(player2_setpoints.x + dim.x / 2, player2_setpoints.y + dim.y - logoSize.y));

	advertPlayer2.setLogoSize(logoSize);
	advertPlayer2.setLogoPosition(sf::Vector2f(player1_setpoints.x + dim.x / 2, player1_setpoints.y + dim.y - logoSize.y));

	player1Background.setTimeFontSize(static_cast<float>(title_size_1));
	player2Background.setTimeFontSize(static_cast<float>(title_size_1));

	sf::Vector2f helpButtonSize(sf::Vector2f(70, 70)*interfaceScale);
	unsigned offsetHelpButton = static_cast<unsigned>(10 * interfaceScale);

	helpButtonPlayer1.setSize(helpButtonSize);
	helpButtonPlayer2.setSize(helpButtonSize);
	helpButtonPlayer1.setPosition(player2_setpoints.x + offsetHelpButton, player2_setpoints.y + offsetHelpButton);
	helpButtonPlayer2.setPosition(player1_setpoints.x + dim.x - helpButtonPlayer2.getSize().x - offsetHelpButton, player1_setpoints.y + offsetHelpButton);
	helpButtonPlayer1.setTexture(&TextureHandler::getInstance().texture_handler["helpButton"]);
	helpButtonPlayer2.setTexture(&TextureHandler::getInstance().texture_handler["helpButton"]);

	unsigned additionalSpaceForFrame = static_cast<unsigned>(10 * interfaceScale);
	int helpFontSize = static_cast<unsigned>(27 * interfaceScale);
	sf::Vector2f helpInformationSize(sf::Vector2f(820, 55)*interfaceScale);
	int helpButtonOutlineThickness = static_cast<int>(3 * interfaceScale);
	int YoffsetForHelpButton = static_cast<int>(150 * interfaceScale);
	int spaceBetweenHelpButtons = static_cast<int>(80 * interfaceScale);

	unsigned helpBubbleCharacterSize{ static_cast<unsigned>(23 * interfaceScale) };
	sf::Vector2f helpBubbleSize{ 360 * interfaceScale,220 * interfaceScale };
	sf::Vector2f helpBubblePositionOffset{ 0,25 * interfaceScale };

	int temp = 0;

	for (RectangleWithTextAndFrames& rect : helpInformationPlayer1)
	{
		rect.setAdditionalSecondRectSize(additionalSpaceForFrame);
		rect.setFontSize(helpFontSize);
		rect.setFont(handler.font_handler["Mecha"]);
		rect.setSize(helpInformationSize);
		rect.setPosition(sf::Vector2f(player2_setpoints.x + dim.x / 2, player2_setpoints.y + YoffsetForHelpButton + temp*spaceBetweenHelpButtons));
		rect.setOutlineThickness(static_cast<float>(helpButtonOutlineThickness));
		++temp;
	}
	temp = 0;
	for (RectangleWithTextAndFrames& rect : helpInformationPlayer2)
	{
		rect.setAdditionalSecondRectSize(additionalSpaceForFrame);
		rect.setFontSize(helpFontSize);
		rect.setFont(handler.font_handler["Mecha"]);
		rect.setSize(helpInformationSize);
		rect.setPosition(sf::Vector2f(player1_setpoints.x + dim.x / 2, player1_setpoints.y + YoffsetForHelpButton + temp*spaceBetweenHelpButtons));
		rect.setOutlineThickness(static_cast<float>(helpButtonOutlineThickness));
		++temp;
	}

	helpInformationPlayer1[0].setString(langMan.getText("Press left mouse button to place the ship"));
	helpInformationPlayer2[0].setString(langMan.getText("Press left mouse button to place the ship"));
	helpInformationPlayer1[1].setString(langMan.getText("Press right mouse button to rotate the ship"));
	helpInformationPlayer2[1].setString(langMan.getText("Press right mouse button to rotate the ship"));

	helpBubble.setFont(handler.font_handler["Mecha"]);
	helpBubble.setCharacterSize(helpBubbleCharacterSize);
	helpBubble.setSize(helpBubbleSize);
	helpBubble.setTextColor(sf::Color::Black);

	helpBubble.setString(langMan.getText("Need help?"));
	helpBubble.setPosition({ player2_setpoints.x + helpBubblePositionOffset.x, player2_setpoints.y + helpBubblePositionOffset.y });
	helpBubble.setOrigin({ helpBubble.getSize().x, 0 });
	helpBubble.setScale(0);
}


