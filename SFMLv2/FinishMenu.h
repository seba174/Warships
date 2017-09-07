#pragma once
#include <memory>
#include "SFML/Graphics.hpp"
#include "FinishStarsWithText.h"
#include "playersInformations.h"
#include"OptionsSubMenu.h"

class LanguageManager;


class FinishMenu
	: public sf::Drawable
{
	sf::RectangleShape background;

	std::vector<FinishStarsWithText> stars;
	std::vector<playersInformations> players;

	sf::Text title;
	sf::Text info;
	sf::Vector2f titlePos;
	int whichPlayer = 0;

	LanguageManager& langMan;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	OptionsSubMenu menuButtons;

	FinishMenu(const sf::Vector2f& dim, LanguageManager& langMan, float interfaceScale);

	void setTitle(const std::wstring& newTitle);

	void addPlayer(const playersInformations& player);

	void updateStars(const sf::Time& dt);

	void updateButtons(const sf::Time& dt, const sf::Vector2f& mousepos);

};

