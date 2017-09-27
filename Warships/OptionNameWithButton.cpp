#include "stdafx.h"
#include "OptionNameWithButton.h"


void OptionNameWithButton::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	//target.draw(boundRectangle, states);
	target.draw(optionName, states);
	target.draw(button, states);
}

void OptionNameWithButton::setTextPosition(float x, float y)
{
	optionName.setPosition(x - size.x / 2, y - ( optionName.getGlobalBounds().height / 2));
}

void OptionNameWithButton::setButtonPosition(float x, float y)
{
	button.setPosition(x + size.x / 2 - button.getSize().x / 2, y);
}

void OptionNameWithButton::setBoundRectanglePosition()
{
	boundRectangle.setPosition(optionName.getPosition().x + size.x / 2 - boundRectangle.getSize().x / 2,
		optionName.getPosition().y + optionName.getGlobalBounds().height / 1.2f - boundRectangle.getSize().y / 2);
}

OptionNameWithButton::OptionNameWithButton(const std::wstring & optionName, const sf::Font & nameFont, int nameCharacterSize, const sf::Vector2f & size,
	const std::string & options_list, const sf::Font & buttonFont, int buttonCharacterSize, LanguageManager& langMan, const sf::Vector2f & button_size, const sf::Color & bounds_color)
	: button(options_list, buttonFont, buttonCharacterSize, langMan,button_size, bounds_color), size(size)
{

	sf::Vector2f boundRectangleProportions(1.05f, 0.9f);


	this->optionName.setFont(nameFont);
	this->optionName.setCharacterSize(nameCharacterSize);
	this->optionName.setString(optionName);
	boundRectangle.setSize(sf::Vector2f(boundRectangleProportions.x*size.x, boundRectangleProportions.y*size.y));
	boundRectangle.setFillColor(sf::Color::Black);
	setPosition(0, 0);
}

void OptionNameWithButton::setPosition(float x, float y)
{
	setTextPosition(x, y);
	setButtonPosition(x, y);
	setBoundRectanglePosition();
}

void OptionNameWithButton::setPosition(const sf::Vector2f & position)
{
	setTextPosition(position.x, position.y);
	setButtonPosition(position.x, position.y);
	setBoundRectanglePosition();
}


