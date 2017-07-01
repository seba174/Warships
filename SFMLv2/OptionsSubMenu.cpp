#include "OptionsSubMenu.h"



void OptionsSubMenu::draw(sf::RenderTarget & target, sf::RenderStates states) const
{

	for (const OptionNameWithButton& but : options_buttons)
		target.draw(but, states);
	
	for (const PushButton& but : push_buttons)
		target.draw(but, states);
}

void OptionsSubMenu::updatePushButtons()
{
	int y = position.y + options_buttons.size()*spaceBetweenButtons;
	int tmp = push_buttons.size();
	for (PushButton& but : push_buttons)
	{
		but.setPosition(position.x - ((0.5*but.getSize().x) + (0.5*spaceBetweenVertically))*(tmp - 1), y + additionalSpaceBetweenOptionsAndPushButtons);
		tmp -= 2;
	}
}

OptionsSubMenu::OptionsSubMenu(const sf::Vector2f & position_of_first, int spaceBetweenButtons)
{
	this->position = position_of_first;
	this->spaceBetweenButtons = spaceBetweenButtons;
	additionalSpaceBetweenOptionsAndPushButtons = 0;
	isConstructed = true;
}

OptionsSubMenu::OptionsSubMenu()
{
	additionalSpaceBetweenOptionsAndPushButtons = 0;
	isConstructed = false;
}

void OptionsSubMenu::Construct(const sf::Vector2f & position_of_first, int spaceBetweenButtons)
{
	if (isConstructed)
		return;

	this->position = position_of_first;
	this->spaceBetweenButtons = spaceBetweenButtons;
	isConstructed = true;
}

void OptionsSubMenu::addPushButton(const std::string & displayed_text, int char_size, const sf::Font & font, sf::Vector2f size, 
	const sf::Color & bounds_color, int line_thickness)
{
	push_buttons.push_back(PushButton(displayed_text, char_size, font, size, bounds_color, line_thickness));
	updatePushButtons();
}

void OptionsSubMenu::addOptionNameWithButton(const std::string & optionName, const sf::Font & nameFont, int nameCharacterSize, 
	const sf::Vector2f & size, const std::string & options_list, const sf::Font & buttonFont, int buttonCharacterSize, const sf::Vector2f & button_size, 
	const sf::Color & bounds_color)
{
	options_buttons.push_back(OptionNameWithButton(optionName, nameFont, nameCharacterSize, size, options_list, buttonFont, buttonCharacterSize, 
		button_size, bounds_color));
	options_buttons[options_buttons.size() - 1].setPosition(position.x, position.y + (options_buttons.size() - 1)*spaceBetweenButtons);
	updatePushButtons();
}

bool OptionsSubMenu::PushButtonContains(int number, const sf::Vector2f & mousepos) const
{
	if (number >= 0 && number < push_buttons.size())
		if (push_buttons[number].contains(mousepos))
			return true;
	return false;
}

bool OptionsSubMenu::OptionNameWithButtonContains(int number, const sf::Vector2f & mousepos) const
{
	if (number >= 0 && number < options_buttons.size())
		if (options_buttons[number].buttonContains(mousepos))
			return true;
	return false;
}

void OptionsSubMenu::highlightButtonContaining(const sf::Vector2f & mousepos)
{
	for (OptionNameWithButton& but : options_buttons)
	{
		if (but.buttonContains(mousepos))
			but.highlightButton();
		if (but.leftButtonContains(mousepos))
			but.highlightLeftButton();
		if (but.rightButtonContains(mousepos))
			but.highlightRightButton();
	}

	for (PushButton& but : push_buttons)
		if (but.contains(mousepos))
			but.highlightButton();
}

void OptionsSubMenu::updateWithAnimations(const sf::Time & time)
{
	for (OptionNameWithButton& but : options_buttons)
	{
		but.updateWithAnimations(time);
		but.updateArrows();
	}

	for (PushButton& but : push_buttons)
		but.updateWithAnimations(time);
}

void OptionsSubMenu::clickArrowContaining(const sf::Vector2f & mousepos)
{
	for (OptionNameWithButton& but : options_buttons)
	{
		if (but.leftButtonContains(mousepos))
			but.clickLeftButton();
		if (but.rightButtonContains(mousepos))
			but.clickRightButton();
	}
}
