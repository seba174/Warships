#include "stdafx.h"
#include "HelpBubble.h"
#include "TextureHandler.h"


HelpBubble::HelpBubble()
{
	bubble.setTexture(&TextureHandler::getInstance().texture_handler["bubble"]);
}

void HelpBubble::setPosition(const sf::Vector2f & position)
{
	bubble.setPosition(position);
	setTextPosition();
	setOrigin(bubble.getOrigin());
}

void HelpBubble::setOrigin(const sf::Vector2f & origin)
{
	bubble.setOrigin(origin);
	text.setOrigin(origin);
}

void HelpBubble::setScale(float scale)
{
	bubble.setScale(scale, scale);
	text.setScale(scale, scale);
}

void HelpBubble::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(bubble, states);
	target.draw(text, states);
}

void HelpBubble::setTextPosition()
{
	float factor{ -1.6f };
	int temp = 0;
	sf::Vector2f bubbleTemp{ bubble.getPosition() - bubble.getOrigin() + bubble.getSize() / 2.0f };

	sf::FloatRect textRect{ text.getLocalBounds() };
	sf::Vector2f textOrigin{ text.getOrigin() };
	text.setPosition(bubbleTemp.x - (textRect.left + textRect.width / 2) + textOrigin.x, bubbleTemp.y - (textRect.top + textRect.height / factor) + textOrigin.y);
}
