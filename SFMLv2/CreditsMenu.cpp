#include "stdafx.h"
#include "CreditsMenu.h"
#include "FontHandler.h"
#include "LanguageManager.h"



void CreditsMenu::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(rect, states);
	for (const CenteredText& text : textArray)
	{
		target.draw(text, states);
	}
	target.draw(button);
}

CreditsMenu::CreditsMenu(const sf::Vector2f &position, const std::wstring & text, unsigned charSize, const sf::Font & font, float interfaceScale, const LanguageManager& langMan)
	: button(text, static_cast<int>(charSize), font, sf::Vector2f(270*interfaceScale, 60*interfaceScale))
{
	rect.setPosition(0, 0);
	rect.setSize(sf::Vector2f(5000,5000));
	rect.setFillColor(sf::Color::Black);

	unsigned characterSize = 20 * interfaceScale;
	unsigned characterSize2 = 30 * interfaceScale;
	unsigned offset = 60 * interfaceScale;
	unsigned distanceBetweenLines = 32 * interfaceScale;


	for (CenteredText& text : textArray)
	{
		text.setFont(FontHandler::getInstance().font_handler["Mecha"]);
		text.setCharacterSize(characterSize);
	}

	textArray[0].setString(langMan.getText("Programming, Graphics, Gameplay Design"));
	textArray[0].setCharacterSize(characterSize2);
	textArray[0].setStyle(sf::Text::Bold);

	textArray[1].setString("Sebastian Safin");
	textArray[2].setString("");

	textArray[3].setString(langMan.getText("Music"));
	textArray[3].setCharacterSize(characterSize2);
	textArray[3].setStyle(sf::Text::Bold);

	textArray[4].setString("-\"Tower Defense\" by Eric Matyas (soundimage.org)");
	textArray[5].setString(L'\n' + langMan.getText("Music below is licensed under Creative Commons: By Attribution 3.0 License"));
	textArray[6].setString("http://creativecommons.org/licenses/by/3.0/");
	textArray[7].setString("\n-\"Crypto\" by Kevin MacLeod (incompetech.com)");
	textArray[8].setString("");

	textArray[9].setString(langMan.getText("Sound Effects"));
	textArray[9].setCharacterSize(characterSize2);
	textArray[9].setStyle(sf::Text::Bold);

	textArray[10].setString("-\"Explosion1\" by Eric Matyas (soundimage.org)");
	textArray[11].setString("-\"Hull Breach 3\" by Eric Matyas (soundimage.org)");
	textArray[12].setString("-Splash by blaukreuz");
	textArray[13].setString("");

	textArray[14].setString(langMan.getText("Textures"));
	textArray[14].setCharacterSize(characterSize2);
	textArray[14].setStyle(sf::Text::Bold);

	textArray[15].setString("-Granny Enchanted (http://freedigiscrapbookelements.blogspot.com)");
	textArray[16].setString("-galangpiliang (https://opengameart.org)");
	textArray[17].setString("-truezipp (https://opengameart.org)");
	textArray[18].setString("-Kenney (https://opengameart.org)");
	textArray[19].setString(L'\n' + langMan.getText("Textures below are licensed under Creative Commons: By Attribution 3.0 License"));
	textArray[20].setString("http://creativecommons.org/licenses/by/3.0/");
	textArray[21].setString("\n-Linh Pham (https://www.flaticon.com/free-icon/questions-circular-button_54591)");
	textArray[22].setString("-Scribe (https://opengameart.org/content/gui-items)");
	textArray[23].setString("-chabull (https://opengameart.org/content/ships-with-ripple-effect)");
	textArray[24].setString("");

	textArray[25].setString(langMan.getText("Libaries"));
	textArray[25].setCharacterSize(characterSize2);
	textArray[25].setStyle(sf::Text::Bold);

	textArray[26].setString("SFML by Laurent Gomila (https://www.sfml-dev.org/)");
	textArray[27].setString("");
	textArray[28].setString(langMan.getText("For more information, please read LICENSE.txt file"));
	textArray[28].setCharacterSize(characterSize2);
	textArray[28].setStyle(sf::Text::Underlined);


	unsigned i = 0;
	for (CenteredText& text : textArray)
	{
		text.setPosition(position.x, offset + i * distanceBetweenLines);
		++i;
	}

	button.setPosition(position.x, offset + (textArray.size() + 2)*distanceBetweenLines);
}

