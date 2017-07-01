#include "OptionButton.h"
#include <iostream>


void OptionButton::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(bound_rectangle, states);
	target.draw(leftbutton, states);
	target.draw(rightbutton, states);
	target.draw(current_displayed_option, states);
}


OptionButton::OptionButton(const std::string & options_list, const sf::Font& font, int characterSize, const sf::Vector2f& size, 
	const sf::Color& bounds_color)
	: isPressed(false), isLeftButtonHighlighted(false), isRightButtonHighlighted(false), shouldUpdateAnimations(false)
{
	current_option_number = 0;
	usableTime = sf::milliseconds(100);
	animationTime = sf::milliseconds(300);
	animationScale = 1.1;

	TextureHandler& texture = TextureHandler::getInstance();

	int number = 0;
	int beg = 0, end;

	// Counting amount of different options (separated by ',') and saving it to "number"
	do {
		end = options_list.find(',', beg);
		if (end == std::string::npos) end = options_list.size();
		++number;
		beg = end + 1;
	} while (end != options_list.size());	
	
	options = std::make_unique<std::string[]>(number);
	
	number_of_options = number;

	// Saving strings to the array
	beg = 0; number = 0;
	do {
		end = options_list.find(',', beg);
		if (end == std::string::npos) end = options_list.size();
		options[number++] = options_list.substr(beg, end - beg);
		beg = end + 1;
	} while (end != options_list.size());

	bound_rectangle.setSize(size);
	bound_rectangle.setFillColor(sf::Color(255,255,255,200));
	
	// default part which left or right button occupies in whole button
	float scale = 0.15f;
	
	leftbutton.setSize(sf::Vector2f(size.x*scale, size.y));
	rightbutton.setSize(sf::Vector2f(size.x*scale, size.y));
	rightbutton.setTexture(&texture.texture_handler["rightarrow"]);
	leftbutton.setTexture(&texture.texture_handler["leftarrow"]);

	sf::IntRect rect = rightbutton.getTextureRect();
	leftbutton.setTextureRect(sf::IntRect(rect.left + rect.width / 2, rect.top, rect.width / 2, rect.height));
	rightbutton.setTextureRect(sf::IntRect(rect.left + rect.width / 2, rect.top, rect.width / 2, rect.height));
	setPosition(0, 0);

	current_displayed_option.setFont(font);
	current_displayed_option.setCharacterSize(characterSize);
	current_displayed_option.setString(options[0]);
	setTextPosition();

	bound_rectangle.setOutlineThickness(2);
	bound_rectangle.setOutlineColor(bounds_color);

	//bound_rectangle.setOutlineColor(sf::Color::Red);
	bound_rectangle.setTexture(&texture.texture_handler["test"]);
}

void OptionButton::setTextPosition()
{
	float newScale = scale;
	newScale += addScale(current_displayed_option.getString());

	current_displayed_option.setPosition(bound_rectangle.getPosition().x + bound_rectangle.getSize().x / 2 - current_displayed_option.getGlobalBounds().width / 2,
		bound_rectangle.getPosition().y + bound_rectangle.getSize().y / 2 - current_displayed_option.getGlobalBounds().height / newScale);
}

float OptionButton::addScale(const std::string & str)
{
	float tmp = 0;
	if (str.find('y') != std::string::npos || str.find('g') != std::string::npos || str.find('j') != std::string::npos || str.find('p') != std::string::npos)
		tmp = 0.18;
	return tmp;
}

void OptionButton::setPosition(float x, float y)
{
	pos = sf::Vector2f(x, y);
	bound_rectangle.setPosition(x - bound_rectangle.getSize().x / 2, y - bound_rectangle.getSize().y / 2);
	rightbutton.setPosition(x + bound_rectangle.getSize().x / 2 - rightbutton.getGlobalBounds().width, bound_rectangle.getPosition().y);
	leftbutton.setPosition(bound_rectangle.getPosition());
	setTextPosition();
}

void OptionButton::setPosition(const sf::Vector2f & position)
{
	pos = position;
	bound_rectangle.setPosition(position.x - bound_rectangle.getSize().x / 2, position.y - bound_rectangle.getSize().y / 2);
	rightbutton.setPosition(position.x + bound_rectangle.getSize().x / 2 - rightbutton.getGlobalBounds().width, bound_rectangle.getPosition().y);
	leftbutton.setPosition(bound_rectangle.getPosition());
	setTextPosition();
}

void OptionButton::updatePosition()
{
	float newScale = scale;
	newScale += addScale(current_displayed_option.getString());

	bound_rectangle.setPosition(pos.x - bound_rectangle.getGlobalBounds().width / 2, pos.y - bound_rectangle.getGlobalBounds().height / 2);
	current_displayed_option.setPosition(pos.x - current_displayed_option.getGlobalBounds().width / 2, pos.y - current_displayed_option.getGlobalBounds().height / newScale);
	leftbutton.setPosition(bound_rectangle.getPosition());

	rightbutton.setPosition(bound_rectangle.getPosition().x + bound_rectangle.getGlobalBounds().width - 2 * bound_rectangle.getOutlineThickness()
		- rightbutton.getGlobalBounds().width, pos.y - bound_rectangle.getGlobalBounds().height / 2);
}

void OptionButton::updateArrows()
{
	// rightbutton and leftbutton have textures of the same size
	sf::IntRect rect = leftbutton.getTextureRect();

	if (isLeftButtonHighlighted)
		leftbutton.setTextureRect(sf::IntRect(0, 0, rect.width, rect.height));
	else
		leftbutton.setTextureRect(sf::IntRect(0 + rect.width, 0, rect.width, rect.height));

	if (isRightButtonHighlighted)
		rightbutton.setTextureRect(sf::IntRect(0, 0, rect.width, rect.height));
	else
		rightbutton.setTextureRect(sf::IntRect(0 + rect.width, 0, rect.width, rect.height));

	isLeftButtonHighlighted = false;
	isRightButtonHighlighted = false;
}

void OptionButton::clickLeftButton()
{
	--current_option_number;
	if (current_option_number < 0)
		current_option_number = number_of_options - 1;
	current_displayed_option.setString(options[current_option_number]);
	setTextPosition();
}

void OptionButton::clickRightButton()
{
	++current_option_number;
	if (current_option_number == number_of_options)
		current_option_number = 0;
	current_displayed_option.setString(options[current_option_number]);
	setTextPosition();
}

void OptionButton::updateWithAnimations(const sf::Time & time)
{
	if (isPressed)
	{
		isPressed = false;
		setScale(animationScale, animationScale);
		shouldUpdateAnimations = true;
		//bound_rectangle.setFillColor(sf::Color(4, 183, 219, 150));
	}
	else
	{
		sf::Time g = sf::microseconds(time.asMicroseconds() / (animationTime.asSeconds() * 10));
		usableTime -= g;
		if (usableTime.asMilliseconds() > 0 && shouldUpdateAnimations)
		{
			// 10*(baseAnimationScale - 1) is a fracitonal part * 10
			setScale(1 + 10 * (animationScale - 1)*usableTime.asSeconds(), 1 + 10 * (animationScale - 1)*usableTime.asSeconds());
		}
		else
		{
			setScale(1, 1);
			usableTime = sf::milliseconds(100);
			shouldUpdateAnimations = false;
		}

		//bound_rectangle.setFillColor(sf::Color::Transparent);
	}
	updatePosition();
}

void OptionButton::setScale(float x, float y)
{
	bound_rectangle.setScale(x, y);
	current_displayed_option.setScale(x, y);
	leftbutton.setScale(x, y);
	rightbutton.setScale(x, y);
}

