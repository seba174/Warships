#include "stdafx.h"
#include "OptionsSubMenu.h"


void OptionsSubMenu::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(boundRectangle, states);
	for (const OptionNameWithButton& but : options_buttons)
		target.draw(but, states);
	
	for (const PushButton& but : push_buttons)
		target.draw(but, states);
}

void OptionsSubMenu::updatePushButtons()
{
	int y = static_cast<int>(position.y + additionalPushButtonOffset + options_buttons.size()*spaceBetweenButtons);
	int tmp = push_buttons.size();
	for (PushButton& but : push_buttons)
	{
		but.setPosition(position.x - ((0.5f*but.getSize().x) + (0.5f*spaceBetweenVertically))*(tmp - 1), static_cast<float>(y + additionalSpaceBetweenOptionsAndPushButtons));
		tmp -= 2;
	}
}

void OptionsSubMenu::updateBoundRectangle()
{
	boundRectangle.setSize(sf::Vector2f(options_buttons[options_buttons.size() - 1].getBoundRectangleSize().x,
		spaceBetweenButtons*(options_buttons.size() - 1) + options_buttons[options_buttons.size() - 1].getBoundRectangleSize().y) + additionalBackgroundSize);
	boundRectangle.setPosition(options_buttons[0].getBoundRectanglePosition());
}

OptionsSubMenu::OptionsSubMenu(const sf::Vector2f & position_of_first, int spaceBetweenButtons, LanguageManager& langMan)
	:langMan(langMan), additionalPushButtonOffset(0)
{
	spaceBetweenVertically = 0;
	this->position = position_of_first;
	this->spaceBetweenButtons = spaceBetweenButtons;
	additionalSpaceBetweenOptionsAndPushButtons = 0;
	//test
	boundRectangle.setFillColor(sf::Color::Black);
	isConstructed = true;
}

OptionsSubMenu::OptionsSubMenu(LanguageManager& langMan)
	:langMan(langMan), additionalPushButtonOffset(0)
{
	additionalBackgroundSize = sf::Vector2f(0, 0);
	spaceBetweenVertically = 0;
	additionalSpaceBetweenOptionsAndPushButtons = 0;
	boundRectangle.setFillColor(sf::Color(0,0,0,200));
	isConstructed = false;
}

void OptionsSubMenu::Construct(const sf::Vector2f & position_of_first, int spaceBetweenButtons, LanguageManager& langMan)
{
	if (isConstructed)
		return;
	
	this->langMan = langMan;
	this->position = position_of_first;
	this->spaceBetweenButtons = spaceBetweenButtons;
	isConstructed = true;
}

void OptionsSubMenu::addPushButton(const std::wstring & displayed_text, int char_size, const sf::Font & font, sf::Vector2f size, 
	const sf::Color & bounds_color, int line_thickness)
{
	push_buttons.push_back(PushButton(displayed_text, char_size, font, size, bounds_color, line_thickness));
	updatePushButtons();
}

void OptionsSubMenu::addOptionNameWithButton(const std::wstring & optionName, const sf::Font & nameFont, int nameCharacterSize, 
	const sf::Vector2f & size, const std::string & options_list, const sf::Font & buttonFont, int buttonCharacterSize, const sf::Vector2f & button_size, 
	const sf::Color & bounds_color)
{
	options_buttons.push_back(OptionNameWithButton(optionName, nameFont, nameCharacterSize, size, options_list, buttonFont, buttonCharacterSize, langMan,
		button_size, bounds_color));
	options_buttons[options_buttons.size() - 1].setPosition(position.x, position.y + (options_buttons.size() - 1)*spaceBetweenButtons);
	updateBoundRectangle();
	updatePushButtons();
}

bool OptionsSubMenu::PushButtonContains(unsigned int number, const sf::Vector2f & mousepos) const
{
	if (number >= 0 && number < push_buttons.size())
		if (push_buttons[number].contains(mousepos))
			return true;
	return false;
}

bool OptionsSubMenu::OptionNameWithButtonContains(unsigned int number, const sf::Vector2f & mousepos) const
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

std::string OptionsSubMenu::getDisplayedOption(unsigned int number)
{
	if (number >= 0 && number < options_buttons.size())
		return options_buttons[number].getDisplayedOption();
	return "";
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

void OptionsSubMenu::setDisplayedOption(unsigned int number, std::string newDisplayedOption)
{
	if (number >= 0 && number < options_buttons.size())
	{
		options_buttons[number].setDisplayedOption(newDisplayedOption);
	}
}

void OptionsSubMenu::coverPushButtonWithColor(unsigned int number, bool shouldApplyColor, const sf::Color & color)
{
	if (number >= 0 && number < push_buttons.size())
	{
		push_buttons[number].coverButtonWithColor(shouldApplyColor,color);
	}
}


void OptionsSubMenu::setSpaceBetweenPushButtons(int space)
{
	spaceBetweenVertically = space;
	updatePushButtons();
}

void OptionsSubMenu::setArrowsBlockAndDisplayedString(unsigned int number, bool arrowsBlocked, const std::string & displayed)
{
	if (number >= 0 && number < options_buttons.size())
	{
		options_buttons[number].setArrowsBlockAndDisplayedString(arrowsBlocked, displayed);
	}
}

void OptionsSubMenu::setInteriorColorAllPushButtons(const sf::Color & color)
{
	for (PushButton& button : push_buttons)
		button.setInteriorColor(color);
}

void OptionsSubMenu::shouldOptionButtonDisplayOnlyText(unsigned int number, bool whatToDo)
{
	if (number >= 0 && number < options_buttons.size())
	{
		options_buttons[number].shouldDisplayOnlyText(whatToDo);
	}
}

void OptionsSubMenu::setOutlineThickness(unsigned int number, float outLine)
{
	if (number >= 0 && number < options_buttons.size())
	{
		options_buttons[number].setOutlineThickness(outLine);
	}
}

void OptionsSubMenu::disableAnimation(unsigned int number, bool shouldDisable)
{
	if (number >= 0 && number < options_buttons.size())
	{
		options_buttons[number].disableAnimation(shouldDisable);
	}
}

float OptionsSubMenu::getOutlineThickness(unsigned int number) const
{
	if (number >= 0 && number < options_buttons.size())
	{
		return options_buttons[number].getOutlineThickness();
	}
	else
		return 0;
}

void OptionsSubMenu::setDictionaryDisabledBool(unsigned int number, bool val)
{
	if (number >= 0 && number < options_buttons.size())
	{
		options_buttons[number].setDictionaryDisabledBool(val);
	}
}
