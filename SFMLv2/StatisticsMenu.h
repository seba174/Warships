#pragma once
#include "SFML/Graphics.hpp"
#include "multipleTextFrame.h"
#include "playersInformations.h"
#include "OptionsSubMenu.h"

class LanguageManager;

class StatisticsMenu
	: public sf::Drawable
{
	std::vector<multipleTextFrame> rows;
	std::vector<playersInformations> players;
	sf::RectangleShape background;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	OptionsSubMenu menuButtons;

	StatisticsMenu(const sf::Vector2f& dim, LanguageManager& langMan, float interfaceScale);

};

