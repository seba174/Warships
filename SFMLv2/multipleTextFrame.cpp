#include "multipleTextFrame.h"


void multipleTextFrame::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (const rectangleWithText& rect : frames)
		target.draw(rect, states);
}

multipleTextFrame::multipleTextFrame(unsigned int numberOfFrames)
	: position(0, 0)
{
	for (int i = 0; i < numberOfFrames; ++i)
		frames.push_back(rectangleWithText());
}

bool multipleTextFrame::setStrings(const std::list<std::wstring>& stringList)
{
	if (stringList.size() != frames.size())
		return false;
	
	auto itList = stringList.begin();
	for (auto itFrames = frames.begin(); itFrames != frames.end(); ++itFrames, ++itList)
		itFrames->setString(*itList);
}

void multipleTextFrame::setPosition(const sf::Vector2f & position)
{
	if (frames.empty())
		return;
	this->position = position;

	if (frames.size() % 2 == 1)
	{
		int tmp = frames.size() / 2;
		for (rectangleWithText& rect : frames)
		{
			rect.setPosition(sf::Vector2f(position.x - rect.getSize().x*tmp, position.y));
			--tmp;
		}
	}
	else
	{
		int tmp = frames.size() / 2;
		for (rectangleWithText& rect : frames)
		{
			rect.setPosition(sf::Vector2f(position.x - rect.getSize().x*(tmp - 0.5), position.y));
			--tmp;
		}
	}

}

void multipleTextFrame::setSize(const sf::Vector2f & size)
{
	for (rectangleWithText& rect : frames)
		rect.setSize(size);
	setPosition(position);
}

void multipleTextFrame::setFontSize(float fontSize)
{
	for (rectangleWithText& rect : frames)
		rect.setFontSize(fontSize);
}

void multipleTextFrame::setFont(const sf::Font & font)
{
	for (rectangleWithText& rect : frames)
		rect.setFont(font);
}


