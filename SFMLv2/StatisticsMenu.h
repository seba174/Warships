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

	// returns a wstring representing given value with only 2 decimal places
	// e.g. function returns 70.51 for value 70.515040
	std::wstring floatWith2DecimalPlaces(float value);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	OptionsSubMenu menuButtons;

	// dim is a dimension of a background for StatisticsMenu
	StatisticsMenu(const sf::Vector2f& dim, LanguageManager& langMan, float interfaceScale);

	void addPlayer(const playersInformations& player);

	// function updates and animates all pushButtons
	void updateButtons(const sf::Time & dt, const sf::Vector2f & mousepos);
};

