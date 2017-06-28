#pragma once
#include "PushButton.h"
#include "FontHandler.h"
#include "OptionNameWithButton.h"


class OptionsSubMenu :
	public sf::Drawable
{
	std::vector<OptionNameWithButton> buttons;
	//PushButton back, apply_changes, load_default.

		// FUNCTIONS

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	OptionsSubMenu();
	~OptionsSubMenu();
};

