#include "OptionButton.h"
#include "FontHandler.h"
#include "TextureHandler.h"


void OptionButton::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	if (!displayOnlyText)
	{
		target.draw(additionalEffects, states);
		target.draw(boundRectangle, states);
		target.draw(leftbutton, states);
		target.draw(rightbutton, states);
	}
	target.draw(boundRectangleOutline, states);
	target.draw(drawnOption, states);
}


OptionButton::OptionButton(const std::string & options_list, const sf::Font& font, int characterSize, LanguageManager& langMan, const sf::Vector2f& size,
	const sf::Color& bounds_color)
	: isPressed(false), isLeftButtonHighlighted(false), isRightButtonHighlighted(false), shouldUpdateAnimations(false), areArrowsBlocked(false), languageManager(langMan),
	displayOnlyText(false), isAnimationBlocked(false), isDictionaryDisabled(false)
{
	currentOptionNumber = 0;
	usableTime = sf::milliseconds(100);
	animationTime = sf::milliseconds(300);
	animationScale = 1.1f;
	boundRectangleOutline.setFillColor(sf::Color::Transparent);

	TextureHandler& texture = TextureHandler::getInstance();

	int number = 0;
	int beg = 0, end;

	// Counting amount of different options (separated by ',') and saving it to "mapSize"
	do {
		end = options_list.find(',', beg);
		if (end == std::string::npos) end = options_list.size();
		++number;
		beg = end + 1;
	} 
	while (end != options_list.size());	
	
	options = std::make_unique<std::string[]>(number);
	
	numberOfOptions = number;

	// Saving strings to the array
	beg = 0; number = 0;
	do {
		end = options_list.find(',', beg);
		if (end == std::string::npos) end = options_list.size();
		options[number++] = options_list.substr(beg, end - beg);
		beg = end + 1;
	} 
	while (end != options_list.size());

	boundRectangle.setSize(size);
	boundRectangle.setFillColor(sf::Color(255,255,255,200));
	
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

	currentDisplayedOption.setFont(font);
	currentDisplayedOption.setCharacterSize(characterSize);
	currentDisplayedOption.setString(options[0]);
	drawnOption = currentDisplayedOption;
	setTextPosition();

	boundRectangleOutline.setOutlineThickness(0);
	boundRectangleOutline.setOutlineColor(bounds_color);

	boundRectangle.setTexture(&texture.texture_handler["test"]);

	boundRectangleOutline.setSize(boundRectangle.getSize());
	boundRectangleOutline.setPosition(boundRectangle.getPosition());
}

void OptionButton::setTextPosition()
{
	//float newScale = scale;
	//newScale += addScale(currentDisplayedOption.getString());

	currentDisplayedOption.setPosition(boundRectangle.getPosition().x + boundRectangle.getSize().x / 2 - currentDisplayedOption.getGlobalBounds().width / 2,
		boundRectangle.getPosition().y + boundRectangle.getSize().y / 2 - (currentDisplayedOption.getLocalBounds().top*currentDisplayedOption.getScale().y +
			currentDisplayedOption.getGlobalBounds().height / 2));

	drawnOption.setPosition(boundRectangle.getPosition().x + boundRectangle.getSize().x / 2 - drawnOption.getGlobalBounds().width / 2,
		boundRectangle.getPosition().y + boundRectangle.getSize().y / 2 - (drawnOption.getLocalBounds().top*drawnOption.getScale().y + drawnOption.getGlobalBounds().height / 2));
}

float OptionButton::addScale(const std::string & str)
{
	//float tmp = 0;
	//if (str.find('y') != std::string::npos || str.find('g') != std::string::npos || str.find('j') != std::string::npos || str.find('p') != std::string::npos)
	//	tmp = 0.18;
	//return tmp;
	return 0.0f;
}

void OptionButton::updateDrawnOption()
{
	drawnOption = currentDisplayedOption;
	std::wstring tmp = languageManager.getText(currentDisplayedOption.getString());
	if (!tmp.empty()&& !isDictionaryDisabled)
		drawnOption.setString(sf::String(tmp));
	setTextPosition();
}

