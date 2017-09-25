#include "stdafx.h"
#include "AdditionalSubMenu.h"

void AdditionalSubMenu::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(background, states);
	target.draw(backgroundForSubMenu, states);
	SubMenu::draw(target, states);
}

AdditionalSubMenu::AdditionalSubMenu(const sf::Vector2f & backgroundSize, const sf::Vector2f & backgroundForSubMenuSize,
	const sf::Vector2f & backgroundForSubMenuPosition, const sf::Color& backgroundForSubMenuColor, const sf::Color & backgroundColor,
	const sf::Vector2f & backgroundPosition, const std::wstring & title, const std::wstring & buttons_text, int title_character_size, int char_size,
	const sf::Vector2f & title_position, const sf::Vector2f & first_button_position, const sf::Vector2f & button_size, int space_between_buttons, 
	const sf::Color & bounds_color, const sf::Font & font, float interfaceScale, sf::Uint32 title_style, sf::Uint32 buttons_style)
{
	construct(backgroundSize, backgroundForSubMenuSize, backgroundForSubMenuPosition, backgroundForSubMenuColor, backgroundColor, backgroundPosition,
		title, buttons_text, title_character_size, char_size, title_position, first_button_position, button_size, space_between_buttons, bounds_color,
		font, interfaceScale, title_style, buttons_style);

	SubMenu::isConstructed = true;
}

void AdditionalSubMenu::construct(const sf::Vector2f & backgroundSize, const sf::Vector2f & backgroundForSubMenuSize,
	const sf::Vector2f & backgroundForSubMenuPosition, const sf::Color & backgroundForSubMenuColor, const sf::Color & backgroundColor,
	const sf::Vector2f & backgroundPosition, const std::wstring & title, const std::wstring & buttons_text, int title_character_size, int char_size,
	const sf::Vector2f & title_position, const sf::Vector2f & first_button_position, const sf::Vector2f & button_size, int space_between_buttons,
	const sf::Color & bounds_color, const sf::Font & font, float interfaceScale, sf::Uint32 title_style, sf::Uint32 buttons_style)
{
	int spaceFromBackgroundForSubMenuEdge = static_cast<int>(10 * interfaceScale);

	if (isConstructed)
		return;

	constructBackgrounds(backgroundSize, backgroundForSubMenuSize, backgroundForSubMenuPosition, backgroundForSubMenuColor, backgroundColor, backgroundPosition);
	SubMenu::construct(title, buttons_text, title_character_size, char_size,
		sf::Vector2f(backgroundForSubMenuPosition.x, backgroundForSubMenu.getPosition().y + spaceFromBackgroundForSubMenuEdge),
		sf::Vector2f(backgroundForSubMenuPosition.x, backgroundForSubMenu.getPosition().y + spaceFromBackgroundForSubMenuEdge + space_between_buttons + title_character_size),
		button_size, space_between_buttons, bounds_color, font, title_style, buttons_style);

	SubMenu::isConstructed = true;
}

AdditionalSubMenu::AdditionalSubMenu() 
	: SubMenu()
{
}

void AdditionalSubMenu::constructBackgrounds(const sf::Vector2f & backgroundSize, const sf::Vector2f & backgroundForSubMenuSize, 
	const sf::Vector2f & backgroundForSubMenuPosition, const sf::Color& backgroundForSubMenuColor, const sf::Color & backgroundColor, 
	const sf::Vector2f & backgroundPosition)
{
	background.setSize(backgroundSize);
	background.setPosition(backgroundPosition);
	background.setFillColor(backgroundColor);

	backgroundForSubMenu.setSize(backgroundForSubMenuSize);
	backgroundForSubMenu.setPosition(backgroundForSubMenuPosition.x - backgroundForSubMenu.getSize().x / 2,
		backgroundForSubMenuPosition.y - backgroundForSubMenu.getSize().y / 2);
	backgroundForSubMenu.setFillColor(backgroundForSubMenuColor);
}
