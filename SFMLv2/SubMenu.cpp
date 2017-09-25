#include "stdafx.h"
#include "SubMenu.h"


void SubMenu::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(title, states);
	for (const PushButton& button : buttons)
		target.draw(button, states);
}

SubMenu::SubMenu(const std::wstring & title, const std::wstring & buttons_text, int title_character_size, int char_size, const sf::Vector2f & title_position,
	const sf::Vector2f & first_button_position, const sf::Vector2f& button_size, int space_between_buttons, const sf::Color& bounds_color, 
	const sf::Font & font, sf::Uint32 title_style, sf::Uint32 buttons_style)
{
	construct(title, buttons_text, title_character_size, char_size, title_position, first_button_position, button_size, space_between_buttons, bounds_color,
		font, title_style, buttons_style);
	
	isConstructed = true;
}

void SubMenu::construct(const std::wstring & title, const std::wstring & buttons_text, int title_character_size, int char_size, 
	const sf::Vector2f & title_position, const sf::Vector2f & first_button_position, const sf::Vector2f & button_size, int space_between_buttons, 
	const sf::Color & bounds_color, const sf::Font & font, sf::Uint32 title_style, sf::Uint32 buttons_style)
{
	// Guarantees that SubMenu is constructed only once
	if (isConstructed)
		return;

	isConstructed = true;

	this->title.setFont(font);
	this->title.setString(title);
	this->title.setCharacterSize(title_character_size);
	this->title.setPosition(sf::Vector2f(title_position.x - this->title.getGlobalBounds().width / 2, title_position.y));
	this->title.setStyle(title_style);

	int i = 0;
	int beg = 0, end;

	// finish if there aren't any buttons to create
	if (buttons_text == L"")
		return;

	// Creating buttons from string "buttons_text" (separated by ',')
	do {
		end = buttons_text.find(',', beg);
		if (end == std::wstring::npos) end = buttons_text.size();
		buttons.push_back(PushButton(buttons_text.substr(beg, end - beg), char_size, font, button_size, bounds_color));
		buttons[buttons.size() - 1].setPosition(first_button_position.x, first_button_position.y + i*space_between_buttons);
		buttons[buttons.size() - 1].setStyle(buttons_style);
		++i;
		beg = end + 1;
	} while (end != buttons_text.size());
}

int SubMenu::contains(const sf::Vector2f & mousepos) const
{
	int counter = 0;
	for (const PushButton& button : buttons)
	{
		if (button.contains(mousepos))
			return counter;
		++counter;
	}
	// if no button contains mousepos
	return -1;
}

bool SubMenu::contains(unsigned int number, const sf::Vector2f& mousepos) const
{
	if (number >= 0 && number < buttons.size())
		return buttons[number].contains(mousepos);
	return false;
}

void SubMenu::updateButtons()
{
	for (PushButton& button : buttons)
		button.update();
}

void SubMenu::updateButtonsWithAnimations(const sf::Time & time)
{
	for (PushButton& button : buttons)
		button.updateWithAnimations(time);
}

void SubMenu::highlightButtonContaining(const sf::Vector2f & mousepos)
{
	int tmp = contains(mousepos);
	// if there is any button which contains mousepos
	if (tmp != -1)
		buttons[tmp].highlightButton();
}

void SubMenu::highlightButton(unsigned int number)
{
	if (number >= 0 && number < buttons.size())
		buttons[number].highlightButton();
}

void SubMenu::coverButtonWithColor(unsigned int number, bool shouldApplyColor, const sf::Color & color)
{
	if (number >= 0 && number < buttons.size())
	{
		buttons[number].coverButtonWithColor(shouldApplyColor, color);
	}
}

void SubMenu::setInteriorColorAllButtons(const sf::Color & color)
{
	for (PushButton& button : buttons)
	{
		button.setInteriorColor(color);
	}
}
