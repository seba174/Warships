#include "multipleTextFrame.h"


void MultipleTextFrame::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (const RectangleWithText& rect : frames)
		target.draw(rect, states);
}

MultipleTextFrame::MultipleTextFrame(unsigned int numberOfFrames)
	: position(0, 0)
{
	for (unsigned int i = 0; i < numberOfFrames; ++i)
		frames.push_back(RectangleWithText());
}

bool MultipleTextFrame::setStrings(const std::list<std::wstring>& stringList)
{
	if (stringList.size() != frames.size())
		return false;

	auto itList = stringList.begin();
	for (auto itFrames = frames.begin(); itFrames != frames.end(); ++itFrames, ++itList)
		itFrames->setString(*itList);
	return true;
}

void MultipleTextFrame::setPosition(const sf::Vector2f & position)
{
	if (frames.empty())
		return;
	this->position = position;

	if (frames.size() % 2 == 1)
	{
		int tmp = frames.size() / 2;
		for (RectangleWithText& rect : frames)
		{
			rect.setPosition(sf::Vector2f(position.x - rect.getSize().x*tmp, position.y));
			--tmp;
		}
	}
	else
	{
		int tmp = frames.size() / 2;
		for (RectangleWithText& rect : frames)
		{
			rect.setPosition(sf::Vector2f(position.x - rect.getSize().x*(tmp - 0.5f), position.y));
			--tmp;
		}
	}
}

void MultipleTextFrame::setSize(const sf::Vector2f & size)
{
	for (RectangleWithText& rect : frames)
		rect.setSize(size);
	setPosition(position);
}

void MultipleTextFrame::setFontSize(float fontSize)
{
	for (RectangleWithText& rect : frames)
		rect.setFontSize(fontSize);
}

void MultipleTextFrame::setFont(const sf::Font & font)
{
	for (RectangleWithText& rect : frames)
		rect.setFont(font);
}

std::list<std::wstring> MultipleTextFrame::getStrings() const
{
	std::list<std::wstring> temp;
	for (const RectangleWithText& rect : frames)
	{
		temp.push_back(rect.getString());
	}
	return temp;
}


