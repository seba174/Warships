#include "StatisticsMenu.h"
#include "LanguageManager.h"


StatisticsMenu::StatisticsMenu(const sf::Vector2f & dim, LanguageManager & langMan, float interfaceScale)
	:background(dim), menuButtons(langMan)
{
	background.setFillColor(sf::Color::Black);


}
