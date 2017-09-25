#include "stdafx.h"
#include "StatisticsMenu.h"
#include "FontHandler.h"
#include "LanguageManager.h"
#include "UtilityFunctions.h"


void StatisticsMenu::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(background, states);
	target.draw(title, states);
	for (const MultipleTextFrame& row : rows)
	{
		target.draw(row, states);
	}
	target.draw(menuButtons, states);
}

void StatisticsMenu::setStringsAfterAddingPlayers()
{
	rows[0].setStrings(std::list<std::wstring>(std::initializer_list<std::wstring>({ L"",players[0].getPlayerName(),players[1].getPlayerName() })));

	rows[1].setStrings(std::list<std::wstring>(std::initializer_list<std::wstring>(
	{ langMan.getText("Total number of shots"),std::to_wstring(players[0].returnTotalShots()),std::to_wstring(players[1].returnTotalShots()) })));
	rows[2].setStrings(std::list<std::wstring>(std::initializer_list<std::wstring>(
	{ langMan.getText("Total number of hits"),std::to_wstring(players[0].returnTotalHits()),std::to_wstring(players[1].returnTotalHits()) })));
	rows[3].setStrings(std::list<std::wstring>(std::initializer_list<std::wstring>(
	{ langMan.getText("Accuracy"),floatWith2DecimalPlaces(players[0].returnAccuracy(), std::wstring()) + L'%',floatWith2DecimalPlaces(players[1].returnAccuracy(), std::wstring()) + L'%' })));
	rows[4].setStrings(std::list<std::wstring>(std::initializer_list<std::wstring>(
	{ langMan.getText("The biggest hit series"),std::to_wstring(players[0].returnMaximumShots()),std::to_wstring(players[1].returnMaximumShots()) })));
	rows[5].setStrings(std::list<std::wstring>(std::initializer_list<std::wstring>(
	{ langMan.getText("The biggest miss series"),std::to_wstring(players[0].returnMaximumMisses()),std::to_wstring(players[1].returnMaximumMisses()) })));
}

StatisticsMenu::StatisticsMenu(const sf::Vector2f & dim, LanguageManager & langMan, float interfaceScale)
	:background(dim), menuButtons(langMan), langMan(langMan)
{
	int numberOfRows = 6;
	int numberOfColumns = 3;

	background.setFillColor(sf::Color::Black);

	sf::Vector2f titlePos = sf::Vector2f(dim.x / 2, 100 * interfaceScale);

	sf::Vector2f wholeSize(sf::Vector2f(350, 60)*interfaceScale);

	sf::Vector2f starsPos(sf::Vector2f(dim.x / 2, 250 * interfaceScale));

	int spaceBetweenButtons(static_cast<int>(90 * interfaceScale));

	sf::Vector2f menuPosition(dim.x / 2, starsPos.y + (numberOfRows + 0.5f)*spaceBetweenButtons);

	int playerFontSize = static_cast<int>(30 * interfaceScale);

	int buttonFontSize = static_cast<int>(26 * interfaceScale);

	int titleFontSize = static_cast<int>(80 * interfaceScale);

	sf::Vector2f push_in_opt_size(292 * interfaceScale, 60 * interfaceScale);

	const int space_between_push_buttons = static_cast<int>(22 * interfaceScale);


	FontHandler& handler = FontHandler::getInstance();

	title.setCharacterSize(titleFontSize);
	title.setFont(handler.font_handler["Mecha"]);
	title.setString(langMan.getText("Statistics"));
	title.setPosition(titlePos.x - title.getGlobalBounds().width / 2, titlePos.y - title.getGlobalBounds().height / 2);

	menuButtons.Construct(menuPosition, static_cast<int>(interfaceScale), langMan);
	menuButtons.addPushButton(langMan.getText("Back"), buttonFontSize, handler.font_handler["Mecha"], push_in_opt_size);
	menuButtons.addPushButton(langMan.getText("Return to Main Menu"), buttonFontSize, handler.font_handler["Mecha"], push_in_opt_size);
	menuButtons.addPushButton(langMan.getText("Quit the game"), buttonFontSize, handler.font_handler["Mecha"], push_in_opt_size);
	menuButtons.setSpaceBetweenPushButtons(space_between_push_buttons);


	for (int i = 0; i < numberOfRows; ++i)
		rows.push_back(MultipleTextFrame(numberOfColumns));

	int temp = 0;
	for (MultipleTextFrame& frame : rows)
	{
		frame.setFont(handler.font_handler["Mecha"]);
		frame.setFontSize(static_cast<float>(playerFontSize));
		frame.setSize(wholeSize);
		frame.setPosition(sf::Vector2f(starsPos.x, starsPos.y + temp*spaceBetweenButtons));
		++temp;
	}

	rows[0].setStrings(std::list<std::wstring>(std::initializer_list<std::wstring>({ L"",L"",L"" })));
	rows[1].setStrings(std::list<std::wstring>(std::initializer_list<std::wstring>({ langMan.getText("Total number of shots"),L"",L"" })));
	rows[2].setStrings(std::list<std::wstring>(std::initializer_list<std::wstring>({ langMan.getText("Total number of hits"),L"",L"" })));
	rows[3].setStrings(std::list<std::wstring>(std::initializer_list<std::wstring>({ langMan.getText("Accuracy"),L"",L"" })));
	rows[4].setStrings(std::list<std::wstring>(std::initializer_list<std::wstring>({ langMan.getText("The biggest hit series"),L"",L"" })));
	rows[5].setStrings(std::list<std::wstring>(std::initializer_list<std::wstring>({ langMan.getText("The biggest miss series"),L"",L"" })));
}

void StatisticsMenu::addPlayer(const playersInformations & player)
{
	players.push_back(player);
	if (players.size() == 2)
		setStringsAfterAddingPlayers();
}

void StatisticsMenu::updateButtons(const sf::Time & dt, const sf::Vector2f & mousepos)
{
	menuButtons.highlightButtonContaining(mousepos);
	menuButtons.updateWithAnimations(dt);
}

