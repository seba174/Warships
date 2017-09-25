#pragma once
#include "PushButton.h"
#include "FontHandler.h"
#include "OptionNameWithButton.h"


class OptionsSubMenu :
	public sf::Drawable
{
	int spaceBetweenVertically;
	int additionalSpaceBetweenOptionsAndPushButtons;

	sf::RectangleShape boundRectangle;

	std::vector<OptionNameWithButton> options_buttons;
	std::vector<PushButton> push_buttons;

	sf::Vector2f position;
	int spaceBetweenButtons;
	int additionalPushButtonOffset;
	sf::Vector2f additionalBackgroundSize;

	bool isConstructed;
	LanguageManager& langMan;

		// FUNCTIONS

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	// updates position of PushButtons after adding any new button
	void updatePushButtons();

	void updateBoundRectangle();

public:
	OptionsSubMenu(const sf::Vector2f& position_of_first_button, int spaceBetweenButtons, LanguageManager& langMan);

	//Default constructor
	// You have to call Construct() function in order to have OptionsSubMenu working properly!
	OptionsSubMenu(LanguageManager& langMan);

	// May be run only once;
	void Construct(const sf::Vector2f& position, int spaceBetweenButtons, LanguageManager& langMan);

	void addPushButton(const std::wstring& displayed_text, int char_size, const sf::Font& font, sf::Vector2f size = sf::Vector2f(240, 50),
		const sf::Color& bounds_color = sf::Color::White, int line_thickness = 3);

	void addOptionNameWithButton(const std::wstring& optionName, const sf::Font& nameFont, int nameCharacterSize, const sf::Vector2f& size,
		const std::string& options_list, const sf::Font& buttonFont, int buttonCharacterSize, const sf::Vector2f& button_size = sf::Vector2f(240, 40),
		const sf::Color& bounds_color = sf::Color::White);

	// checks if PushButton of given mapSize contains mousepos
	// if button does not exists, returns false
	bool PushButtonContains(unsigned int number, const sf::Vector2f& mousepos) const;

	// checks if OptionNameWithButton of given mapSize contains mousepos
	// if button does not exists, returns false
	bool OptionNameWithButtonContains(unsigned int number, const sf::Vector2f& mousepos) const;

	// check if any of Option and Push Buttons contains mousepos and if so, highlights them
	// if no button is pressed, function does nothing
	void highlightButtonContaining(const sf::Vector2f& mousepos);

	// sets additional space between OptionsButtons and PushButtons
	void setAdditionalSpaceBetweenOptionsAndPushButtons(int add) { this->additionalSpaceBetweenOptionsAndPushButtons = add; }

	// gets string with current displayed option of given button mapSize
	// if button does not exists, function returns empty string
	std::string getDisplayedOption(unsigned int number);

	// function animates and updates all buttons
	void updateWithAnimations(const sf::Time& time);

	// function checks if any arrow of Options Buttons contains mousepos and if so, clicks it
	void clickArrowContaining(const sf::Vector2f& mousepos);

	// function sets new displayed option for button of given mapSize
	// fucntion sets it only when new displayed option is included in option list
	void setDisplayedOption(unsigned int number, std::string newDisplayedOption);

	void coverPushButtonWithColor(unsigned int number, bool shouldApplyColor, const sf::Color& color);

	void setSpaceBetweenPushButtons(int space);

	void setArrowsBlockAndDisplayedString(unsigned int number, bool arrowsBlocked, const std::string& displayed);

	void setInteriorColorAllPushButtons(const sf::Color& color);

	void addVerticalOffsetForPushButtons(int offset) { additionalPushButtonOffset = offset; updatePushButtons(); }

	void setAdditionalBackgroundSize(const sf::Vector2f& additionalSize) { additionalBackgroundSize = additionalSize; }

	void shouldOptionButtonDisplayOnlyText(unsigned int number, bool whatToDo);

	void setOutlineThickness(unsigned int number, float outLine);

	void disableAnimation(unsigned int number, bool shouldDisable);

	float getOutlineThickness(unsigned int number) const;

	void setDictionaryDisabledBool(unsigned int number, bool val);
};

