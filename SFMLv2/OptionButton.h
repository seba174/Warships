#pragma once
#include <string>
#include <memory>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Text.hpp>
#include "FontHandler.h"
#include "TextureHandler.h"

class OptionButton :
	public sf::Drawable, public sf::Transformable
{
	const float scale = 0.95f;

	// number of options in options array
	int number_of_options;

	// index of displayed_text in options array
	int current_option_number;

	// an array of options to choose from
	std::unique_ptr<std::string[]> options;

	sf::RectangleShape bound_rectangle;
	sf::RectangleShape leftbutton;
	sf::RectangleShape rightbutton;

	// used in left arrow animation 
	bool isLeftButtonHighlighted;

	// used in right arrow animation 
	bool isRightButtonHighlighted;

	// option displayed in button at pertacuilar moment
	sf::Text current_displayed_option;

	// position set in last call of setPosition function
	sf::Vector2f pos;

	// variables used to control animation
	bool shouldUpdateAnimations;
	sf::Time usableTime;
	float animationScale;
	sf::Time animationTime;

	// information if mouse is within bound_rectagle (it is used in animation)
	bool isPressed;

	// FUNCTIONS

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	// sets displayed_text in the center of button (bound_rectangle)
	void setTextPosition();

	float addScale(const std::string& str);

public:
	// strings in options_list (which contains information about options avaliable) must be separated with ',' (comma)!
	OptionButton(const std::string& options_list, const sf::Font& font, int characterSize, const sf::Vector2f& button_size = sf::Vector2f(240, 40),
		const sf::Color& bounds_color = sf::Color::Transparent);

	std::string getDisplayedOption() const { return current_displayed_option.getString(); }

	// sets position of a CENTER of a button 
	void setPosition(float x, float y);

	// sets position of a CENTER of a button 
	void setPosition(const sf::Vector2f& position);

	// updates position of button in order to be in a center of it's last set position (by setPosition function)
	void updatePosition();

	// checks if left arrow button contains mousepos
	bool leftButtonContains(const sf::Vector2f& mousepos) const { return leftbutton.getGlobalBounds().contains(mousepos); }

	// checks if right arrow button contains mousepos
	bool rightButtonContains(const sf::Vector2f& mousepos) const { return rightbutton.getGlobalBounds().contains(mousepos); }

	// checks if whole button contains mousepos
	bool buttonContains(const sf::Vector2f& mousepos) const { return bound_rectangle.getGlobalBounds().contains(mousepos); }

	// sets isLeftButtonHighlighted true (used in animation)
	void highlightLeftButton() { isLeftButtonHighlighted = true; }

	// sets isRightButtonHighlighted true (used in animation)
	void highlightRightButton() { isRightButtonHighlighted = true; }

	// sets isPressed true (used in animation)
	void highlightButton() { isPressed = true; }

	// function updates animation of left and right arrow buttons
	void updateArrows();

	// returns size of bound rectangle
	sf::Vector2f getSize() { return sf::Vector2f(bound_rectangle.getGlobalBounds().width, bound_rectangle.getGlobalBounds().height); }

	// function changes string displayed in a button for previous one in array
	// if number exceeds array the last text in array is displayed
	void clickLeftButton();

	// function changes string displayed in a button for next one in array
	// if number exceeds array the first text in array is displayed
	void clickRightButton();

	// function animates and updates button size
	void updateWithAnimations(const sf::Time& time);

	// set scale for whole button (with all elements)
	void setScale(float x, float y);

	// sets scale of button after highlighting
	void setAnimationScale(float x) { animationScale = x; }

	// sets duration of animation
	void setAnimationDuration(const sf::Time& time) { animationTime = time; }

	// Sets new displayed option
	// Fucntion sets it only when new displayed option is included in option list
	void setDisplayedOption(const std::string& newDisplayedOption);
};

