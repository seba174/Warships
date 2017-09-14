#pragma once
#include "PushButton.h"
#include "FontHandler.h"

class SubMenu : 
	public sf::Drawable
{
protected:
	// title of SubMenu (static)
	sf::Text title;

	// vector of different buttons
	std::vector<PushButton> buttons;

	// true if SubMenu was fully constructed (not by using default constructor)
	bool isConstructed;

		// FUNCTIONS

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	// default constructor
	// sets isConstructed value false
	// You have to use construct function in order to have it working properly!
	SubMenu() { isConstructed = false; }

	// strings in buttons_text (which contains information about text on buttons) must be separated with ',' (comma)!
	// title and first_button positions are positions of a CENTER of an object
	SubMenu(const std::wstring& title, const std::wstring& buttons_text, int title_character_size, int char_size, const sf::Vector2f& title_position,
		const sf::Vector2f& first_button_position, const sf::Vector2f& button_size, int space_between_buttons, const sf::Color& bounds_color,
		const sf::Font& font, sf::Uint32 title_style = sf::Text::Regular, sf::Uint32 buttons_style = sf::Text::Regular);

	// acts like constructor, may be run only once
	void construct(const std::wstring& title, const std::wstring& buttons_text, int title_character_size, int char_size, const sf::Vector2f& title_position,
		const sf::Vector2f& first_button_position, const sf::Vector2f& button_size, int space_between_buttons, const sf::Color& bounds_color,
		const sf::Font& font, sf::Uint32 title_style = sf::Text::Regular, sf::Uint32 buttons_style = sf::Text::Regular);

	// checks if any button in SubMenu contains mousepos
	// returns number of a button which contains mousepos
	// if no button is pressed, returns -1
	int contains(const sf::Vector2f& mousepos) const;

	// checks if button of given number contains mousepos
	// if button does not exists, returns false
	bool contains(unsigned int number, const sf::Vector2f& mousepos) const;

	// updates information about OutlineColor for every button
	void updateButtons();

	// updates and anitmates every button
	void updateButtonsWithAnimations(const sf::Time& time);

	// pressButton which contains mousepos
	// if no button is pressed, function does nothing
	void highlightButtonContaining(const sf::Vector2f& mousepos);

	// sets isPressed = true for indicated button
	void highlightButton(unsigned int number);

	void coverButtonWithColor(unsigned int number, bool shouldApplyColor, const sf::Color& color);

	void setInteriorColorAllButtons(const sf::Color& color);
};

