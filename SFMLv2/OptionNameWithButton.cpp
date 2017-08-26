#include "OptionNameWithButton.h"


void OptionNameWithButton::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(optionName, states);
	target.draw(button, states);
}

void OptionNameWithButton::setTextPosition(float x, float y)
{
	optionName.setPosition(x - size.x / 2, y - optionName.getGlobalBounds().height / 1.1);
}

void OptionNameWithButton::setButtonPosition(float x, float y)
{
	button.setPosition(x + size.x / 2 - button.getSize().x / 2, y);
}

OptionNameWithButton::OptionNameWithButton(const std::wstring & optionName, const sf::Font & nameFont, int nameCharacterSize, const sf::Vector2f & size,
	const std::string & options_list, const sf::Font & buttonFont, int buttonCharacterSize, LanguageManager& langMan, const sf::Vector2f & button_size, const sf::Color & bounds_color)
	: button(options_list, buttonFont, buttonCharacterSize, langMan,button_size, bounds_color), size(size)
{
	this->optionName.setFont(nameFont);
	this->optionName.setCharacterSize(nameCharacterSize);
	this->optionName.setString(optionName);
	setPosition(0, 0);
}

void OptionNameWithButton::setPosition(float x, float y)
{
	setTextPosition(x, y);
	setButtonPosition(x, y);
}

void OptionNameWithButton::setPosition(const sf::Vector2f & position)
{
	setTextPosition(position.x, position.y);
	setButtonPosition(position.x, position.y);
}


