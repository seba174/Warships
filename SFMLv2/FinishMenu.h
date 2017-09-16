#pragma once
#include <memory>
#include "SFML/Graphics.hpp"
#include "FinishStarsWithText.h"
#include "playersInformations.h"
#include "OptionsSubMenu.h"

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

	// dim is a dimension of a background for FinishMenu
	FinishMenu(const sf::Vector2f& dim, LanguageManager& langMan, float interfaceScale);

	// sets title of FinishMenu
	void setTitle(const std::wstring& newTitle);

	void addPlayer(const playersInformations& player);

	// function animates shining of the stars
	// mapSize of stars to shine for every player is based on the player's accuracy
	void updateStars(const sf::Time& dt);

	// function updates and animates all pushButtons
	void updateButtons(const sf::Time& dt, const sf::Vector2f& mousepos);

};

