#pragma once
#include "PushButton.h"
#include "FontHandler.h"
#include "OptionNameWithButton.h"


class OptionsSubMenu :
	public sf::Drawable
{
	const int spaceBetweenVertically = 10;
	int additionalSpaceBetweenOptionsAndPushButtons;

	std::vector<OptionNameWithButton> options_buttons;
	std::vector<PushButton> push_buttons;

	sf::Vector2f position;
	int spaceBetweenButtons;

	bool isConstructed;

		// FUNCTIONS

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	// updates position of PushButtons after adding any new button
	void updatePushButtons();

public:
	OptionsSubMenu(const sf::Vector2f& position_of_first_button, int spaceBetweenButtons);

	//Default constructor
	// You have to call Construct() function in order to have OptionsSubMenu working properly!
	OptionsSubMenu();

	// May be run only once;
	void Construct(const sf::Vector2f& position, int spaceBetweenButtons);

	void addPushButton(const std::string& displayed_text, int char_size, const sf::Font& font, sf::Vector2f size = sf::Vector2f(240, 50),
		const sf::Color& bounds_color = sf::Color::White, int line_thickness = 3);

	void addOptionNameWithButton(const std::string& optionName, const sf::Font& nameFont, int nameCharacterSize, const sf::Vector2f& size,
		const std::string& options_list, const sf::Font& buttonFont, int buttonCharacterSize, const sf::Vector2f& button_size = sf::Vector2f(240, 40),
		const sf::Color& bounds_color = sf::Color::Transparent);

	// checks if PushButton of given number contains mousepos
	// if button does not exists, returns false
	bool PushButtonContains(int number, const sf::Vector2f& mousepos) const;

	// checks if OptionNameWithButton of given number contains mousepos
	// if button does not exists, returns false
	bool OptionNameWithButtonContains(int number, const sf::Vector2f& mousepos) const;

	// check if any of Option and Push Buttons contains mousepos and if so, highlights them
	// if no button is pressed, function does nothing
	void highlightButtonContaining(const sf::Vector2f& mousepos);

	// sets additional space between OptionsButtons and PushButtons
	void setAdditionalSpaceBetweenOptionsAndPushButtons(int add) { this->additionalSpaceBetweenOptionsAndPushButtons = add; }

	// function animates and updates all buttons
	void updateWithAnimations(const sf::Time& time);

	// function checks if any arrow of Options Buttons contains mousepos and if so, clicks it
	void clickArrowContaining(const sf::Vector2f& mousepos);

};

