#include "FinishMenu.h"
#include "LanguageManager.h"
#include "FontHandler.h"
#include "TextureHandler.h"





void FinishMenu::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(background, states);
	target.draw(menuButtons, states);
	target.draw(title, states);
	target.draw(info, states);
	for (const FinishStarsWithText& star : stars)
		target.draw(star, states);
}

FinishMenu::FinishMenu(const sf::Vector2f & dim, LanguageManager & langMan, float interfaceScale)
	: menuButtons(langMan),
	background(dim), langMan(langMan)
{
	sf::Vector2f starSize(sf::Vector2f(50, 50)*interfaceScale);

	sf::Vector2f wholeSize(sf::Vector2f(800, 80)*interfaceScale);

	sf::Vector2f starsPos(sf::Vector2f(dim.x / 2, 400 * interfaceScale));

	int spaceBetweenButtons(130 * interfaceScale);

	sf::Vector2f menuPosition(dim.x / 2, starsPos.y + 3*spaceBetweenButtons);

	int playerFontSize = 30 * interfaceScale;
	
	int buttonFontSize = 26 * interfaceScale;

	int titleFontSize = 80 * interfaceScale;

	int infoFontSize = 35 * interfaceScale;

	sf::Vector2f push_in_opt_size(292 * interfaceScale, 60 * interfaceScale);

	const int space_between_push_buttons = 22 * interfaceScale;

	int additionalTextureOffset = 10 * interfaceScale;

	titlePos = sf::Vector2f(dim.x / 2, 100 * interfaceScale);

	stars.push_back(FinishStarsWithText(wholeSize, starSize, starsPos, playerFontSize));
	stars[stars.size() - 1].setAdditionalTextureOffset(additionalTextureOffset);
	stars.push_back(FinishStarsWithText(wholeSize, starSize, sf::Vector2f(starsPos.x,starsPos.y+spaceBetweenButtons), playerFontSize));
	stars[stars.size() - 1].setAdditionalTextureOffset(additionalTextureOffset);
	
	FontHandler& handler = FontHandler::getInstance();

	title.setCharacterSize(titleFontSize);
	title.setFont(handler.font_handler["Mecha"]);

	info.setCharacterSize(infoFontSize);
	info.setFont(handler.font_handler["Mecha"]);
	info.setString(langMan.getText("Rating of players"));
	info.setPosition(sf::Vector2f(dim.x / 2 - info.getGlobalBounds().width / 2, titlePos.y + 1.5*spaceBetweenButtons - info.getGlobalBounds().height / 2));

	background.setFillColor(sf::Color::Black);

	menuButtons.Construct(menuPosition, interfaceScale, langMan);
	menuButtons.addPushButton(langMan.getText("Statistics"), buttonFontSize, handler.font_handler["Mecha"], push_in_opt_size);
	menuButtons.addPushButton(langMan.getText("Return to Main Menu"), buttonFontSize, handler.font_handler["Mecha"], push_in_opt_size);
	menuButtons.addPushButton(langMan.getText("Quit the game"), buttonFontSize, handler.font_handler["Mecha"], push_in_opt_size);
	menuButtons.setSpaceBetweenPushButtons(space_between_push_buttons);
}

void FinishMenu::setTitle(const std::wstring & newTitle)
{
	title.setString(newTitle);
	title.setPosition(titlePos.x - title.getGlobalBounds().width / 2, titlePos.y - title.getGlobalBounds().height / 2);
}

void FinishMenu::addPlayer(const playersInformations & player)
{
	players.push_back(player);
	stars[whichPlayer].setTextString(player.getPlayerName());
	if (player.isAWinner())
		stars[whichPlayer].setAdditionalTexture(&TextureHandler::getInstance().texture_handler["cup"]);
	whichPlayer++;
}

void FinishMenu::updateStars(const sf::Time & dt)
{
	int i = 0;
	for (auto it = stars.begin(); it != stars.end(); ++it)
	{
		int numberOfStars = 0;

		int accuracy = players[i].returnAccuracy();

		if (accuracy >= 70)
			numberOfStars = 5;
		else if (accuracy >= 60)
			numberOfStars = 4;
		else if (accuracy >= 50)
			numberOfStars = 3;
		else if (accuracy >= 40)
			numberOfStars = 2;
		else numberOfStars = 1;

		it->clickStars(numberOfStars, dt);
		++i;
	}
}

void FinishMenu::updateButtons(const sf::Time & dt, const sf::Vector2f & mousepos)
{
	menuButtons.highlightButtonContaining(mousepos);
	menuButtons.updateWithAnimations(dt);
}
