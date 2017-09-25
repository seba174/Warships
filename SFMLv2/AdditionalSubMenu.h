#pragma once
#include "SubMenu.h"

class AdditionalSubMenu :
	public SubMenu
{
	sf::RectangleShape background;
	sf::RectangleShape backgroundForSubMenu;

		// FUNCTIONS

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	// creates background rectangle, which covers up screen
	// creates backgroundForSubMenu, which is used as a background for SubMenu class
	void constructBackgrounds(const sf::Vector2f& backgroundSize, const sf::Vector2f& backgroundForSubMenuSize, const sf::Vector2f& backgroundForSubMenuPosition,
		const sf::Color& backgroundColor, const sf::Color& backgroundForSubMenuColor, const sf::Vector2f& backgroundPosition = sf::Vector2f(0, 0));

public:
	// strings in buttons_text (which contains information about text on buttons) must be separated with ',' (comma)!
	// WARNING! 
	// Position of title and button is based on backgroundForSubMenuPosition!
	// first_button_position is not used!
	AdditionalSubMenu(const sf::Vector2f & backgroundSize, const sf::Vector2f & backgroundForSubMenuSize,
		const sf::Vector2f & backgroundForSubMenuPosition, const sf::Color& backgroundForSubMenuColor, const sf::Color & backgroundColor,
		const sf::Vector2f & backgroundPosition, const std::wstring& title, const std::wstring& buttons_text, int title_character_size, int char_size,
		const sf::Vector2f& title_position, const sf::Vector2f& first_button_position, const sf::Vector2f& button_size, int space_between_buttons,
		const sf::Color& bounds_color, const sf::Font& font, float interfaceScale, sf::Uint32 title_style = sf::Text::Regular, sf::Uint32 buttons_style = sf::Text::Regular);

	// acts like constructor, may be run only once
	// strings in buttons_text (which contains information about text on buttons) must be separated with ',' (comma)!
	// WARNING!
	// Position of title and button is based on backgroundForSubMenuPosition!
	// first_button_position is not used!
	void construct(const sf::Vector2f & backgroundSize, const sf::Vector2f & backgroundForSubMenuSize,
		const sf::Vector2f & backgroundForSubMenuPosition, const sf::Color& backgroundForSubMenuColor, const sf::Color & backgroundColor,
		const sf::Vector2f & backgroundPosition, const std::wstring& title, const std::wstring& buttons_text, int title_character_size, int char_size,
		const sf::Vector2f& title_position, const sf::Vector2f& first_button_position, const sf::Vector2f& button_size, int space_between_buttons,
		const sf::Color& bounds_color, const sf::Font& font, float interfaceScale, sf::Uint32 title_style = sf::Text::Regular,
		sf::Uint32 buttons_style = sf::Text::Regular);

	// default constructor
	// sets isConstructed value false
	// You have to use construct function in order to have it working properly!
	AdditionalSubMenu();


};

