#pragma once
#include "LanguageManager.h"


class OptionButton :
	public sf::Drawable, public sf::Transformable
{
	float scale = 1.1f;

	// mapSize of options in options array
	int numberOfOptions;

	// index of displayedText in options array
	int currentOptionNumber;

	// an array of options to choose from
	std::unique_ptr<std::string[]> options;

	sf::RectangleShape boundRectangle, boundRectangleOutline;
	sf::RectangleShape additionalEffects;
	sf::RectangleShape leftbutton;
	sf::RectangleShape rightbutton;

	// used in left arrow animation 
	bool isLeftButtonHighlighted;

	// used in right arrow animation 
	bool isRightButtonHighlighted;

	// option displayed in button at pertacuilar moment
	sf::Text currentDisplayedOption;
	sf::Text drawnOption;

	// position set in last call of setPosition function
	sf::Vector2f pos;

	LanguageManager& languageManager;

	// variables used to control animation
	bool shouldUpdateAnimations;
	sf::Time usableTime;
	float animationScale;
	sf::Time animationTime;
	bool displayOnlyText;
	bool isAnimationBlocked;
	bool isDictionaryDisabled;

	bool areArrowsBlocked;

	// information if mouse is within bound_rectagle (it is used in animation)
	bool isPressed;

	// FUNCTIONS

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	// sets displayedText in the center of button (boundRectangle)
	void setTextPosition();

	float addScale(const std::string& str);

	void updateDrawnOption();

public:
	// strings in options_list (which contains information about options avaliable) must be separated with ',' (comma)!
	OptionButton(const std::string& options_list, const sf::Font& font, int characterSize, LanguageManager& langMan, const sf::Vector2f& button_size = sf::Vector2f(240, 40),
		const sf::Color& bounds_color = sf::Color::White);

	std::string getDisplayedOption() const { return currentDisplayedOption.getString(); }

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
	bool buttonContains(const sf::Vector2f& mousepos) const { return boundRectangle.getGlobalBounds().contains(mousepos); }

	// sets isLeftButtonHighlighted true (used in animation)
	void highlightLeftButton() { isLeftButtonHighlighted = true; }

	// sets isRightButtonHighlighted true (used in animation)
	void highlightRightButton() { isRightButtonHighlighted = true; }

	// sets isPressed true (used in animation)
	void highlightButton() { isPressed = true; }

	// function updates animation of left and right arrow buttons
	void updateArrows();

	// returns size of bound rectangle
	sf::Vector2f getSize() { return sf::Vector2f(boundRectangle.getGlobalBounds().width, boundRectangle.getGlobalBounds().height); }

	// function changes string displayed in a button for previous one in array
	// if mapSize exceeds array the last text in array is displayed
	void clickLeftButton();

	// function changes string displayed in a button for next one in array
	// if mapSize exceeds array the first text in array is displayed
	void clickRightButton();

	// function animates and updates button size
	void updateWithAnimations(const sf::Time& time);

	// set scale for whole button (with all elements)
	void setScale(float x, float y);

	// sets scale of button after highlighting
	void setAnimationScale(float x) { animationScale = x; }

	// sets duration of animation
	void setAnimationDuration(const sf::Time& time) { animationTime = time; }

	void setOutlineThickness(float outLine) { boundRectangleOutline.setOutlineThickness(outLine); }

	void disableAnimation(bool shouldDisable) { isAnimationBlocked = shouldDisable; }

	// Sets new displayed option
	// Fucntion sets it only when new displayed option is included in option list
	void setDisplayedOption(const std::string& newDisplayedOption);

	void handleAdditionalRectangleColor(bool shouldApplyColor, const sf::Color& color);

	void setArrowsBlockAndDisplayedString(bool arrowsBlocked,const std::string& displayed);

	void shouldDisplayOnlyText(bool whatDo) { displayOnlyText = whatDo; }

	float getOutlineThickness() const { return boundRectangleOutline.getOutlineThickness(); }

	void setDictionaryDisabledBool(bool val) { isDictionaryDisabled = val; }
};