void OptionButton::setPosition(float x, float y)
{
	pos = sf::Vector2f(x, y);
	boundRectangle.setPosition(x - boundRectangle.getSize().x / 2, y - boundRectangle.getSize().y / 2);
	rightbutton.setPosition(x + boundRectangle.getSize().x / 2 - rightbutton.getGlobalBounds().width, boundRectangle.getPosition().y);
	leftbutton.setPosition(boundRectangle.getPosition());
	setTextPosition();

	boundRectangleOutline.setSize(boundRectangle.getSize());
	boundRectangleOutline.setPosition(boundRectangle.getPosition());
}

void OptionButton::setPosition(const sf::Vector2f & position)
{
	pos = position;
	boundRectangle.setPosition(position.x - boundRectangle.getSize().x / 2, position.y - boundRectangle.getSize().y / 2);
	rightbutton.setPosition(position.x + boundRectangle.getSize().x / 2 - rightbutton.getGlobalBounds().width, boundRectangle.getPosition().y);
	leftbutton.setPosition(boundRectangle.getPosition());
	setTextPosition();

	boundRectangleOutline.setSize(boundRectangle.getSize());
	boundRectangleOutline.setPosition(boundRectangle.getPosition());
}

void OptionButton::updatePosition()
{
	//float newScale = scale;
	//newScale += addScale(currentDisplayedOption.getString());

	boundRectangle.setPosition(pos.x - boundRectangle.getGlobalBounds().width / 2, pos.y - boundRectangle.getGlobalBounds().height / 2);
	
	currentDisplayedOption.setPosition(pos.x - currentDisplayedOption.getGlobalBounds().width / 2, pos.y -
		(currentDisplayedOption.getLocalBounds().top*currentDisplayedOption.getScale().y + currentDisplayedOption.getGlobalBounds().height / 2));
	drawnOption.setPosition(pos.x - drawnOption.getGlobalBounds().width / 2, pos.y -
		(drawnOption.getLocalBounds().top*drawnOption.getScale().y + drawnOption.getGlobalBounds().height / 2));

	
	leftbutton.setPosition(boundRectangle.getPosition());
	rightbutton.setPosition(boundRectangle.getPosition().x + boundRectangle.getGlobalBounds().width - 2 * boundRectangle.getOutlineThickness()
		- rightbutton.getGlobalBounds().width, pos.y - boundRectangle.getGlobalBounds().height / 2);
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
	if (areArrowsBlocked)
		return;
	--currentOptionNumber;
	if (currentOptionNumber < 0)
		currentOptionNumber = numberOfOptions - 1;
	currentDisplayedOption.setString(options[currentOptionNumber]);
	updateDrawnOption();
	setTextPosition();
}

void OptionButton::clickRightButton()
{
	if (areArrowsBlocked)
		return;
	++currentOptionNumber;
	if (currentOptionNumber == numberOfOptions)
		currentOptionNumber = 0;
	currentDisplayedOption.setString(options[currentOptionNumber]);
	updateDrawnOption();
	setTextPosition();
}

void OptionButton::updateWithAnimations(const sf::Time & time)
{
	if (isAnimationBlocked)
		return;

	if (isPressed)
	{
		isPressed = false;
		setScale(animationScale, animationScale);
		shouldUpdateAnimations = true;
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
	}
	updatePosition();
}

void OptionButton::setScale(float x, float y)
{
	boundRectangle.setScale(x, y);
	currentDisplayedOption.setScale(x, y);
	drawnOption.setScale(x, y);
	leftbutton.setScale(x, y);
	rightbutton.setScale(x, y);
}

void OptionButton::setDisplayedOption(const std::string & newDisplayedOption)
{
	for (int i = 0; i < numberOfOptions; ++i)
	{
		if (newDisplayedOption == options[i])
		{
			currentDisplayedOption.setString(newDisplayedOption);
			currentOptionNumber = i;
			updateDrawnOption();
			return;
		}
	}
}

void OptionButton::handleAdditionalRectangleColor(bool shouldApplyColor, const sf::Color & color)
{
	if (shouldApplyColor)
		additionalEffects.setFillColor(color);
	else
		additionalEffects.setFillColor(sf::Color::Transparent);
}

void OptionButton::setArrowsBlockAndDisplayedString(bool arrowsBlocked, const std::string & displayed)
{
	areArrowsBlocked = arrowsBlocked;
	if (areArrowsBlocked)
		currentDisplayedOption.setString(displayed);
	else
		currentDisplayedOption.setString(options[currentOptionNumber]);
	updateDrawnOption();
}

