#pragma once
#include "SFML/Graphics.hpp"
#include "multipleTextFrame.h"
#include "playersInformations.h"
#include "OptionsSubMenu.h"

class LanguageManager;

class StatisticsMenu
	: public sf::Drawable
{
	std::vector<MultipleTextFrame> rows;
	std::vector<playersInformations> players;
	sf::RectangleShape background;
	sf::Text title;

	LanguageManager& langMan;

	// FUNCTIONS

	void setStringsAfterAddingPlayers();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	OptionsSubMenu menuButtons;

	// dim is a dimension of a background for StatisticsMenu
	StatisticsMenu(const sf::Vector2f& dim, LanguageManager& langMan, float interfaceScale);

	void addPlayer(const playersInformations& player);

	// function updates and animates all pushButtons
	void updateButtons(const sf::Time & dt, const sf::Vector2f & mousepos);
};

