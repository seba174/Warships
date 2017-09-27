#pragma once

class CenteredText:
	public sf::Text
{

	void setOrginInCenter();
public:
	CenteredText();

	void setPosition(float x, float y);

	void setPosition(const sf::Vector2f &position);
};

