#include "PushButton.h"



void PushButton::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(interior, states);
	target.draw(displayedText, states);
	//target.draw(additionalEffects, states);
	target.draw(boundRectangle, states);

	
}

void PushButton::setTextPosition()
{
	//// Scale for better visual effect
	//float newScale = scale;
	//newScale += addScale(displayedText.getString());

	//displayedText.setPosition(boundRectangle.getPosition().x + boundRectangle.getSize().x / 2 - displayedText.getGlobalBounds().width / 2,
	//	boundRectangle.getPosition().y + boundRectangle.getSize().y / 2 - displayedText.getGlobalBounds().height / newScale);

	displayedText.setPosition(boundRectangle.getPosition().x + boundRectangle.getSize().x / 2 - displayedText.getGlobalBounds().width / 2,
		boundRectangle.getPosition().y + boundRectangle.getSize().y / 2 - (displayedText.getLocalBounds().top + displayedText.getGlobalBounds().height / 2.0f));
}

float PushButton::addScale(const std::wstring & str)
{
	float tmp = 0;
	//if (str.find('y') != std::wstring::npos || str.find('g') != std::wstring::npos || str.find('j') != std::wstring::npos || str.find('p') != std::wstring::npos
	//	|| str.find(L'ą') != std::wstring::npos || str.find(L'ę') != std::wstring::npos)
	//	tmp = 0.18;
	return tmp;
}

void PushButton::setInteriorPosition()
{
	interior.setPosition(boundRectangle.getPosition().x + (boundRectangle.getSize().x - interior.getSize().x) / 2,
		boundRectangle.getPosition().y + (boundRectangle.getSize().y - interior.getSize().y) / 2);
}

PushButton::PushButton(const std::wstring& text, int char_size, const sf::Font& font, sf::Vector2f size, const sf::Color& bounds_color,
	 int line_thickness)
	: isPressed(false), shouldUpdateAnimations(false)
{
	TextureHandler& texutreHandler = TextureHandler::getInstance();

	outlineColor = bounds_color;
	animationTime = sf::milliseconds(100);

	boundRectangle.setSize(size);
	interior.setFillColor(sf::Color::Transparent);
	interior.setSize(sf::Vector2f(interiorScale*boundRectangle.getSize().x, interiorScale*boundRectangle.getSize().y));
	additionalEffects = interior;
	setInteriorPosition();

	boundRectangle.setTexture(&texutreHandler.texture_handler["buttonFrame"]);


	displayedText.setFont(font);
	displayedText.setCharacterSize(char_size);
	displayedText.setString(text);

	setTextPosition();

	boundRectangle.setOutlineThickness(static_cast<float>(line_thickness));
	boundRectangle.setOutlineColor(sf::Color::Transparent);
}

void PushButton::setPosition(float x, float y)
{
	pos = sf::Vector2f(x, y);
	boundRectangle.setPosition(x - boundRectangle.getSize().x / 2, y - boundRectangle.getSize().y / 2);
	setInteriorPosition();
	additionalEffects.setPosition(interior.getPosition());
	setTextPosition();
}

void PushButton::setPosition(const sf::Vector2f & position)
{
	pos = position;
	boundRectangle.setPosition(position.x - boundRectangle.getSize().x / 2, position.y - boundRectangle.getSize().y / 2);
	setInteriorPosition();
	additionalEffects.setPosition(interior.getPosition());
	setTextPosition();
}

void PushButton::update()
{
	if (isPressed)
	{
		boundRectangle.setOutlineColor(outlineColor);
		isPressed = false;
	}
	else
		boundRectangle.setOutlineColor(sf::Color::Transparent);
}

void PushButton::updateWithAnimations(const sf::Time & time)
{
	if (isPressed)
	{
		isPressed = false;
		setScale(1.1f, 1.1f);
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
	float newScale = scale;
	newScale += addScale(displayedText.getString());

	boundRectangle.setPosition(pos.x - boundRectangle.getGlobalBounds().width / 2, pos.y - boundRectangle.getGlobalBounds().height / 2);
	setInteriorPosition();
	additionalEffects.setPosition(interior.getPosition());
	displayedText.setPosition(pos.x - displayedText.getGlobalBounds().width / 2, pos.y - (displayedText.getScale().y*displayedText.getLocalBounds().top+displayedText.getGlobalBounds().height / 2));
	//displayedText.setPosition(pos.x - displayedText.getGlobalBounds().width / 2, pos.y - displayedText.getGlobalBounds().height / newScale);
}

void PushButton::setScale(float x, float y)
{
	boundRectangle.setScale(x, y);
	displayedText.setScale(x, y);
	additionalEffects.setScale(x, y);
	interior.setScale(x, y);
}

void PushButton::coverButtonWithColor(bool shouldApplyColor, const sf::Color & color)
{
	if (shouldApplyColor)
	{
		boundRectangle.setFillColor(sf::Color(color.r, color.g, color.b, 255));
		displayedText.setFillColor(sf::Color(255, 255, 255, color.a));
	}
	else
	{
		displayedText.setFillColor(sf::Color::White);
		boundRectangle.setFillColor(sf::Color::White);
	}
}

void PushButton::setInteriorColor(const sf::Color & color)
{
	interior.setFillColor(color);
}


