#pragma once
#include <string>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Text.hpp>
#include "TextureHandler.h"

class PushButton :
	public sf::Drawable, public sf::Transformable
{
	float scale = 1.1f;
	float interiorScale = 0.93f;

	sf::RectangleShape boundRectangle;
	sf::RectangleShape additionalEffects;
	sf::RectangleShape interior;
	sf::Text displayedText;
	
	// information if mouse is within bound_rectagle (it is used in animation)
	bool isPressed;

	sf::Color outlineColor;

	// variables used to control animation
	bool shouldUpdateAnimations;
	sf::Time animationTime;

	// position set in last call of setPosition function
	sf::Vector2f pos;

		// FUNCTIONS

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	// sets displayedText in the center of button (boundRectangle)
	void setTextPosition();

	float addScale(const std::wstring& str);

	void setInteriorPosition();

public:

	PushButton(const std::wstring& displayed_text, int char_size, const sf::Font& font, sf::Vector2f size = sf::Vector2f(240, 50),
		const sf::Color& bounds_color = sf::Color::White,  int line_thickness = 3); 

	// sets style for the text in the button
	void setStyle(sf::Uint32 style) { displayedText.setStyle(style); }

	// gets size of an bounding box with text 
	sf::Vector2f getSize() const { return sf::Vector2f(boundRectangle.getSize().x, boundRectangle.getSize().y); }

	// function chcecks if a point is inside button
	// WARNING! if you pass mouse position, check if you don't need to use mapCoordsToPixels function!
	bool contains(const sf::Vector2f& mousepos) const { return boundRectangle.getGlobalBounds().contains(mousepos); }

	// sets isPressed = true
	void highlightButton() { isPressed = true; }

	// sets position of a CENTER of a button 
	void setPosition(float x, float y);

	// sets position of a CENTER of a button 
	void setPosition(const sf::Vector2f& position);

	// function updates information about OutlineColor
	void update();

	// function animates and updates button size
	void updateWithAnimations(const sf::Time& time);

	// updates position of button in order to be in a center of it's last set position (by setPosition function)
	void updatePosition();

	// set scale for button
	void setScale(float x, float y);

	// returns size of a button
	sf::Vector2f getSize() { return boundRectangle.getSize(); }

	void coverButtonWithColor(bool shouldApplyColor, const sf::Color& color);

	void setInteriorColor(const sf::Color& color);
};

