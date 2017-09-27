#pragma once
#include "CenteredText.h"
#include "PushButton.h"

class LanguageManager;

class CreditsMenu :
	public sf::Drawable
{
	std::array<CenteredText, 29> textArray;
	sf::RectangleShape rect;
	PushButton button;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	CreditsMenu(const sf::Vector2f &position, const std::wstring & text, unsigned characterSize, const sf::Font & font, float interfaceScale, const LanguageManager& langMan);

	bool buttonContains(const sf::Vector2f& mousepos) const { return button.contains(mousepos); }

	void highlightButton(const sf::Vector2f& mousepos) { if (button.contains(mousepos)) button.highlightButton(); }

	void updateButton(const sf::Time& time) { button.updateWithAnimations(time); }
};

