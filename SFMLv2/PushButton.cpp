#include "PushButton.h"



void PushButton::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(bound_rectangle, states);
	target.draw(displayed_text, states);
}

void PushButton::setTextPosition()
{
	displayed_text.setPosition(bound_rectangle.getPosition().x + bound_rectangle.getSize().x / 2 - displayed_text.getGlobalBounds().width / 2,
		bound_rectangle.getPosition().y + bound_rectangle.getSize().y / 2 - displayed_text.getGlobalBounds().height / 1.1);
}

PushButton::PushButton(const std::string& text, int char_size, const sf::Font& font, sf::Vector2f size, const sf::Color& bounds_color,
	 int line_thickness)
	: isPressed(false), shouldUpdateAnimations(false)
{
	TextureHandler& texutreHandler = TextureHandler::getInstance();

	outlineColor = bounds_color;
	animationTime = sf::milliseconds(100);

	bound_rectangle.setSize(size);
	bound_rectangle.setTexture(&texutreHandler.texture_handler["buttonFrame"]);

	displayed_text.setFont(font);
	displayed_text.setCharacterSize(char_size);
	displayed_text.setString(text);
	setTextPosition();

	bound_rectangle.setOutlineThickness(line_thickness);
	bound_rectangle.setOutlineColor(sf::Color::Transparent);
}

void PushButton::setPosition(float x, float y)
{
	pos = sf::Vector2f(x, y);
	bound_rectangle.setPosition(x - bound_rectangle.getSize().x / 2, y - bound_rectangle.getSize().y / 2);
	setTextPosition();
}

void PushButton::setPosition(const sf::Vector2f & position)
{
	pos = position;
	bound_rectangle.setPosition(position.x - bound_rectangle.getSize().x / 2, position.y - bound_rectangle.getSize().y / 2);
	setTextPosition();
}

void PushButton::update()
{
	if (isPressed)
	{
		bound_rectangle.setOutlineColor(outlineColor);
		isPressed = false;
	}
	else
		bound_rectangle.setOutlineColor(sf::Color::Transparent);
}

void PushButton::updateWithAnimations(const sf::Time & time)
{
	if (isPressed)
	{
		isPressed = false;
		setScale(1.1, 1.1);
		shouldUpdateAnimations = true;
	}
	else
	{
		sf::Time g = sf::microseconds(time.asMicroseconds() / 3);
		animationTime -= g;
		if (animationTime.asMilliseconds() > 0 && shouldUpdateAnimations)
		{
			setScale(1 + animationTime.asSeconds(), 1 + animationTime.asSeconds());
		}
		else
		{
			setScale(1, 1);
			animationTime = sf::milliseconds(100);
			shouldUpdateAnimations = false;
		}
	}
	updatePosition();
}

void PushButton::updatePosition()
{
	bound_rectangle.setPosition(pos.x - bound_rectangle.getGlobalBounds().width / 2, pos.y - bound_rectangle.getGlobalBounds().height / 2);
	displayed_text.setPosition(pos.x - displayed_text.getGlobalBounds().width / 2, pos.y - displayed_text.getGlobalBounds().height / 1.1f);
}

void PushButton::setScale(float x, float y)
{
	bound_rectangle.setScale(x, y);
	displayed_text.setScale(x, y);
}