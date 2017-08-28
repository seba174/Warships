#pragma once
#include <SFML/Graphics.hpp>
#include "OptionButton.h"

class OptionNameWithButton :
	public sf::Drawable
{
	sf::Text optionName;

	// position set in last call of setPosition function
	sf::Vector2f size;

	sf::RectangleShape boundRectangle;

	OptionButton button;

		// FUNCTIONS

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void setTextPosition(float x, float y);

	void setButtonPosition(float x, float y);

	void setBoundRectanglePosition();

public:
	// strings in options_list (which contains information about options avaliable) must be separated with ',' (comma)!
	OptionNameWithButton(const std::wstring& optionName, const sf::Font& nameFont, int nameCharacterSize, const sf::Vector2f& size,
		const std::string& options_list, const sf::Font& buttonFont, int buttonCharacterSize, LanguageManager& langMan, const sf::Vector2f& button_size = sf::Vector2f(240, 40),
		const sf::Color& bounds_color = sf::Color::Transparent);

	std::string getDisplayedOption() const { return button.getDisplayedOption(); }

	sf::Vector2f getBoundRectanglePosition() const { return boundRectangle.getPosition(); }

	sf::Vector2f getBoundRectangleSize() const { return boundRectangle.getSize(); }

	// sets position of a CENTER of the object
	void setPosition(float x, float y);

	// sets position of a CENTER of the object
	void setPosition(const sf::Vector2f& position);

	// checks if left arrow button contains mousepos
	bool leftButtonContains(const sf::Vector2f& mousepos) const { return button.leftButtonContains(mousepos); }

	// checks if right arrow button contains mousepos
	bool rightButtonContains(const sf::Vector2f& mousepos) const { return button.rightButtonContains(mousepos); }

	// checks if whole button contains mousepos
	bool buttonContains(const sf::Vector2f& mousepos) const { return button.buttonContains(mousepos); }

	// sets isLeftButtonHighlighted true (used in animation)
	void highlightLeftButton() { button.highlightLeftButton(); }

	// sets isRightButtonHighlighted true (used in animation)
	void highlightRightButton() { button.highlightRightButton(); }

	// sets isPressed true (used in animation)
	void highlightButton() { button.highlightButton(); }

	// function updates animation of left and right arrow buttons
	void updateArrows() { button.updateArrows(); }

	// function changes string displayed in a button for previous one in array
	// if number exceeds array the last text in array is displayed
	void clickLeftButton() { button.clickLeftButton(); }

	// function changes string displayed in a button for next one in array
	// if number exceeds array the first text in array is displayed
	void clickRightButton() { button.clickRightButton(); }

	// function animates and updates button size
	void updateWithAnimations(const sf::Time& time) { button.updateWithAnimations(time); }

	// set scale for whole button (with all elements)
	void setScale(float x, float y) { button.setScale(x, y); }

	// sets scale of button after highlighting
	void setAnimationScale(float x) { button.setAnimationScale(x); }

	// sets duration of animation
	void setAnimationDuration(const sf::Time& time) { button.setAnimationDuration(time); }

	// Sets new displayed option for OptionButton
	// Fucntion sets it only when new displayed option is included in option list
	void setDisplayedOption(const std::string& newDisplayedOption) { button.setDisplayedOption(newDisplayedOption); }

	void setArrowsBlockAndDisplayedString(bool arrowsBlocked, const std::string& displayed) { button.setArrowsBlockAndDisplayedString(arrowsBlocked, displayed); }
};

